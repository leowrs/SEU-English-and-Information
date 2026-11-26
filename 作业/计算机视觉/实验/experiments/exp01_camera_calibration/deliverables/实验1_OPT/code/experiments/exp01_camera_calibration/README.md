# Experiment 01: Camera Calibration

This experiment estimates a 3D-to-2D camera projection matrix from the assignment data, decomposes it into intrinsic and extrinsic parameters, verifies reprojection accuracy, and generates the report package.

## Layout

- `assignment.pdf`: original assignment.
- `artifacts/`: generated numeric results.
- `deliverables/`: generated report folder and compressed submission package.

## Run

From the repository root:

```powershell
python scripts/run_experiment_01.py --group-name OPT
python -m unittest discover -s tests -v
```
