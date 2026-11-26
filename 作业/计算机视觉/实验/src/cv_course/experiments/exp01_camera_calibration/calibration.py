# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

from dataclasses import dataclass

import numpy as np


WORLD_POINTS = np.array(
    [
        [9.9613, 0.7818, 4.4268],
        [1.0665, 9.6190, 0.0463],
        [7.7491, 8.1730, 8.6869],
        [0.8444, 3.9978, 2.5987],
        [8.0007, 4.3141, 9.1065],
        [1.8185, 2.6380, 1.4554],
        [1.3607, 8.6929, 5.7970],
        [5.4986, 1.4495, 8.5303],
        [6.2206, 3.5095, 5.1325],
        [4.0181, 0.7597, 2.3992],
    ],
    dtype=float,
)

IMAGE_POINTS = np.array(
    [
        [1.4360, -7.2422],
        [-8.9475, -22.4474],
        [-0.8486, -1.4078],
        [3.4099, 6.4703],
        [-1.2302, -1.9620],
        [2.1849, 5.4741],
        [-7.5374, -10.0774],
        [14.2124, 17.6236],
        [-4.3479, -12.9624],
        [1.5071, 5.0049],
    ],
    dtype=float,
)


@dataclass(frozen=True)
class CalibrationResult:
    projection_matrix: np.ndarray
    intrinsic_matrix: np.ndarray
    rotation_matrix: np.ndarray
    translation_vector: np.ndarray
    camera_center: np.ndarray
    scale_factor: float
    projected_points: np.ndarray
    reprojection_errors: np.ndarray
    mean_reprojection_error: float
    max_reprojection_error: float


def get_experiment_data() -> tuple[np.ndarray, np.ndarray]:
    return WORLD_POINTS.copy(), IMAGE_POINTS.copy()


def _to_homogeneous(points: np.ndarray) -> np.ndarray:
    return np.column_stack((points, np.ones(points.shape[0])))


def _normalize_points_2d(points: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    centroid = points.mean(axis=0)
    centered = points - centroid
    mean_distance = np.linalg.norm(centered, axis=1).mean()
    scale = np.sqrt(2.0) / mean_distance
    transform = np.array(
        [
            [scale, 0.0, -scale * centroid[0]],
            [0.0, scale, -scale * centroid[1]],
            [0.0, 0.0, 1.0],
        ]
    )
    normalized = (transform @ _to_homogeneous(points).T).T
    return transform, normalized


def _normalize_points_3d(points: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    centroid = points.mean(axis=0)
    centered = points - centroid
    mean_distance = np.linalg.norm(centered, axis=1).mean()
    scale = np.sqrt(3.0) / mean_distance
    transform = np.array(
        [
            [scale, 0.0, 0.0, -scale * centroid[0]],
            [0.0, scale, 0.0, -scale * centroid[1]],
            [0.0, 0.0, scale, -scale * centroid[2]],
            [0.0, 0.0, 0.0, 1.0],
        ]
    )
    normalized = (transform @ _to_homogeneous(points).T).T
    return transform, normalized


def estimate_projection_matrix(
    world_points: np.ndarray,
    image_points: np.ndarray,
) -> np.ndarray:
    if world_points.shape != (10, 3):
        raise ValueError("world_points must have shape (10, 3) for this experiment.")
    if image_points.shape != (10, 2):
        raise ValueError("image_points must have shape (10, 2) for this experiment.")

    image_transform, normalized_image_points = _normalize_points_2d(image_points)
    world_transform, normalized_world_points = _normalize_points_3d(world_points)

    design_matrix = []
    for world_point, image_point in zip(normalized_world_points, normalized_image_points):
        x_coord, y_coord, z_coord, w_coord = world_point
        u_coord, v_coord, _ = image_point
        design_matrix.append(
            [
                0.0,
                0.0,
                0.0,
                0.0,
                -w_coord * x_coord,
                -w_coord * y_coord,
                -w_coord * z_coord,
                -w_coord * w_coord,
                v_coord * x_coord,
                v_coord * y_coord,
                v_coord * z_coord,
                v_coord * w_coord,
            ]
        )
        design_matrix.append(
            [
                w_coord * x_coord,
                w_coord * y_coord,
                w_coord * z_coord,
                w_coord * w_coord,
                0.0,
                0.0,
                0.0,
                0.0,
                -u_coord * x_coord,
                -u_coord * y_coord,
                -u_coord * z_coord,
                -u_coord * w_coord,
            ]
        )

    _, _, right_vectors = np.linalg.svd(np.asarray(design_matrix))
    normalized_projection_matrix = right_vectors[-1].reshape(3, 4)
    projection_matrix = (
        np.linalg.inv(image_transform)
        @ normalized_projection_matrix
        @ world_transform
    )

    return projection_matrix / projection_matrix[-1, -1]


def project_points(
    projection_matrix: np.ndarray,
    world_points: np.ndarray,
) -> np.ndarray:
    projected = (projection_matrix @ _to_homogeneous(world_points).T).T
    return projected[:, :2] / projected[:, 2:3]


def _rq_decomposition(matrix: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    orthogonal_part, upper_part = np.linalg.qr(np.flipud(matrix).T)
    upper_part = np.flipud(upper_part.T)
    upper_part = np.fliplr(upper_part)
    orthogonal_part = orthogonal_part.T
    orthogonal_part = np.flipud(orthogonal_part)
    return upper_part, orthogonal_part


def decompose_projection_matrix(
    projection_matrix: np.ndarray,
) -> tuple[np.ndarray, np.ndarray, np.ndarray, float]:
    left_block = projection_matrix[:, :3]
    intrinsic_unnormalized, rotation_matrix = _rq_decomposition(left_block)

    sign_matrix = np.diag(np.where(np.diag(intrinsic_unnormalized) < 0.0, -1.0, 1.0))
    intrinsic_unnormalized = intrinsic_unnormalized @ sign_matrix
    rotation_matrix = sign_matrix @ rotation_matrix

    if np.linalg.det(rotation_matrix) < 0.0:
        handedness_fix = np.diag([1.0, 1.0, -1.0])
        intrinsic_unnormalized = intrinsic_unnormalized @ handedness_fix
        rotation_matrix = handedness_fix @ rotation_matrix

    scale_factor = float(intrinsic_unnormalized[2, 2])
    intrinsic_matrix = intrinsic_unnormalized / scale_factor
    translation_vector = np.linalg.inv(intrinsic_unnormalized) @ projection_matrix[:, 3]

    return intrinsic_matrix, rotation_matrix, translation_vector, scale_factor


def calibrate_camera(
    world_points: np.ndarray,
    image_points: np.ndarray,
) -> CalibrationResult:
    projection_matrix = estimate_projection_matrix(world_points, image_points)
    intrinsic_matrix, rotation_matrix, translation_vector, scale_factor = (
        decompose_projection_matrix(projection_matrix)
    )
    projected_points = project_points(projection_matrix, world_points)
    reprojection_errors = np.linalg.norm(projected_points - image_points, axis=1)
    camera_center = -rotation_matrix.T @ translation_vector

    return CalibrationResult(
        projection_matrix=projection_matrix,
        intrinsic_matrix=intrinsic_matrix,
        rotation_matrix=rotation_matrix,
        translation_vector=translation_vector,
        camera_center=camera_center,
        scale_factor=scale_factor,
        projected_points=projected_points,
        reprojection_errors=reprojection_errors,
        mean_reprojection_error=float(reprojection_errors.mean()),
        max_reprojection_error=float(reprojection_errors.max()),
    )
