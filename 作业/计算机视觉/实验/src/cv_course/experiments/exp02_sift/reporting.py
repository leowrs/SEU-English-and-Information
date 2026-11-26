# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

import shutil
from pathlib import Path
from zipfile import ZIP_DEFLATED, ZipFile

from docx import Document
from docx.shared import Inches

from .sift_experiment import SiftExperimentResult, write_experiment_summary


REPO_ROOT = Path(__file__).resolve().parents[4]
EXPERIMENT_ROOT = REPO_ROOT / "experiments" / "exp02_sift"
PACKAGE_ROOT = Path(__file__).resolve().parent
TEST_ROOT = REPO_ROOT / "tests" / "exp02_sift"


_CATEGORY_LABELS = {
    "baseline": "基准图",
    "rotation": "旋转因素",
    "illumination": "光照因素",
    "scale": "尺寸因素",
    "content": "不同内容",
}

_VARIANT_CATEGORIES = {
    "img1_base_1000": "baseline",
    "img1_rotate_30": "rotation",
    "img1_dark": "illumination",
    "img1_bright": "illumination",
    "img1_scale_700": "scale",
    "img1_scale_1200": "scale",
    "img2_base_1000": "content",
}

_VARIANT_LABELS = {
    "img1_base_1000": "img1 基准图（长边 1000）",
    "img1_rotate_30": "img1 旋转 30 度",
    "img1_dark": "img1 低亮度（0.55x）",
    "img1_bright": "img1 高亮度（1.35x）",
    "img1_scale_700": "img1 缩放到长边 700",
    "img1_scale_1200": "img1 缩放到长边 1200",
    "img2_base_1000": "img2 不同内容图（长边 1000）",
}

_PAIR_LABELS = {
    ("img1_base_1000", "img1_rotate_30"): "旋转 30 度",
    ("img1_base_1000", "img1_dark"): "低亮度",
    ("img1_base_1000", "img1_bright"): "高亮度",
    ("img1_base_1000", "img1_scale_700"): "缩小尺寸",
    ("img1_base_1000", "img1_scale_1200"): "放大尺寸",
    ("img1_base_1000", "img2_base_1000"): "不同内容",
}


def _variant_rows(result: SiftExperimentResult) -> list[dict[str, object]]:
    return list(result.summary["variants"])  # type: ignore[index]


def _match_rows(result: SiftExperimentResult) -> list[dict[str, object]]:
    return list(result.summary["matches"])  # type: ignore[index]


def _add_variant_table(document: Document, result: SiftExperimentResult) -> None:
    headers = ["实验因素", "图像", "尺寸", "检测特征点数"]
    table = document.add_table(rows=1, cols=len(headers))
    table.style = "Table Grid"
    for index, header in enumerate(headers):
        table.rows[0].cells[index].text = header

    for row_payload in _variant_rows(result):
        name = str(row_payload["name"])
        row = table.add_row().cells
        row[0].text = _CATEGORY_LABELS[_VARIANT_CATEGORIES[name]]
        row[1].text = _VARIANT_LABELS[name]
        row[2].text = f"{row_payload['width']} x {row_payload['height']}"
        row[3].text = str(row_payload["keypoint_count"])


def _add_match_table(document: Document, result: SiftExperimentResult) -> None:
    headers = ["匹配实验", "基准特征点", "对比特征点", "通过 ratio test 的匹配数", "匹配率"]
    table = document.add_table(rows=1, cols=len(headers))
    table.style = "Table Grid"
    for index, header in enumerate(headers):
        table.rows[0].cells[index].text = header

    for row_payload in _match_rows(result):
        pair = (str(row_payload["query"]), str(row_payload["train"]))
        row = table.add_row().cells
        row[0].text = _PAIR_LABELS[pair]
        row[1].text = str(row_payload["query_keypoint_count"])
        row[2].text = str(row_payload["train_keypoint_count"])
        row[3].text = str(row_payload["match_count"])
        row[4].text = f"{float(row_payload['match_rate']) * 100:.2f}%"


def _add_picture_if_exists(document: Document, image_path: Path, caption: str) -> None:
    if not image_path.exists():
        return
    document.add_picture(str(image_path), width=Inches(5.8))
    document.add_paragraph(caption)


def _lookup_match_rate(result: SiftExperimentResult, pair: tuple[str, str]) -> float:
    for row_payload in _match_rows(result):
        if (row_payload["query"], row_payload["train"]) == pair:
            return float(row_payload["match_rate"])
    return 0.0


