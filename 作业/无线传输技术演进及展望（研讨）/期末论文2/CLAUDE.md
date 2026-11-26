# CLAUDE.md - Survey Paper Writing Guidelines

## 1. Core Principles (核心原则)

- **Comprehensiveness (全景视角)**: 综述不仅仅是罗列，必须覆盖从"愿景(Vision)"到"需求(Requirements)"，再到"架构(Architecture)"和"具体技术(Technologies)"的完整生态链。
- **Critical Appraisal (批判性评估)**: 避免单纯的流水账（Listing）。对现有文献和技术必须进行批判性分析，明确指出其局限性（Limitations）和技术空白（Gaps）。
- **Structured Comparison (结构化对比)**: 必须大量使用表格（Tables）来横向对比现有综述文章与本文的差异，以及对比不同技术方案的性能指标（KPIs）。
- **Vision-Driven (愿景驱动)**: 对于前沿综述，应从未来的应用场景倒推技术需求，体现前瞻性。

## 2. Structure & Outline (结构编排)

- **Abstract (摘要公式)**:
  1. **Background**: 一句话引入技术阶段 (e.g., "5G has entered commercial deployment...").
  2. **Problem**: 指出当前局限性 (e.g., "However, it faces challenges in...").
  3. **Status**: 简述学术/工业界现状 (e.g., "Research has commenced...").
  4. **Scope**: 明确本文覆盖范围 (Visions, Requirements, Technologies).
  5. **Contribution**: 强调本文的独特性 (e.g., "Crucially, this survey details X for the first time...").

- **Introduction (引言逻辑)**:
  1. **Historical Context**: 简述技术代际演进 (e.g., "From 1G to 5G...").
  2. **Gap Analysis (Motivation)**: 专门一节详述上一代技术的不足，为新技术引入提供强发动机。
  3. **Contributions**: **[必须]** 显式列出3-4点贡献，并使用表格 (Table) 对比本文与现有综述的区别。
  4. **Organization**: "The rest of the survey is organized as follows..."

- **Main Body (Taxonomy 分类学)**:
  - 采用 **Vision -> Requirements -> Architecture -> Key Technologies** 的层级结构。
  - 对于算法类综述 (如 OFDM/PAPR)，采用 **Principle -> Mathematical Model -> Algorithm Classification -> Complexity Analysis**。
  - **Simulation Setup Standard**: 必须总结主流文献使用的标准参数集 (Benchmark Parameters)，如信道模型 (EVA/ETU)、车速、多径时延等，确保可复现性。
  - **Standardization Linkage**: 必须将学术算法关联至工业标准 (e.g., "Adopted in LTE Rel-15", "Part of WiFi-7 candidate technologies")。
  - 使用层级化的标题和小结（Summary sections）来管理复杂内容。

- **Comparisons (对比 - 核心价值)**:
  - 禁止仅做文字描述。必须提供 **Summary Tables** 对比不同算法/架构的优缺点、复杂度、适用场景。
  - **Quantitative Metrics**: 对于通信类论文，必须对比计算复杂度 (Computational Complexity) 和性能指标 (如 BER, CCDF)。

- **Conclusion & Future Works**:
  - **Open Issues**: 针对正文提到的技术，提出开放性问题，旨在 "stimulate global debate"。
  - **Conclusion**: 总结全文，重申愿景与核心技术路径。

## 3. Writing Style & Tone (写作风格)

- **Voice**:
  - **Expert/Authoritative**: 使用确定的语气描述趋势 (e.g., "It is envisioned that...", "6G will be...").
  - **Objective but Critical**: 先肯定现有工作，随即通过 "However", "Although" 转折指出不足。

- **Scientific Rigor (严谨性)**:
  - **Citation Authority**: 优先引用顶级期刊 (IEEE Trans., JSAC) 和旗舰会议 (ICC, Globecom) 的论文。避免大量引用预印本 (arXiv) 除非涵盖最新趋势。
  - **Avoid Overclaiming**: 避免绝对化词汇 (never, always, perfect)。使用 "mitigate" 代替 "eliminate"， "outperform in terms of X" 代替 "is better than"。
  - **Quantitative Trade-off**: 禁止仅做定性描述。必须量化 "Complexity vs. Performance" 的权衡 (e.g., "Sacrificing 0.5dB gain for 30% FLOPS reduction")。

- **Complexity**:
  - 句子结构要严谨，多使用复合句来表达因果和转折关系，但避免过于晦涩。
  - **Paragraphs**: 每个段落必须有明确的主题句（Topic Sentence）。

- **Critique (如何评价前人)**:
  - "Although [Algorithm A] improves X, it incurs high computational cost."
  - "The existing literature has identified X, but [Specific Aspect] is not sufficiently discussed."

## 4. Academic Phraseology (常用句式库)

- **Opening (开头)**:
  - "With the rapid proliferation of [Technology]..."
  - "Recent years have witnessed the unprecedented growth of..."
  - "[Topic] has emerged as a promising paradigm to address..."

- **Gap Identification & Motivation (动机与差距)**:
  - "However, these works mainly focus on X, ignoring the vital aspect of Y."
  - "A comprehensive survey on [Topic] is still missing in the literature."
  - "To bridge this gap, this paper presents..."

- **Contributions (贡献陈述)**:
  - "To the best of our knowledge, this is the first survey that..."
  - "The key contributions of this article are summarized as follows:"
  - "We provide a comprehensive taxonomy of..."

- **Transitions (过渡)**:
  - "In contrast to conventional approaches..."
  - "To further enhance the performance of..."
  - "Based on the aforementioned requirements, we now discuss..."

- **Concluding (总结)**:
  - "In summary, [Technology] is pivotal for..."
  - "We have scrutinized the visions and requirements of..."
  - "This survey aims to shed light on..."

## 5. LaTeX/Formatting Rules (Formatting)

- **Citations (引用)**:
  - 使用方括号数字，如 `[1]`。
  - 多个连续引用合并：`[1]-[5]`；不连续合并：`[1], [3], [5]`。
  - 句中位置：通常在名词后或句尾，e.g., "As discussed in [1], ..."

- **Captions (图表标题)**:
  - **Figures**: `Fig. 1. Description of the figure.` (放在图下方)
  - **Tables**: `TABLE I SUMMARY OF COMPARISON` (通常大写或首字母大写，放在表上方)
  - **Self-contained**: 标题应包含足够信息，使读者不看正文也能理解图表大意。

- **Lists**:
  - 在列举贡献（Contributions）时，使用 `1), 2), 3)` 或 Bullet points。
