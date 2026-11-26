# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

import json
import math
import subprocess
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw, ImageEnhance


@dataclass(frozen=True)
class VariantSpec:
    name: str
    label: str
    category: str
    source_file: str
    max_side: int
    rotate_degrees: float | None = None
    brightness: float = 1.0
    contrast: float = 1.0


@dataclass(frozen=True)
class FeatureSet:
    image_name: str
    width: int
    height: int
    locations: np.ndarray
    descriptors: np.ndarray

    @property
    def keypoint_count(self) -> int:
        return int(self.locations.shape[0])


@dataclass(frozen=True)
class DescriptorMatch:
    query_index: int
    train_index: int
    nearest_distance: float
    second_distance: float

    @property
    def ratio(self) -> float:
        if self.second_distance == 0.0:
            return math.inf
        return self.nearest_distance / self.second_distance


@dataclass(frozen=True)
class SiftExperimentResult:
    feature_sets: list[FeatureSet]
    matches: dict[tuple[str, str], list[DescriptorMatch]]
    summary: dict[str, object]
    variant_images: dict[str, Path]
    key_files: dict[str, Path]
    visualizations: dict[str, Path]


def build_default_variant_specs() -> list[VariantSpec]:
    return [
        VariantSpec(
            name="img1_base_1000",
            label="img1 基准图（长边 1000）",
            category="baseline",
            source_file="img1.jpg",
            max_side=1000,
        ),
        VariantSpec(
            name="img1_rotate_30",
            label="img1 旋转 30 度",
            category="rotation",
            source_file="img1.jpg",
            max_side=1000,
            rotate_degrees=30.0,
        ),
        VariantSpec(
            name="img1_dark",
            label="img1 低亮度（0.55x）",
            category="illumination",
            source_file="img1.jpg",
            max_side=1000,
            brightness=0.55,
        ),
        VariantSpec(
            name="img1_bright",
            label="img1 高亮度（1.35x）",
            category="illumination",
            source_file="img1.jpg",
            max_side=1000,
            brightness=1.35,
        ),
        VariantSpec(
            name="img1_scale_700",
            label="img1 缩放到长边 700",
            category="scale",
            source_file="img1.jpg",
            max_side=700,
        ),
        VariantSpec(
            name="img1_scale_1200",
            label="img1 缩放到长边 1200",
            category="scale",
            source_file="img1.jpg",
            max_side=1200,
        ),
        VariantSpec(
            name="img2_base_1000",
            label="img2 不同内容图（长边 1000）",
            category="content",
            source_file="img2.jpg",
            max_side=1000,
        ),
    ]


def _resize_to_max_side(image: Image.Image, max_side: int) -> Image.Image:
    width, height = image.size
    current_max = max(width, height)
    if current_max == max_side:
        return image.copy()
    scale = max_side / current_max
    target_size = (max(1, round(width * scale)), max(1, round(height * scale)))
    return image.resize(target_size, Image.Resampling.LANCZOS)


def _prepare_variant_image(input_root: Path, spec: VariantSpec) -> Image.Image:
    source_path = input_root / spec.source_file
    if not source_path.exists():
        raise FileNotFoundError(f"Input image not found: {source_path}")

    image = Image.open(source_path).convert("RGB")
    image = _resize_to_max_side(image, spec.max_side)

    if spec.rotate_degrees is not None:
        image = image.rotate(spec.rotate_degrees, resample=Image.Resampling.BICUBIC, expand=True)
        if max(image.size) > spec.max_side:
            image = _resize_to_max_side(image, spec.max_side)

    if spec.brightness != 1.0:
        image = ImageEnhance.Brightness(image).enhance(spec.brightness)
    if spec.contrast != 1.0:
        image = ImageEnhance.Contrast(image).enhance(spec.contrast)

    return image.convert("L")


def _run_sift_binary(pgm_path: Path, key_path: Path, sift_executable: Path) -> None:
    if not sift_executable.exists():
        raise FileNotFoundError(f"SIFT executable not found: {sift_executable}")

    with pgm_path.open("rb") as stdin, key_path.open("wb") as stdout:
        result = subprocess.run(
            [str(sift_executable)],
            stdin=stdin,
            stdout=stdout,
            stderr=subprocess.PIPE,
            cwd=sift_executable.parent,
            check=False,
        )
    if result.returncode != 0:
        stderr = result.stderr.decode(errors="replace").strip()
        raise RuntimeError(f"SIFT failed for {pgm_path.name}: {stderr}")


