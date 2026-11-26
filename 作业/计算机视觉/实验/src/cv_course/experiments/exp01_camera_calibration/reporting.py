# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

import json
import shutil
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile

from docx import Document

from .calibration import CalibrationResult


REPO_ROOT = Path(__file__).resolve().parents[4]
EXPERIMENT_ROOT = REPO_ROOT / "experiments" / "exp01_camera_calibration"
PACKAGE_ROOT = Path(__file__).resolve().parent
TEST_ROOT = REPO_ROOT / "tests" / "exp01_camera_calibration"


def _round_matrix(matrix, digits: int = 6) -> list[list[float]]:
    return [[round(float(value), digits) for value in row] for row in matrix]


def _round_vector(vector, digits: int = 6) -> list[float]:
    return [round(float(value), digits) for value in vector]


def result_to_dict(result: CalibrationResult) -> dict[str, object]:
    return {
        "projection_matrix": _round_matrix(result.projection_matrix),
        "intrinsic_matrix": _round_matrix(result.intrinsic_matrix),
        "rotation_matrix": _round_matrix(result.rotation_matrix),
        "translation_vector": _round_vector(result.translation_vector),
        "camera_center": _round_vector(result.camera_center),
        "scale_factor": round(float(result.scale_factor), 6),
        "projected_points": _round_matrix(result.projected_points),
        "reprojection_errors": _round_vector(result.reprojection_errors),
        "mean_reprojection_error": round(float(result.mean_reprojection_error), 8),
        "max_reprojection_error": round(float(result.max_reprojection_error), 8),
    }


def write_calibration_results(result: CalibrationResult, output_path: Path) -> Path:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        json.dumps(result_to_dict(result), indent=2, ensure_ascii=False),
        encoding="utf-8",
    )
    return output_path


def _write_matrix_table(document: Document, title: str, matrix) -> None:
    document.add_paragraph(title)
    table = document.add_table(rows=len(matrix), cols=len(matrix[0]))
    table.style = "Table Grid"
    for row_index, row in enumerate(matrix):
        for column_index, value in enumerate(row):
            table.cell(row_index, column_index).text = f"{float(value):.6f}"


def _write_validation_table(document: Document, result: CalibrationResult) -> None:
    document.add_paragraph("重投影验证结果如下，误差单位与题目给定成像平面坐标一致。")
    headers = ["点号", "u 真值", "v 真值", "u 估计", "v 估计", "误差"]
    table = document.add_table(rows=1, cols=len(headers))
    table.style = "Table Grid"
    for index, header in enumerate(headers):
        table.rows[0].cells[index].text = header

    from .calibration import IMAGE_POINTS

    for point_index, (truth, estimated, error) in enumerate(
        zip(IMAGE_POINTS, result.projected_points, result.reprojection_errors),
        start=1,
    ):
        row = table.add_row().cells
        row[0].text = str(point_index)
        row[1].text = f"{truth[0]:.4f}"
        row[2].text = f"{truth[1]:.4f}"
        row[3].text = f"{estimated[0]:.6f}"
        row[4].text = f"{estimated[1]:.6f}"
        row[5].text = f"{error:.8f}"


def _write_report_docx(
    result: CalibrationResult,
    report_path: Path,
    group_name: str,
    members: list[str],
) -> Path:
    document = Document()
    document.add_heading("实验1 相机标定实验报告", level=0)
    document.add_paragraph(f"组名：{group_name}")
    document.add_paragraph("组员信息：")
    for member in members:
        document.add_paragraph(member, style="List Bullet")

    document.add_heading("一、实验分析", level=1)
    document.add_paragraph(
        "本实验采用针孔相机模型。设三维点的齐次坐标为 X~=[X,Y,Z,1]^T，"
        "其成像点齐次坐标为 x~=[u,v,1]^T，则两者满足 s x~ = M X~，"
        "其中 M 为 3×4 投影矩阵。"
    )
    document.add_paragraph(
        "将 M 的三行分别记为 m1^T、m2^T、m3^T，可得 "
        "u = (m1^T X~) / (m3^T X~)，v = (m2^T X~) / (m3^T X~)。"
        "每组点对应两条线性约束，10 组对应点一共形成 20 条约束。"
    )
    document.add_paragraph(
        "实验中先对三维点和二维点做相似变换归一化，再使用 DLT 构造线性方程组 "
        "A m = 0，并通过 SVD 取最小奇异值对应的右奇异向量，恢复投影矩阵 M。"
    )
    document.add_paragraph(
        "得到 M 后，将其左 3×3 子块记为 A。利用 RQ 分解写成 A = K R，"
        "其中 K 为上三角内参矩阵，R 为旋转矩阵。再由投影矩阵最后一列求得平移向量 t，"
        "并通过重投影误差检验标定结果的正确性。题目给定 ε=1，与本实验中保持 K 对角线为正、"
        "旋转矩阵满足 det(R)=1 的选取一致。"
    )

    document.add_heading("二、实验结果", level=1)
    _write_matrix_table(document, "投影矩阵 M：", result.projection_matrix)
    _write_matrix_table(document, "内参数矩阵 K：", result.intrinsic_matrix)
    _write_matrix_table(document, "旋转矩阵 R：", result.rotation_matrix)
    document.add_paragraph(
        "平移向量 t = [" + ", ".join(f"{value:.6f}" for value in result.translation_vector) + "]^T"
    )
    document.add_paragraph(
        "相机中心 C = [" + ", ".join(f"{value:.6f}" for value in result.camera_center) + "]^T"
    )
    document.add_paragraph(f"平均重投影误差：{result.mean_reprojection_error:.8f}")
    document.add_paragraph(f"最大重投影误差：{result.max_reprojection_error:.8f}")

    document.add_heading("三、正确性验证", level=1)
    document.add_paragraph(
        "将估计得到的投影矩阵重新作用在 10 个三维点上，可得到与题目给定二维点几乎一致的重投影坐标。"
        "平均误差和最大误差都在 10^-4 量级，说明估计结果与给定数据高度一致。"
    )
    _write_validation_table(document, result)

    document.add_heading("四、第2题回答", level=1)
    document.add_paragraph(
        "在三维重建中，图像点本质上只给出一条从相机中心出发的成像光线。若不知道相机的内参 K，"
        "就无法把像素坐标换算到归一化成像平面；若不知道外参 R、t，就无法把不同视角下的光线统一到同一世界坐标系。"
    )
    document.add_paragraph(
        "以双目三角化为例，两幅图像满足 x1~ = P1 X~、x2~ = P2 X~，其中 Pi = Ki[Ri|ti]。"
        "只有先通过标定得到 Pi，才能建立 x_i × P_i X~ = 0 的线性方程组并恢复真实三维点。"
        "如果没有标定，恢复结果最多只能停留在射影意义下，无法得到正确的长度、角度和空间位置。"
    )
    document.add_paragraph(
        "因此，相机标定是把二维像素观测转换为可用于几何计算的物理成像模型的前提，"
        "它直接决定了后续三维重建、姿态估计和测量结果的精度。"
    )

    document.add_heading("五、说明", level=1)
    document.add_paragraph(
        "本报告由代码自动生成。封面的组名、姓名和学号当前使用占位内容，提交前请替换为实际信息。"
    )
    report_path.parent.mkdir(parents=True, exist_ok=True)
    document.save(report_path)
    return report_path