def write_experiment_report(
    result: SiftExperimentResult,
    report_path: Path,
    group_name: str,
    members: list[str] | None = None,
) -> Path:
    members = members or ["姓名：待填写    学号：待填写"]

    document = Document()
    document.add_heading("实验二 SIFT算法实验报告", level=0)
    document.add_paragraph(f"组名：{group_name}")
    document.add_paragraph("组员信息：")
    for member in members:
        document.add_paragraph(member, style="List Bullet")

    document.add_heading("一、实验目标与方法", level=1)
    document.add_paragraph(
        "本实验使用课程发布包中的 David Lowe SIFT 程序作为特征提取器。"
        "程序先将输入图像转为灰度 PGM，并控制长边不超过 1200 像素，满足发布说明中图像尺寸不宜超过 2000 x 2000 的限制。"
    )
    document.add_paragraph(
        "实验围绕四类因素展开：图像旋转、光照变化、图像尺寸变化、不同内容图像。"
        "评价指标包括每张图像检测到的 SIFT 特征点数量，以及与 img1 基准图之间通过 Lowe ratio test 的匹配数量和匹配率。"
        "ratio test 阈值取 0.6，与发布包中 match.m 的默认设置保持一致。"
    )

    document.add_heading("二、第1题实验结果", level=1)
    document.add_paragraph("各图像变体的特征点检测结果如下。")
    _add_variant_table(document, result)
    document.add_paragraph("各变体与基准图之间的匹配统计如下。")
    _add_match_table(document, result)

    document.add_heading("三、效果图", level=1)
    _add_picture_if_exists(
        document,
        result.visualizations["keypoints_img1_base_1000"],
        "图1：img1 基准图上的部分 SIFT 特征点。圆圈表示尺度，短线表示主方向。",
    )
    _add_picture_if_exists(
        document,
        result.visualizations["match_img1_base_1000_to_img1_rotate_30"],
        "图2：基准图与旋转 30 度图像的匹配效果。",
    )
    _add_picture_if_exists(
        document,
        result.visualizations["match_img1_base_1000_to_img1_dark"],
        "图3：基准图与低亮度图像的匹配效果。",
    )
    _add_picture_if_exists(
        document,
        result.visualizations["match_img1_base_1000_to_img1_scale_700"],
        "图4：基准图与缩小图像的匹配效果。",
    )
    _add_picture_if_exists(
        document,
        result.visualizations["match_img1_base_1000_to_img2_base_1000"],
        "图5：基准图与不同内容图像的匹配效果。",
    )

    document.add_heading("四、实验结论", level=1)
    rotation_rate = _lookup_match_rate(result, ("img1_base_1000", "img1_rotate_30"))
    dark_rate = _lookup_match_rate(result, ("img1_base_1000", "img1_dark"))
    scale_rate = _lookup_match_rate(result, ("img1_base_1000", "img1_scale_700"))
    content_rate = _lookup_match_rate(result, ("img1_base_1000", "img2_base_1000"))
    document.add_paragraph(
        f"旋转实验中，旋转 30 度后仍有 {rotation_rate * 100:.2f}% 的相对匹配率，"
        "说明 SIFT 通过关键点主方向归一化获得了较好的旋转鲁棒性。匹配数下降主要来自旋转插值、边界裁剪和局部纹理变化。"
    )
    document.add_paragraph(
        f"光照实验中，低亮度图像的匹配率为 {dark_rate * 100:.2f}%。"
        "SIFT 描述子会做局部梯度统计和归一化，因此对整体亮度变化相对稳定；但当亮度降低导致局部对比度变弱时，检测到的稳定极值点会减少。"
    )
    document.add_paragraph(
        f"尺寸实验中，长边 700 的缩小图像匹配率为 {scale_rate * 100:.2f}%。"
        "低分辨率会减少细节和候选极值点，放大图像通常能产生更多关键点，但其中一部分由插值和重复纹理带来，并不一定都对应更高质量的匹配。"
    )
    document.add_paragraph(
        f"不同内容图像的匹配率为 {content_rate * 100:.2f}%，明显低于同一图像的几何或光照变换。"
        "这说明 SIFT 描述子具有较强区分性，ratio test 会过滤掉大量不可靠的最近邻。"
    )

    document.add_heading("五、第2题：DoG 差分金字塔与尺度不变性", level=1)
    document.add_paragraph(
        "SIFT 首先构建高斯尺度空间。设原图为 I(x,y)，高斯平滑后的图像为 "
        "L(x,y,sigma)=G(x,y,sigma)*I(x,y)。对同一 octave 内相邻尺度做差，得到 "
        "D(x,y,sigma)=L(x,y,k sigma)-L(x,y,sigma)，这就是 DoG 差分金字塔。"
    )
    document.add_paragraph(
        "DoG 可以近似尺度归一化的 LoG（Laplacian of Gaussian）响应，即高斯拉普拉斯算子。"
        "在实现上，DoG 只需要相邻两层高斯图像相减，比直接计算 LoG 更高效，因此适合在多尺度上搜索候选特征点。"
    )
    document.add_paragraph(
        "关键点检测时，算法会把每个像素与当前尺度、上一尺度、下一尺度中的 26 个邻域点比较，寻找三维空间 "
        "(x, y, sigma) 中的极大或极小值。若同一物理结构在图像缩放后出现，它会在不同 sigma 上产生相应的极值，"
        "因此算法能够为该结构选择一个特征尺度。"
    )
    document.add_paragraph(
        "尺度不变性的核心原因是：关键点不是只在固定像素尺度上检测，而是在尺度空间中检测，并把后续描述子窗口按关键点尺度进行归一化。"
        "这样，同一局部结构即使在图像中变大或变小，也会在其对应的特征尺度上被描述，得到可比较的描述子。"
        "再结合主方向分配，SIFT 同时获得了较好的尺度和旋转不变性。"
    )

    document.add_heading("六、说明", level=1)
    document.add_paragraph(
        "本报告和效果图由脚本自动生成。组员姓名和学号当前为占位内容，提交前请替换为真实信息。"
    )

    report_path.parent.mkdir(parents=True, exist_ok=True)
    document.save(report_path)
    return report_path


