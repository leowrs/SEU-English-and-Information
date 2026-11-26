# Original Author: GitHub @leowrs (https://github.com/leowrs)
import sys
import tempfile
import unittest
from pathlib import Path

import numpy as np

PROJECT_ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PROJECT_ROOT / "src"))

from cv_course.experiments.exp02_sift import (
    FeatureSet,
    build_default_variant_specs,
    match_descriptors,
    parse_key_file,
    summarize_experiment,
)


def _descriptor(active_index: int) -> list[int]:
    values = [0] * 128
    values[active_index] = 255
    return values


class SiftExperimentTestCase(unittest.TestCase):
    def test_parse_key_file_reads_locations_and_normalized_descriptors(self) -> None:
        key_text = (
            "2 128\n"
            "10.0 20.0 1.5 0.25\n"
            + " ".join(str(value) for value in _descriptor(0))
            + "\n"
            "30.0 40.0 2.5 -0.5\n"
            + " ".join(str(value) for value in _descriptor(1))
            + "\n"
        )

        with tempfile.TemporaryDirectory() as temp_dir:
            key_path = Path(temp_dir) / "sample.key"
            key_path.write_text(key_text, encoding="utf-8")

            feature_set = parse_key_file(key_path, image_name="sample", image_size=(100, 80))

        self.assertEqual(feature_set.keypoint_count, 2)
        self.assertEqual(feature_set.descriptors.shape, (2, 128))
        self.assertEqual(feature_set.locations.shape, (2, 4))
        self.assertTrue(np.allclose(np.linalg.norm(feature_set.descriptors, axis=1), 1.0))
        self.assertEqual(feature_set.width, 100)
        self.assertEqual(feature_set.height, 80)

    def test_match_descriptors_keeps_only_ratio_test_matches(self) -> None:
        query = np.array(
            [
                [1.0, 0.0, 0.0],
                [0.0, 1.0, 0.0],
                [0.70, 0.70, 0.0],
            ]
        )
        train = np.array(
            [
                [1.0, 0.0, 0.0],
                [0.9, 0.1, 0.0],
                [0.0, 1.0, 0.0],
                [0.1, 0.9, 0.0],
                [0.72, 0.68, 0.0],
                [0.68, 0.72, 0.0],
            ]
        )

        matches = match_descriptors(query, train, ratio_threshold=0.6)

        self.assertEqual([(match.query_index, match.train_index) for match in matches], [(0, 0), (1, 2)])

    def test_match_descriptors_handles_exactly_two_candidates(self) -> None:
        query = np.array([[1.0, 0.0, 0.0]])
        train = np.array(
            [
                [1.0, 0.0, 0.0],
                [0.0, 1.0, 0.0],
            ]
        )

        matches = match_descriptors(query, train, ratio_threshold=0.6)

        self.assertEqual(len(matches), 1)
        self.assertEqual(matches[0].train_index, 0)

    def test_default_variants_cover_assignment_factors(self) -> None:
        variants = build_default_variant_specs()
        categories = {variant.category for variant in variants}

        self.assertIn("baseline", categories)
        self.assertIn("rotation", categories)
        self.assertIn("illumination", categories)
        self.assertIn("scale", categories)
        self.assertIn("content", categories)

    def test_summarize_experiment_calculates_match_rates(self) -> None:
        base = FeatureSet(
            image_name="img1_base",
            width=100,
            height=80,
            locations=np.zeros((10, 4), dtype=float),
            descriptors=np.zeros((10, 128), dtype=float),
        )
        rotated = FeatureSet(
            image_name="img1_rotated",
            width=100,
            height=80,
            locations=np.zeros((8, 4), dtype=float),
            descriptors=np.zeros((8, 128), dtype=float),
        )

        summary = summarize_experiment(
            feature_sets=[base, rotated],
            match_counts={("img1_base", "img1_rotated"): 4},
        )

        self.assertEqual(summary["variants"][0]["keypoint_count"], 10)
        self.assertEqual(summary["matches"][0]["match_count"], 4)
        self.assertAlmostEqual(summary["matches"][0]["match_rate"], 0.5)


if __name__ == "__main__":
    unittest.main()
