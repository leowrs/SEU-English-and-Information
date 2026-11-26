# Computer Vision Course Experiments

This repository stores computer vision course experiments in a structure that can grow beyond the first assignment.

## Layout

- `src/cv_course/experiments/`: reusable experiment implementations.
- `experiments/`: assignment PDFs, generated artifacts, and deliverables grouped by experiment.
- `scripts/`: command-line entry points for running experiments.
- `tests/`: regression tests grouped by experiment.

## Experiment 01

Camera calibration:

- assignment: `experiments/exp01_camera_calibration/assignment.pdf`
- code: `src/cv_course/experiments/exp01_camera_calibration/`
- outputs: `experiments/exp01_camera_calibration/artifacts/`
- submission package: `experiments/exp01_camera_calibration/deliverables/`

## Experiment 02

SIFT robustness:

- assignment: `experiments/exp02_sift/assignment.docx`
- released materials: `experiments/exp02_sift/materials/`
- code: `src/cv_course/experiments/exp02_sift/`
- outputs: `experiments/exp02_sift/artifacts/`
- submission package: `experiments/exp02_sift/deliverables/`

## Commands

Use the bundled Python runtime or any Python environment with `numpy`, `Pillow`, and `python-docx` installed.

```powershell
python scripts/run_experiment_01.py --group-name OPT
python scripts/run_experiment_02.py --group-name OPT
python -m unittest discover -s tests -v
```