def _copy_source_tree(target_root: Path) -> None:
    code_root = target_root / "code"
    code_root.mkdir(parents=True, exist_ok=True)

    copy_items = [
        (REPO_ROOT / "pyproject.toml", code_root / "pyproject.toml"),
        (PACKAGE_ROOT, code_root / "src" / "cv_course" / "experiments" / "exp01_camera_calibration"),
        (REPO_ROOT / "src" / "cv_course" / "__init__.py", code_root / "src" / "cv_course" / "__init__.py"),
        (
            REPO_ROOT / "src" / "cv_course" / "experiments" / "__init__.py",
            code_root / "src" / "cv_course" / "experiments" / "__init__.py",
        ),
        (REPO_ROOT / "tests" / "__init__.py", code_root / "tests" / "__init__.py"),
        (TEST_ROOT, code_root / "tests" / "exp01_camera_calibration"),
        (REPO_ROOT / "scripts" / "run_experiment_01.py", code_root / "scripts" / "run_experiment_01.py"),
        (REPO_ROOT / "README.md", code_root / "README.md"),
        (EXPERIMENT_ROOT / "README.md", code_root / "experiments" / "exp01_camera_calibration" / "README.md"),
    ]

    for source_path, destination in copy_items:
        if not source_path.exists():
            continue
        destination.parent.mkdir(parents=True, exist_ok=True)
        if source_path.is_dir():
            shutil.copytree(
                source_path,
                destination,
                dirs_exist_ok=True,
                ignore=shutil.ignore_patterns("__pycache__", "*.pyc"),
            )
        else:
            shutil.copy2(source_path, destination)


def _write_readme(target_root: Path) -> None:
    readme_path = target_root / "README.txt"
    readme_path.write_text(
        "1. 报告文件：实验报告_相机标定.docx\n"
        "2. 标定结果：标定结果.json\n"
        "3. 源代码：code 目录\n"
        "4. 若需重新生成，请在仓库根目录运行 scripts/run_experiment_01.py。\n",
        encoding="utf-8",
    )


def _zip_folder(folder_path: Path, archive_path: Path) -> Path:
    archive_path.parent.mkdir(parents=True, exist_ok=True)
    with ZipFile(archive_path, "w", compression=ZIP_DEFLATED) as archive:
        for file_path in folder_path.rglob("*"):
            archive.write(file_path, file_path.relative_to(folder_path.parent))
    return archive_path


def build_submission_package(
    result: CalibrationResult,
    output_root: Path,
    group_name: str = "待填写组名",
    members: list[str] | None = None,
) -> dict[str, Path]:
    members = members or ["姓名：待填写    学号：待填写"]
    submission_folder = output_root / f"实验1_{group_name}"
    if submission_folder.exists():
        shutil.rmtree(submission_folder)
    submission_folder.mkdir(parents=True, exist_ok=True)

    report_path = _write_report_docx(
        result,
        submission_folder / "实验报告_相机标定.docx",
        group_name,
        members,
    )
    result_path = write_calibration_results(result, submission_folder / "标定结果.json")
    _copy_source_tree(submission_folder)
    _write_readme(submission_folder)

    archive_path = _zip_folder(submission_folder, output_root / f"实验1_{group_name}.zip")
    return {
        "folder": submission_folder,
        "report": report_path,
        "results": result_path,
        "archive": archive_path,
    }
