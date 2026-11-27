from __future__ import annotations

import argparse
import json
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from PIL import Image, ImageDraw, ImageFilter


RNG_SEED = 20260611


@dataclass(frozen=True)
class RegistrationResult:
    inliers: int
    total_matches: int
    median_reprojection_error: float
    corner_transfer_error: float
    estimated_homography: list[list[float]]


def apply_homography(points: np.ndarray, h_matrix: np.ndarray) -> np.ndarray:
    homogeneous = np.c_[points, np.ones(len(points))]
    projected = homogeneous @ h_matrix.T
    denominator = projected[:, 2:3]
    with np.errstate(divide="ignore", invalid="ignore"):
        projected = np.divide(projected[:, :2], denominator)
    return projected


def normalize_points(points: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    centroid = points.mean(axis=0)
    shifted = points - centroid
    mean_dist = np.sqrt((shifted**2).sum(axis=1)).mean()
    scale = np.sqrt(2.0) / max(mean_dist, 1e-9)
    transform = np.array(
        [
            [scale, 0.0, -scale * centroid[0]],
            [0.0, scale, -scale * centroid[1]],
            [0.0, 0.0, 1.0],
        ]
    )
    normalized = apply_homography(points, transform)
    return normalized, transform


def estimate_homography(src_points: np.ndarray, dst_points: np.ndarray) -> np.ndarray:
    if len(src_points) < 4:
        raise ValueError("At least four correspondences are required.")

    src_norm, src_transform = normalize_points(src_points)
    dst_norm, dst_transform = normalize_points(dst_points)

    rows = []
    for (x_src, y_src), (x_dst, y_dst) in zip(src_norm, dst_norm):
        rows.append([-x_src, -y_src, -1.0, 0.0, 0.0, 0.0, x_dst * x_src, x_dst * y_src, x_dst])
        rows.append([0.0, 0.0, 0.0, -x_src, -y_src, -1.0, y_dst * x_src, y_dst * y_src, y_dst])

    _, _, vt_matrix = np.linalg.svd(np.asarray(rows))
    h_norm = vt_matrix[-1].reshape(3, 3)
    h_matrix = np.linalg.inv(dst_transform) @ h_norm @ src_transform
    if abs(h_matrix[2, 2]) < 1e-12:
        raise np.linalg.LinAlgError("Degenerate homography normalization.")
    return h_matrix / h_matrix[2, 2]


def ransac_homography(
    src_points: np.ndarray,
    dst_points: np.ndarray,
    *,
    threshold: float = 3.0,
    iterations: int = 800,
    rng: np.random.Generator,
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    best_inliers = np.zeros(len(src_points), dtype=bool)
    best_h = np.eye(3)
    indices = np.arange(len(src_points))

    for _ in range(iterations):
        sample = rng.choice(indices, size=4, replace=False)
        try:
            h_candidate = estimate_homography(src_points[sample], dst_points[sample])
        except np.linalg.LinAlgError:
            continue
        errors = np.linalg.norm(apply_homography(src_points, h_candidate) - dst_points, axis=1)
        if not np.isfinite(errors).all():
            continue
        inliers = errors < threshold
        if inliers.sum() > best_inliers.sum():
            best_inliers = inliers
            best_h = h_candidate

    if best_inliers.sum() >= 4:
        best_h = estimate_homography(src_points[best_inliers], dst_points[best_inliers])
        if not np.isfinite(best_h).all():
            raise np.linalg.LinAlgError("RANSAC produced a non-finite homography.")
    else:
        raise RuntimeError("RANSAC failed to find at least four inlier correspondences.")

    reprojection_errors = np.linalg.norm(apply_homography(src_points, best_h) - dst_points, axis=1)
    return best_h, best_inliers, reprojection_errors


def warp_perspective(image: np.ndarray, h_matrix: np.ndarray, output_size: tuple[int, int]) -> np.ndarray:
    out_w, out_h = output_size
    inv_h = np.linalg.inv(h_matrix)
    yy, xx = np.mgrid[0:out_h, 0:out_w]
    target = np.stack([xx.ravel(), yy.ravel()], axis=1)
    source = apply_homography(target, inv_h)
    x_src = source[:, 0]
    y_src = source[:, 1]

    valid = (
        (x_src >= 0)
        & (x_src < image.shape[1] - 1)
        & (y_src >= 0)
        & (y_src < image.shape[0] - 1)
    )

    warped = np.zeros((out_h * out_w, image.shape[2]), dtype=np.float32)
    x0 = np.floor(x_src[valid]).astype(int)
    y0 = np.floor(y_src[valid]).astype(int)
    dx = (x_src[valid] - x0)[:, None]
    dy = (y_src[valid] - y0)[:, None]

    top = (1 - dx) * image[y0, x0] + dx * image[y0, x0 + 1]
    bottom = (1 - dx) * image[y0 + 1, x0] + dx * image[y0 + 1, x0 + 1]
    warped[valid] = (1 - dy) * top + dy * bottom
    return warped.reshape(out_h, out_w, image.shape[2]).clip(0, 255).astype(np.uint8)


def make_scene(size: tuple[int, int] = (320, 240)) -> tuple[np.ndarray, np.ndarray]:
    width, height = size
    image = Image.new("RGB", size, "white")
    mask = Image.new("L", size, 0)
    draw = ImageDraw.Draw(image)
    mask_draw = ImageDraw.Draw(mask)

    for x_val in range(0, width, 32):
        draw.line((x_val, 0, x_val, height), fill=(225, 232, 240), width=1)
    for y_val in range(0, height, 32):
        draw.line((0, y_val, width, y_val), fill=(225, 232, 240), width=1)

    draw.rectangle((58, 50, 155, 146), fill=(46, 116, 181), outline=(12, 52, 91), width=3)
    draw.ellipse((180, 62, 268, 150), fill=(238, 108, 77), outline=(133, 42, 35), width=3)
    draw.polygon([(96, 182), (148, 166), (205, 206), (80, 216)], fill=(62, 150, 112))
    mask_draw.rectangle((58, 50, 155, 146), fill=255)
    mask_draw.ellipse((180, 62, 268, 150), fill=255)
    mask_draw.polygon([(96, 182), (148, 166), (205, 206), (80, 216)], fill=255)
    return np.asarray(image), np.asarray(mask)


def run_registration(output_dir: Path, rng: np.random.Generator) -> RegistrationResult:
    scene, _ = make_scene()
    true_h = np.array(
        [
            [0.94, 0.13, 18.0],
            [-0.08, 1.03, 21.0],
            [0.00025, -0.00055, 1.0],
        ]
    )
    warped = warp_perspective(scene, true_h, (360, 280))

    grid_x, grid_y = np.meshgrid(np.linspace(40, 280, 7), np.linspace(35, 205, 5))
    src_points = np.stack([grid_x.ravel(), grid_y.ravel()], axis=1)
    dst_points = apply_homography(src_points, true_h)
    dst_points += rng.normal(0.0, 0.9, size=dst_points.shape)

    outlier_count = 8
    outlier_indices = rng.choice(np.arange(len(dst_points)), size=outlier_count, replace=False)
    dst_points[outlier_indices] += rng.normal(0.0, 42.0, size=(outlier_count, 2))

    estimated_h, inliers, errors = ransac_homography(src_points, dst_points, rng=rng)

    corners = np.array([[0, 0], [319, 0], [319, 239], [0, 239]], dtype=float)
    corner_transfer = float(
        np.linalg.norm(apply_homography(corners, estimated_h) - apply_homography(corners, true_h), axis=1).mean()
    )

    overlay = Image.fromarray(warped)
    draw = ImageDraw.Draw(overlay)
    projected = apply_homography(src_points, estimated_h)
    for idx, (x_val, y_val) in enumerate(projected):
        color = (40, 170, 90) if inliers[idx] else (210, 60, 60)
        draw.ellipse((x_val - 3, y_val - 3, x_val + 3, y_val + 3), fill=color)
    Image.fromarray(scene).save(output_dir / "registration_source.png")
    overlay.save(output_dir / "registration_ransac_overlay.png")

    return RegistrationResult(
        inliers=int(inliers.sum()),
        total_matches=int(len(src_points)),
        median_reprojection_error=float(np.median(errors[inliers])),
        corner_transfer_error=corner_transfer,
        estimated_homography=np.round(estimated_h, 5).tolist(),
    )


def mask_iou(predicted: np.ndarray, reference: np.ndarray) -> float:
    pred_bool = predicted.astype(bool)
    ref_bool = reference.astype(bool)
    intersection = np.logical_and(pred_bool, ref_bool).sum()
    union = np.logical_or(pred_bool, ref_bool).sum()
    return float(intersection / max(union, 1))


def run_robustness(output_dir: Path, rng: np.random.Generator) -> dict[str, float]:
    scene, reference_mask = make_scene()
    scene_float = scene.astype(np.float32)
    shared_noise = rng.normal(0.0, 18.0, scene.shape[:2])[:, :, None]

    variants: dict[str, np.ndarray] = {
        "clean": scene_float,
        "low_light": scene_float * 0.62,
        "gaussian_noise": np.clip(scene_float + shared_noise, 0, 255),
        "blur": np.asarray(Image.fromarray(scene).filter(ImageFilter.GaussianBlur(radius=2.0)), dtype=np.float32),
    }

    results: dict[str, float] = {}
    panels = []
    for name, variant in variants.items():
        channel_spread = variant.max(axis=2) - variant.min(axis=2)
        brightness = variant.mean(axis=2)
        predicted = (channel_spread > 35) & (brightness < 245)
        results[name] = mask_iou(predicted, reference_mask > 0)
        panel = Image.fromarray(np.where(predicted, 255, 0).astype(np.uint8)).convert("RGB")
        draw = ImageDraw.Draw(panel)
        draw.rectangle((0, 0, 138, 22), fill=(255, 255, 255))
        draw.text((6, 5), f"{name}: IoU={results[name]:.3f}", fill=(0, 0, 0))
        panels.append(panel)

    panel_width = sum(panel.width for panel in panels)
    panel = Image.new("RGB", (panel_width, panels[0].height), "white")
    cursor = 0
    for item in panels:
        panel.paste(item, (cursor, 0))
        cursor += item.width
    panel.save(output_dir / "robustness_masks.png")
    return results


def main() -> None:
    parser = argparse.ArgumentParser(description="Minimal CV report experiment: homography RANSAC and robustness metrics.")
    parser.add_argument("--out", type=Path, default=Path(__file__).resolve().parents[1] / "artifacts")
    args = parser.parse_args()
    args.out.mkdir(parents=True, exist_ok=True)

    rng = np.random.default_rng(RNG_SEED)
    registration = run_registration(args.out, rng)
    robustness = run_robustness(args.out, rng)
    payload = {
        "seed": RNG_SEED,
        "registration": registration.__dict__,
        "robustness_iou": robustness,
        "artifacts": [
            "registration_source.png",
            "registration_ransac_overlay.png",
            "robustness_masks.png",
        ],
    }
    with (args.out / "cv_minimal_lab_results.json").open("w", encoding="utf-8") as file_obj:
        json.dump(payload, file_obj, ensure_ascii=False, indent=2, allow_nan=False)
    print(json.dumps(payload, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