def _copy_source_tree(target_root: Path, input_root: Path) -> None:
    code_root = target_root / "code"
    code_root.mkdir(parents=True, exist_ok=True)

    copy_items = [
        (REPO_ROOT / "pyproject.toml", code_root / "pyproject.toml"),
        (PACKAGE_ROOT, code_root / "src" / "cv_course" / "experiments" / "exp02_sift"),
        (REPO_ROOT / "src" / "cv_course" / "__init__.py", code_root / "src" / "cv_course" / "__init__.py"),
        (
            REPO_ROOT / "src" / "cv_course" / "experiments" / "__init__.py",
            code_root / "src" / "cv_course" / "experiments" / "__init__.py",
        ),
        (REPO_ROOT / "tests" / "__init__.py", code_root / "tests" / "__init__.py"),
        (TEST_ROOT, code_root / "tests" / "exp02_sift"),
        (REPO_ROOT / "scripts" / "run_experiment_02.py", code_root / "scripts" / "run_experiment_02.py"),
        (REPO_ROOT / "README.md", code_root / "README.md"),
        (EXPERIMENT_ROOT / "README.md", code_root / "experiments" / "exp02_sift" / "README.md"),
        (input_root / "img1.jpg", code_root / "materials" / "img1.jpg"),
        (input_root / "img2.jpg", code_root / "materials" / "img2.jpg"),
        (input_root / "siftDemoV4", code_root / "materials" / "siftDemoV4"),
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
                ignore=shutil.ignore_patterns("__pycache__", "*.pyc", "tmp.key", "tmp.pgm"),
            )
        else:
            shutil.copy2(source_path, destination)


def _copy_figures(result: SiftExperimentResult, target_root: Path) -> None:
    figure_root = target_root / "figures"
    figure_root.mkdir(parents=True, exist_ok=True)
    for source_path in result.visualizations.values():
        if source_path.exists():
            shutil.copy2(source_path, figure_root / source_path.name)


def _write_readme(target_root: Path) -> None:
    readme_path = target_root / "README.txt"
    readme_path.write_text(
        "1. 报告文件：实验报告_SIFT算法实验.docx\n"
        "2. 统计结果：实验结果.json\n"
        "3. 效果图：figures 目录\n"
        "4. 源代码：code 目录\n"
        "5. 若需重新生成，请在仓库根目录运行 scripts/run_experiment_02.py --group-name OPT。\n"
        "6. 组员姓名和学号当前为占位内容，提交前请替换为真实信息。\n",
        encoding="utf-8",
    )


def _zip_folder(folder_path: Path, archive_path: Path) -> Path:
    archive_path.parent.mkdir(parents=True, exist_ok=True)
    with ZipFile(archive_path, "w", compression=ZIP_DEFLATED) as archive:
        for file_path in folder_path.rglob("*"):
            archive.write(file_path, file_path.relative_to(folder_path.parent))
    return archive_path


def build_submission_package(
    result: SiftExperimentResult,
    output_root: Path,
    input_root: Path,
    group_name: str = "OPT",
    members: list[str] | None = None,
) -> dict[str, Path]:
    members = members or ["姓名：待填写    学号：待填写"]
    submission_folder = output_root / f"实验2_{group_name}"
    if submission_folder.exists():
        shutil.rmtree(submission_folder)
    submission_folder.mkdir(parents=True, exist_ok=True)

    report_path = write_experiment_report(
        result,
        submission_folder / "实验报告_SIFT算法实验.docx",
        group_name,
        members,
    )
    result_path = write_experiment_summary(result, submission_folder / "实验结果.json")
    _copy_figures(result, submission_folder)
    _copy_source_tree(submission_folder, input_root)
    _write_readme(submission_folder)

    archive_path = _zip_folder(submission_folder, output_root / f"实验2_{group_name}.zip")
    return {
        "folder": submission_folder,
        "report": report_path,
        "results": result_path,
        "archive": archive_path,
    }