def parse_key_file(key_path: Path, image_name: str, image_size: tuple[int, int]) -> FeatureSet:
    tokens = key_path.read_text(encoding="utf-8", errors="replace").split()
    if len(tokens) < 2:
        raise ValueError(f"Invalid key file header: {key_path}")

    keypoint_count = int(tokens[0])
    descriptor_length = int(tokens[1])
    if descriptor_length != 128:
        raise ValueError(f"Unexpected descriptor length {descriptor_length}; expected 128.")

    expected_tokens = 2 + keypoint_count * (4 + descriptor_length)
    if len(tokens) < expected_tokens:
        raise ValueError(
            f"Incomplete key file {key_path}: expected at least {expected_tokens} tokens, got {len(tokens)}."
        )

    locations = np.zeros((keypoint_count, 4), dtype=float)
    descriptors = np.zeros((keypoint_count, descriptor_length), dtype=float)
    cursor = 2
    for index in range(keypoint_count):
        locations[index] = [float(value) for value in tokens[cursor : cursor + 4]]
        cursor += 4
        descriptor = np.array(
            [float(value) for value in tokens[cursor : cursor + descriptor_length]],
            dtype=float,
        )
        cursor += descriptor_length
        norm = np.linalg.norm(descriptor)
        descriptors[index] = descriptor / norm if norm > 0.0 else descriptor

    width, height = image_size
    return FeatureSet(
        image_name=image_name,
        width=width,
        height=height,
        locations=locations,
        descriptors=descriptors,
    )


def _normalize_descriptor_rows(descriptors: np.ndarray) -> np.ndarray:
    descriptors = np.asarray(descriptors, dtype=float)
    if descriptors.size == 0:
        return descriptors.reshape((descriptors.shape[0], -1))
    norms = np.linalg.norm(descriptors, axis=1, keepdims=True)
    return np.divide(descriptors, norms, out=np.zeros_like(descriptors), where=norms > 0.0)


def match_descriptors(
    query_descriptors: np.ndarray,
    train_descriptors: np.ndarray,
    ratio_threshold: float = 0.6,
) -> list[DescriptorMatch]:
    query = _normalize_descriptor_rows(query_descriptors)
    train = _normalize_descriptor_rows(train_descriptors)
    if len(query) == 0 or len(train) < 2:
        return []

    matches: list[DescriptorMatch] = []
    for query_index, descriptor in enumerate(query):
        distances = np.linalg.norm(train - descriptor, axis=1)
        nearest_two = np.argpartition(distances, 1)[:2]
        nearest_two = nearest_two[np.argsort(distances[nearest_two])]
        nearest_index, second_index = int(nearest_two[0]), int(nearest_two[1])
        nearest_distance = float(distances[nearest_index])
        second_distance = float(distances[second_index])
        if second_distance > 0.0 and nearest_distance < ratio_threshold * second_distance:
            matches.append(
                DescriptorMatch(
                    query_index=query_index,
                    train_index=nearest_index,
                    nearest_distance=nearest_distance,
                    second_distance=second_distance,
                )
            )
    return matches


def draw_keypoint_overview(
    image_path: Path,
    feature_set: FeatureSet,
    output_path: Path,
    max_keypoints: int = 250,
) -> Path:
    image = Image.open(image_path).convert("RGB")
    draw = ImageDraw.Draw(image)
    locations = feature_set.locations[:max_keypoints]
    for row, col, scale, orientation in locations:
        radius = max(2.0, min(8.0, float(scale) * 0.7))
        x_coord = float(col)
        y_coord = float(row)
        draw.ellipse(
            (x_coord - radius, y_coord - radius, x_coord + radius, y_coord + radius),
            outline=(255, 64, 64),
            width=2,
        )
        line_length = radius * 2.2
        draw.line(
            (
                x_coord,
                y_coord,
                x_coord + line_length * math.cos(float(orientation)),
                y_coord + line_length * math.sin(float(orientation)),
            ),
            fill=(64, 180, 255),
            width=1,
        )
    output_path.parent.mkdir(parents=True, exist_ok=True)
    image.save(output_path)
    return output_path


def draw_match_visualization(
    query_image_path: Path,
    train_image_path: Path,
    query_features: FeatureSet,
    train_features: FeatureSet,
    matches: list[DescriptorMatch],
    output_path: Path,
    max_matches: int = 80,
) -> Path:
    query_image = Image.open(query_image_path).convert("RGB")
    train_image = Image.open(train_image_path).convert("RGB")
    combined = Image.new(
        "RGB",
        (query_image.width + train_image.width, max(query_image.height, train_image.height)),
        color=(255, 255, 255),
    )
    combined.paste(query_image, (0, 0))
    combined.paste(train_image, (query_image.width, 0))

    draw = ImageDraw.Draw(combined)
    ordered_matches = sorted(matches, key=lambda match: match.ratio)[:max_matches]
    palette = [
        (242, 85, 85),
        (48, 148, 255),
        (34, 168, 98),
        (222, 158, 46),
        (155, 92, 225),
        (12, 151, 166),
    ]
    for match_index, match in enumerate(ordered_matches):
        q_row, q_col = query_features.locations[match.query_index, :2]
        t_row, t_col = train_features.locations[match.train_index, :2]
        color = palette[match_index % len(palette)]
        start = (float(q_col), float(q_row))
        end = (float(t_col) + query_image.width, float(t_row))
        draw.line((start, end), fill=color, width=1)
        draw.ellipse((start[0] - 3, start[1] - 3, start[0] + 3, start[1] + 3), fill=color)
        draw.ellipse((end[0] - 3, end[1] - 3, end[0] + 3, end[1] + 3), fill=color)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    combined.save(output_path)
    return output_path


