# Original Author: GitHub @leowrs (https://github.com/leowrs)
import json
import sys
import tempfile
import unittest
from pathlib import Path

import numpy as np

PROJECT_ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PROJECT_ROOT / "src"))

from cv_course.experiments.exp01_camera_calibration import (
    build_submission_package,
    calibrate_camera,
    decompose_projection_matrix,
    estimate_projection_matrix,
    get_experiment_data,
    project_points,
    write_calibration_results,
)


class CameraCalibrationTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.world_points, self.image_points = get_experiment_data()

    def test_estimate_projection_matrix_reprojects_given_points(self) -> None:
        projection_matrix = estimate_projection_matrix(
            self.world_points,
            self.image_points,
        )

        projected = project_points(projection_matrix, self.world_points)
        error = np.linalg.norm(projected - self.image_points, axis=1)

        self.assertEqual(projection_matrix.shape, (3, 4))
        self.assertLess(error.mean(), 1e-3)
        self.assertLess(error.max(), 1e-3)

    def test_decompose_projection_matrix_returns_valid_krt(self) -> None:
        projection_matrix = estimate_projection_matrix(
            self.world_points,
            self.image_points,
        )

        intrinsic, rotation, translation, scale = decompose_projection_matrix(
            projection_matrix,
        )

        self.assertAlmostEqual(intrinsic[2, 2], 1.0, places=6)
        self.assertTrue(np.allclose(np.tril(intrinsic, -1), 0.0, atol=1e-8))
        self.assertTrue(np.all(np.diag(intrinsic) > 0.0))
        self.assertTrue(np.allclose(rotation @ rotation.T, np.eye(3), atol=1e-6))
        self.assertAlmostEqual(np.linalg.det(rotation), 1.0, places=6)
        rebuilt = scale * intrinsic @ np.column_stack((rotation, translation))
        self.assertTrue(np.allclose(rebuilt, projection_matrix, atol=1e-6))

    def test_calibrate_camera_matches_expected_numeric_solution(self) -> None:
        result = calibrate_camera(self.world_points, self.image_points)

        expected_intrinsic = np.array(
            [
                [1.30005563, 0.00004248, 0.60002308],
                [0.0, 1.19994629, 0.40005341],
                [0.0, 0.0, 1.0],
            ]
        )
        expected_translation = np.array([3.19934183, 14.50046081, 6.70002199])

        self.assertTrue(
            np.allclose(result.intrinsic_matrix, expected_intrinsic, atol=1e-4)
        )
        self.assertTrue(np.allclose(result.translation_vector, expected_translation, atol=1e-4))
        self.assertLess(result.mean_reprojection_error, 1e-3)

    def test_write_calibration_results_exports_json(self) -> None:
        result = calibrate_camera(self.world_points, self.image_points)

        with tempfile.TemporaryDirectory() as temp_dir:
            output_path = Path(temp_dir) / "results.json"
            write_calibration_results(result, output_path)

            self.assertTrue(output_path.exists())
            payload = json.loads(output_path.read_text(encoding="utf-8"))
            self.assertIn("projection_matrix", payload)
            self.assertIn("intrinsic_matrix", payload)
            self.assertAlmostEqual(payload["mean_reprojection_error"], result.mean_reprojection_error)

    def test_build_submission_package_creates_report_and_zip(self) -> None:
        result = calibrate_camera(self.world_points, self.image_points)

        with tempfile.TemporaryDirectory() as temp_dir:
            paths = build_submission_package(
                result,
                Path(temp_dir),
                group_name="测试组",
                members=["张三 20250001", "李四 20250002"],
            )

            self.assertTrue(paths["folder"].exists())
            self.assertTrue(paths["report"].exists())
            self.assertTrue(paths["archive"].exists())


if __name__ == "__main__":
    unittest.main()
