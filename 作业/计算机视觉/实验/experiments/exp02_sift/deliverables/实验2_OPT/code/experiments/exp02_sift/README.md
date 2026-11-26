# Experiment 02: SIFT Robustness

This experiment uses the released Lowe SIFT demo to compare feature detection and matching under rotation, illumination changes, image scaling, and different image content.

## Inputs

- `assignment.docx`: copied original assignment.
- `materials/img1.jpg`, `materials/img2.jpg`: assignment images.
- `materials/siftDemoV4/siftWin32.exe`: SIFT keypoint extractor.
- `materials/siftDemoV4.zip`: original released SIFT archive.

## Outputs

- `artifacts/`: generated variant images, key files, figures, and JSON summary.
- `deliverables/`: generated report folder and compressed submission package.

## Run

From the repository root:

```powershell
python scripts/run_experiment_02.py --group-name OPT
python -m unittest discover -s tests -v
```
