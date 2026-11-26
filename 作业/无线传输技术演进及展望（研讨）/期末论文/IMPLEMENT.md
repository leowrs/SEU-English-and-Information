# Implementation Plan: Evolution of OFDM Systems - From Foundations to ISAC

## 0. Meta Data

- **Title Candidate**: Evolution and Future of OFDM: From Foundations to Integrated Sensing and Communication (ISAC)
- **Target Journal**: IEEE Communications Surveys & Tutorials (Impact Factor ~35) / IEEE Wireless Communications
- **Estimated Length**: 15-20 Pages (Double Column, IEEE Journal Format) / ~12,000 words
- **Core Theme**: Tracing the evolution of OFDM from basic multicarrier modulation to its modern integration with NOMA and Sensing (ISAC), emphasizing the **Complexity-Performance Trade-off** in PAPR reduction.

## Phase 1: Knowledge Graph Construction (Day 1-5)

- [ ] **Task 1.1: Finalized Taxonomy Definition (Updated 01/25)**
  - _Action_: Implement the 4-Dimension MECE structure derived from 54+ Zotero items:
    1.  **Dimension 1: Foundations & Evolution** (The 'Why' & 'How')
        - _Scope_: Historical Context (Weinstein 1971), System Comparison (CDMA vs OFDM), Synch & Channel Estimation.
    2.  **Dimension 2: Impairment Mitigation** (The 'Core Challenge')
        - _PAPR Reduction_ (Primary Focus):
          - **Probabilistic**: SLM (Focus on Blind/No-SI methods), PTS, Interleaving.
          - **Distortion**: Companding, Clipping.
          - **Coding/Extension**: Tone Reservation (TR), Tone Injection (TI), Active Constellation Extension (ACE).
        - _ICI Reduction_: Self-cancellation schemes.
    3.  **Dimension 3: System Integration** (The 'Context')
        - **MIMO-OFDM**: Space-Time-Frequency Coding, Beamforming.
        - **Multiple Access**: OFDM-NOMA (Power Domain), MC-CDMA.
    4.  **Dimension 4: New Frontiers** (The 'Future')
        - **Beyond RF**: Optical OFDM (VLC, ACO-OFDM).
        - **Sensing (ISAC)**: Opportunistic Sensing (Rexhepi 2025).
        - **AI/ML**: Swarm Intelligence for parameter optimization.

- [ ] **Task 1.2: Literature Filtering Strategy**
  - _Inclusion_: IEEE Transactions/Journals, seminal papers (1970s-2000s), and recent high-impact articles (2020-2025) on ISAC/NOMA.
  - _Exclusion_: Conference papers with <10 citations (unless very recent), pure simulation studies without analysis.

## Phase 2: Drafting - The Core (Day 6-20)

- [ ] **Task 2.1: The "Evolution" Narrative (Sections II & III)**
  - _Content_: Start with Weinstein's 1971 breakthrough (`C4Z548DM`). Explain why OFDM beat CDMA (`9MIQCGEJ`) for 4G/5G (Simple eq. vs Complex RAKE receivers).
  - _Deliverable_: A timeline figure showing OFDM's journey through standards (DAB -> DVB -> WiFi -> LTE -> 5G NR).

- [ ] **Task 2.2: Deep Dive into PAPR (Section IV)**
  - _Guideline_: Use the new **Quantitative Trade-off** rule.
  - _Action_: Compare SLM vs. PTS not just by description, but by `FLOPS count` vs `CCDF gain`.
  - _Key Reference_: Li et al. 2008 (`LHYACXCN`) for low-complexity benchmarks.

- [ ] **Task 2.3: Modern Integration (Section V)**
  - _Focus_: How OFDM adapts to NOMA (Sayyari 2022, `2PGQ8UKQ`).
  - _Challenge_: Distinguish between OFDM-NOMA and standard OFDMA.

- [ ] **Task 2.4: Future Trends (Section VI)**
  - _Highlight_: ISAC/JCAS. How OFDM signals are used for radar sensing (Range/Doppler estimation).
  - _Ref_: Rexhepi 2025 (`TB6C7JYJ`).

## Phase 3: Narrative & Connecting (Day 21-25)

- [ ] **Task 3.1: Introduction & Motivation**
  - _Gap_: "While many surveys cover PAPR, few connect it to the recent ISAC paradigm shift in 6G."
  - _Contributions Table_: Explicitly compare with 3-4 existing surveys (use Zotero to find these reviews).

- [ ] **Task 3.2: Abstract Optimization**
  - _Drafting_: Ensure it covers: Background (5G/6G) -> Problem (PAPR/Spectrum) -> Scope (History to ISAC) -> Contribution.

## Phase 4: Review & Polish (Day 26-30)

- [ ] **Self-Check**: Verify against updated `CLAUDE.md`:
  - Are simulation parameters (Channel models) listed?
  - Is "Standardization Linkage" present for every major technology discussed?
- [ ] **Citation Audit**: Ensure seminal works (`C4Z548DM`) and recent breakthroughs (`TB6C7JYJ`) are correctly cited.

## Key Zotero Resources Library

| Key        | Year | Topic                 | Usage in Review                     |
| :--------- | :--- | :-------------------- | :---------------------------------- |
| `C4Z548DM` | 1971 | OFDM Foundation (DFT) | History/Fundamentals                |
| `9MIQCGEJ` | 2002 | CDMA vs OFDM          | Evolution Motivation (Why OFDM won) |
| `LHYACXCN` | 2008 | Low Complexity SLM    | PAPR Techniques (Benchmark)         |
| `2PGQ8UKQ` | 2022 | OFDM-NOMA PTS         | Modern Integration (5G/B5G)         |
| `TB6C7JYJ` | 2025 | OFDM ISAC/Sensing     | Future Trends (6G)                  |
