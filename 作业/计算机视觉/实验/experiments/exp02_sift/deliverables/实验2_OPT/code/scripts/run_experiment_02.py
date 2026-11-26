# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

import argparse
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / "src"))

from cv_course.experiments.exp02_sift import (
    build_submission_package,
    run_sift_experiment,
    write_experiment_summary,
)


def _resolve_input_root(explicit_input_root: str | None) -> Path:
    if explicit_input_root:
        return Path(explicit_input_root).resolve()

    candidates = [
        PROJECT_ROOT / "experiments" / "exp02_sift" / "materials",
        PROJECT_ROOT / "实验二发布",
        PROJECT_ROOT / "materials",
    ]
    for candidate in candidates:
        if (candidate / "img1.jpg").exists() and (candidate / "img2.jpg").exists():
            return candidate
    raise FileNotFoundError("Cannot find experiment 02 inputs. Expected 实验二发布/ or materials/.")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run the SIFT robustness experiment.")
    parser.add_argument(
        "--group-name",
        default="OPT",
        help="Group name used in the generated submission folder and report.",
    )
    parser.add_argument(
        "--member",
        action="append",
        dest="members",
        help="Member info line, for example: 姓名：张三 学号：20250001. Repeatable.",
    )
    parser.add_argument(
        "--input-root",
        help="Folder containing img1.jpg, img2.jpg, and siftDemoV4.",
    )
    parser.add_argument(
        "--sift-executable",
        help="Path to Lowe's SIFT executable. Defaults to <input-root>/siftDemoV4/siftWin32.exe.",
    )
    parser.add_argument(
        "--ratio-threshold",
        type=float,
        default=0.6,
        help="Lowe ratio-test threshold used for feature matching.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    input_root = _resolve_input_root(args.input_root)
    sift_executable = (
        Path(args.sift_executable).resolve()
        if args.sift_executable
        else input_root / "siftDemoV4" / "siftWin32.exe"
    )

    experiment_root = PROJECT_ROOT / "experiments" / "exp02_sift"
    artifacts_root = experiment_root / "artifacts"
    deliverables_root = experiment_root / "deliverables"

    result = run_sift_experiment(
        input_root=input_root,
        sift_executable=sift_executable,
        output_root=artifacts_root,
        ratio_threshold=args.ratio_threshold,
    )
    summary_path = write_experiment_summary(result, artifacts_root / "sift_experiment_results.json")
    package_paths = build_submission_package(
        result,
        deliverables_root,
        input_root=input_root,
        group_name=args.group_name,
        members=args.members,
    )

    print(f"Input root: {input_root.resolve()}")
    print(f"SIFT executable: {sift_executable.resolve()}")
    print(f"Experiment summary: {summary_path.resolve()}")
    print(f"Submission folder: {package_paths['folder'].resolve()}")
    print(f"Report path: {package_paths['report'].resolve()}")
    print(f"Archive path: {package_paths['archive'].resolve()}")


if __name__ == "__main__":
    main()
