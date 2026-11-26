# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

import argparse
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / "src"))

from cv_course.experiments.exp01_camera_calibration import (
    build_submission_package,
    calibrate_camera,
    get_experiment_data,
    write_calibration_results,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Run the camera calibration experiment.")
    parser.add_argument(
        "--group-name",
        default="待填写组名",
        help="Group name used in the generated submission folder and report.",
    )
    parser.add_argument(
        "--member",
        action="append",
        dest="members",
        help="Member info line, for example: 姓名：张三 学号：20250001. Repeatable.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    world_points, image_points = get_experiment_data()
    result = calibrate_camera(world_points, image_points)

    experiment_root = PROJECT_ROOT / "experiments" / "exp01_camera_calibration"
    artifacts_root = experiment_root / "artifacts"
    deliverables_root = experiment_root / "deliverables"

    result_path = write_calibration_results(result, artifacts_root / "calibration_results.json")
    package_paths = build_submission_package(
        result,
        deliverables_root,
        group_name=args.group_name,
        members=args.members,
    )

    print(f"Calibration results written to: {result_path.resolve()}")
    print(f"Submission folder: {package_paths['folder'].resolve()}")
    print(f"Report path: {package_paths['report'].resolve()}")
    print(f"Archive path: {package_paths['archive'].resolve()}")


if __name__ == "__main__":
    main()