def summarize_experiment(
    feature_sets: list[FeatureSet],
    match_counts: dict[tuple[str, str], int],
) -> dict[str, object]:
    feature_by_name = {feature_set.image_name: feature_set for feature_set in feature_sets}
    variants = [
        {
            "name": feature_set.image_name,
            "width": feature_set.width,
            "height": feature_set.height,
            "keypoint_count": feature_set.keypoint_count,
        }
        for feature_set in feature_sets
    ]

    matches = []
    for (query_name, train_name), match_count in match_counts.items():
        query_count = feature_by_name[query_name].keypoint_count
        train_count = feature_by_name[train_name].keypoint_count
        denominator = min(query_count, train_count)
        matches.append(
            {
                "query": query_name,
                "train": train_name,
                "match_count": int(match_count),
                "match_rate": round(float(match_count / denominator), 6) if denominator else 0.0,
                "query_keypoint_count": query_count,
                "train_keypoint_count": train_count,
            }
        )

    return {"variants": variants, "matches": matches}


def _default_match_pairs() -> list[tuple[str, str]]:
    return [
        ("img1_base_1000", "img1_rotate_30"),
        ("img1_base_1000", "img1_dark"),
        ("img1_base_1000", "img1_bright"),
        ("img1_base_1000", "img1_scale_700"),
        ("img1_base_1000", "img1_scale_1200"),
        ("img1_base_1000", "img2_base_1000"),
    ]


def run_sift_experiment(
    input_root: Path,
    sift_executable: Path,
    output_root: Path,
    variants: list[VariantSpec] | None = None,
    ratio_threshold: float = 0.6,
) -> SiftExperimentResult:
    variants = variants or build_default_variant_specs()
    image_root = output_root / "variant_images"
    key_root = output_root / "keys"
    figure_root = output_root / "figures"
    image_root.mkdir(parents=True, exist_ok=True)
    key_root.mkdir(parents=True, exist_ok=True)
    figure_root.mkdir(parents=True, exist_ok=True)

    feature_sets: list[FeatureSet] = []
    variant_images: dict[str, Path] = {}
    key_files: dict[str, Path] = {}
    visualizations: dict[str, Path] = {}

    for spec in variants:
        image = _prepare_variant_image(input_root, spec)
        pgm_path = image_root / f"{spec.name}.pgm"
        image.save(pgm_path)
        key_path = key_root / f"{spec.name}.key"
        _run_sift_binary(pgm_path, key_path, sift_executable)

        feature_set = parse_key_file(key_path, spec.name, image.size)
        feature_sets.append(feature_set)
        variant_images[spec.name] = pgm_path
        key_files[spec.name] = key_path

    feature_by_name = {feature_set.image_name: feature_set for feature_set in feature_sets}
    matches: dict[tuple[str, str], list[DescriptorMatch]] = {}
    for query_name, train_name in _default_match_pairs():
        query_features = feature_by_name[query_name]
        train_features = feature_by_name[train_name]
        pair_matches = match_descriptors(
            query_features.descriptors,
            train_features.descriptors,
            ratio_threshold=ratio_threshold,
        )
        matches[(query_name, train_name)] = pair_matches
        visualizations[f"match_{query_name}_to_{train_name}"] = draw_match_visualization(
            variant_images[query_name],
            variant_images[train_name],
            query_features,
            train_features,
            pair_matches,
            figure_root / f"match_{query_name}_to_{train_name}.png",
        )

    for feature_set in feature_sets:
        visualizations[f"keypoints_{feature_set.image_name}"] = draw_keypoint_overview(
            variant_images[feature_set.image_name],
            feature_set,
            figure_root / f"keypoints_{feature_set.image_name}.png",
        )

    summary = summarize_experiment(
        feature_sets=feature_sets,
        match_counts={pair: len(pair_matches) for pair, pair_matches in matches.items()},
    )
    return SiftExperimentResult(
        feature_sets=feature_sets,
        matches=matches,
        summary=summary,
        variant_images=variant_images,
        key_files=key_files,
        visualizations=visualizations,
    )


def write_experiment_summary(result: SiftExperimentResult, output_path: Path) -> Path:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(
        json.dumps(result.summary, indent=2, ensure_ascii=False),
        encoding="utf-8",
    )
    return output_path
