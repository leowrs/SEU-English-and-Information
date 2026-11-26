# Original Author: GitHub @leowrs (https://github.com/leowrs)
from __future__ import annotations

from pathlib import Path
import textwrap

from PIL import Image, ImageDraw, ImageFont
from docx import Document
from docx.enum.section import WD_SECTION
from docx.enum.table import WD_ALIGN_VERTICAL, WD_TABLE_ALIGNMENT
from docx.enum.text import WD_ALIGN_PARAGRAPH, WD_BREAK
from docx.oxml import OxmlElement
from docx.oxml.ns import qn
from docx.shared import Cm, Inches, Pt, RGBColor


ROOT = Path(__file__).resolve().parent
OUT_DOCX = ROOT / "计算机视觉课程报告-视觉基础模型到世界模型最新进展.docx"
FIGURE_PATH = ROOT / "cv_foundation_model_roadmap.png"

FONT_SONG = "SimSun"
FONT_HEI = "SimHei"
FONT_LATIN = "Times New Roman"
FONT_DENG = "DengXian"
FONT_HEI_PATH = Path(r"C:\Windows\Fonts\simhei.ttf")
FONT_SONG_PATH = Path(r"C:\Windows\Fonts\simsun.ttc")


def set_run_font(run, east_asia: str = FONT_SONG, latin: str = FONT_LATIN, size: float | None = None,
                 bold: bool | None = None, color: str | None = None) -> None:
    run.font.name = latin
    run._element.rPr.rFonts.set(qn("w:eastAsia"), east_asia)
    run._element.rPr.rFonts.set(qn("w:ascii"), latin)
    run._element.rPr.rFonts.set(qn("w:hAnsi"), latin)
    if size is not None:
        run.font.size = Pt(size)
    if bold is not None:
        run.bold = bold
    if color:
        run.font.color.rgb = RGBColor.from_string(color)


def set_paragraph_font(paragraph, east_asia: str = FONT_SONG, latin: str = FONT_LATIN,
                       size: float = 10.5) -> None:
    for run in paragraph.runs:
        set_run_font(run, east_asia=east_asia, latin=latin, size=size)


def set_style_font(style, east_asia: str, latin: str = FONT_LATIN, size: float = 10.5,
                   bold: bool | None = None, color: str | None = None) -> None:
    style.font.name = latin
    style._element.rPr.rFonts.set(qn("w:eastAsia"), east_asia)
    style._element.rPr.rFonts.set(qn("w:ascii"), latin)
    style._element.rPr.rFonts.set(qn("w:hAnsi"), latin)
    style.font.size = Pt(size)
    if bold is not None:
        style.font.bold = bold
    if color:
        style.font.color.rgb = RGBColor.from_string(color)


def configure_document(doc: Document) -> None:
    section = doc.sections[0]
    section.page_width = Cm(21)
    section.page_height = Cm(29.7)
    section.top_margin = Cm(2.54)
    section.bottom_margin = Cm(2.54)
    section.left_margin = Cm(3.17)
    section.right_margin = Cm(3.17)
    section.header_distance = Cm(1.25)
    section.footer_distance = Cm(1.25)

    styles = doc.styles
    normal = styles["Normal"]
    set_style_font(normal, FONT_SONG, size=10.5)
    normal.paragraph_format.line_spacing = 1.35
    normal.paragraph_format.space_after = Pt(6)

    h1 = styles["Heading 1"]
    set_style_font(h1, FONT_HEI, size=16, bold=True, color="1F4D78")
    h1.paragraph_format.space_before = Pt(18)
    h1.paragraph_format.space_after = Pt(8)
    h1.paragraph_format.keep_with_next = True

    h2 = styles["Heading 2"]
    set_style_font(h2, FONT_HEI, size=13, bold=True, color="2E74B5")
    h2.paragraph_format.space_before = Pt(12)
    h2.paragraph_format.space_after = Pt(6)
    h2.paragraph_format.keep_with_next = True

    h3 = styles["Heading 3"]
    set_style_font(h3, FONT_HEI, size=11.5, bold=True, color="1F4D78")
    h3.paragraph_format.space_before = Pt(8)
    h3.paragraph_format.space_after = Pt(4)
    h3.paragraph_format.keep_with_next = True

    for style_name in ["List Bullet", "List Number"]:
        st = styles[style_name]
        set_style_font(st, FONT_SONG, size=10.5)
        st.paragraph_format.line_spacing = 1.25
        st.paragraph_format.space_after = Pt(4)


def add_page_number(paragraph) -> None:
    paragraph.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = paragraph.add_run("第 ")
    set_run_font(run, FONT_SONG, size=9)
    fld_char_1 = OxmlElement("w:fldChar")
    fld_char_1.set(qn("w:fldCharType"), "begin")
    instr_text = OxmlElement("w:instrText")
    instr_text.set(qn("xml:space"), "preserve")
    instr_text.text = "PAGE"
    fld_char_2 = OxmlElement("w:fldChar")
    fld_char_2.set(qn("w:fldCharType"), "end")
    run._r.append(fld_char_1)
    run._r.append(instr_text)
    run._r.append(fld_char_2)
    run2 = paragraph.add_run(" 页")
    set_run_font(run2, FONT_SONG, size=9)


def add_body_paragraph(doc: Document, text: str, first_line: bool = True,
                       align=WD_ALIGN_PARAGRAPH.JUSTIFY) -> None:
    p = doc.add_paragraph()
    p.alignment = align
    p.paragraph_format.line_spacing = 1.35
    p.paragraph_format.space_after = Pt(6)
    if first_line:
        p.paragraph_format.first_line_indent = Cm(0.74)
    run = p.add_run(text)
    set_run_font(run, FONT_SONG, size=10.5)


def add_caption(doc: Document, text: str) -> None:
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p.paragraph_format.space_after = Pt(8)
    run = p.add_run(text)
    set_run_font(run, FONT_SONG, size=9, color="555555")


def cell_text(cell, text: str, bold: bool = False, size: float = 9.5,
              color: str | None = None, align=WD_ALIGN_PARAGRAPH.LEFT) -> None:
    cell.text = ""
    p = cell.paragraphs[0]
    p.alignment = align
    p.paragraph_format.space_after = Pt(0)
    p.paragraph_format.line_spacing = 1.15
    run = p.add_run(text)
    set_run_font(run, FONT_SONG, size=size, bold=bold, color=color)
    cell.vertical_alignment = WD_ALIGN_VERTICAL.CENTER


def set_cell_shading(cell, fill: str) -> None:
    tc_pr = cell._tc.get_or_add_tcPr()
    shd = tc_pr.find(qn("w:shd"))
    if shd is None:
        shd = OxmlElement("w:shd")
        tc_pr.append(shd)
    shd.set(qn("w:fill"), fill)


def set_cell_margins(cell, top=80, start=120, bottom=80, end=120) -> None:
    tc = cell._tc
    tc_pr = tc.get_or_add_tcPr()
    tc_mar = tc_pr.first_child_found_in("w:tcMar")
    if tc_mar is None:
        tc_mar = OxmlElement("w:tcMar")
        tc_pr.append(tc_mar)
    for m, v in [("top", top), ("start", start), ("bottom", bottom), ("end", end)]:
        node = tc_mar.find(qn(f"w:{m}"))
        if node is None:
            node = OxmlElement(f"w:{m}")
            tc_mar.append(node)
        node.set(qn("w:w"), str(v))
        node.set(qn("w:type"), "dxa")


def set_table_borders(table, color="D9E2EC", size="6") -> None:
    tbl = table._tbl
    tbl_pr = tbl.tblPr
    borders = tbl_pr.first_child_found_in("w:tblBorders")
    if borders is None:
        borders = OxmlElement("w:tblBorders")
        tbl_pr.append(borders)
    for edge in ("top", "left", "bottom", "right", "insideH", "insideV"):
        tag = f"w:{edge}"
        element = borders.find(qn(tag))
        if element is None:
            element = OxmlElement(tag)
            borders.append(element)
        element.set(qn("w:val"), "single")
        element.set(qn("w:sz"), size)
        element.set(qn("w:space"), "0")
        element.set(qn("w:color"), color)


def set_table_widths(table, widths_cm: list[float]) -> None:
    table.autofit = False
    for row in table.rows:
        for idx, width in enumerate(widths_cm):
            row.cells[idx].width = Cm(width)


def make_table(doc: Document, headers: list[str], rows: list[list[str]], widths_cm: list[float]):
    table = doc.add_table(rows=1, cols=len(headers))
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.style = "Table Grid"
    set_table_widths(table, widths_cm)
    set_table_borders(table)
    for i, header in enumerate(headers):
        cell = table.rows[0].cells[i]
        set_cell_shading(cell, "F4F6F9")
        set_cell_margins(cell)
        cell_text(cell, header, bold=True, color="1F4D78", align=WD_ALIGN_PARAGRAPH.CENTER)
    for row_data in rows:
        row = table.add_row()
        for i, value in enumerate(row_data):
            cell = row.cells[i]
            set_cell_margins(cell)
            cell_text(cell, value, size=9.2, align=WD_ALIGN_PARAGRAPH.LEFT)
    return table


def draw_wrapped(draw: ImageDraw.ImageDraw, xy: tuple[int, int], text: str, font: ImageFont.FreeTypeFont,
                 fill: str, max_width: int, line_gap: int = 5, align: str = "center") -> int:
    lines: list[str] = []
    current = ""
    for ch in text:
        candidate = current + ch
        if draw.textbbox((0, 0), candidate, font=font)[2] <= max_width:
            current = candidate
        else:
            if current:
                lines.append(current)
            current = ch
    if current:
        lines.append(current)
    x, y = xy
    for line in lines:
        bbox = draw.textbbox((0, 0), line, font=font)
        width = bbox[2] - bbox[0]
        if align == "center":
            lx = x + (max_width - width) // 2
        else:
            lx = x
        draw.text((lx, y), line, font=font, fill=fill)
        y += (bbox[3] - bbox[1]) + line_gap
    return y


def create_roadmap_figure(path: Path) -> None:
    w, h = 2000, 1050
    img = Image.new("RGB", (w, h), "white")
    draw = ImageDraw.Draw(img)
    title_font = ImageFont.truetype(str(FONT_HEI_PATH), 56)
    head_font = ImageFont.truetype(str(FONT_HEI_PATH), 34)
    body_font = ImageFont.truetype(str(FONT_SONG_PATH), 25)
    small_font = ImageFont.truetype(str(FONT_SONG_PATH), 24)

    draw.rectangle((0, 0, w, h), fill="#FFFFFF")
    draw.text((90, 70), "2023—2026 计算机视觉算法与技术演进路线", font=title_font, fill="#0B2545")
    draw.text((92, 142), "从“识别图片”走向“理解多模态、生成世界、支撑行动”", font=body_font, fill="#52616B")

    boxes = [
        ("视觉表征基础模型", "DINOv2\n自监督特征\n高质量视觉编码器", "#E8F1FF"),
        ("提示式视觉模型", "SAM 2 / Florence-2\n分割、检测、描述\n统一为提示接口", "#EAF7F0"),
        ("视觉语言模型", "Qwen2.5-VL\nGemini 1.5\n动态分辨率、长上下文\n图文视频推理", "#FFF3DC"),
        ("生成式视觉", "SD3 / Sora\nMovie Gen\nDiT、流匹配\n图像与视频生成", "#FDECEC"),
        ("3D与世界模型", "3DGS / VGGT\nV-JEPA 2\n几何、预测、规划\n机器人控制", "#F0EAFE"),
    ]
    x0, y0 = 95, 260
    box_w, box_h, gap = 330, 330, 45
    accent = "#2E74B5"
    for idx, (head, body, fill) in enumerate(boxes):
        x = x0 + idx * (box_w + gap)
        y = y0
        draw.rounded_rectangle((x, y, x + box_w, y + box_h), radius=32, fill=fill, outline="#B7C7D9", width=3)
        draw_wrapped(draw, (x + 25, y + 38), head, head_font, "#0B2545", box_w - 50)
        draw.line((x + 35, y + 105, x + box_w - 35, y + 105), fill="#B7C7D9", width=2)
        for line_idx, line in enumerate(body.split("\n")):
            draw_wrapped(draw, (x + 30, y + 140 + line_idx * 50), line, body_font, "#1F2933", box_w - 60)
        if idx < len(boxes) - 1:
            ax = x + box_w + 5
            ay = y + box_h // 2
            draw.line((ax, ay, ax + gap - 18, ay), fill=accent, width=5)
            draw.polygon([(ax + gap - 18, ay - 12), (ax + gap - 18, ay + 12), (ax + gap + 4, ay)], fill=accent)

    draw.rounded_rectangle((120, 680, 1880, 905), radius=28, fill="#F7F9FB", outline="#D9E2EC", width=3)
    draw.text((160, 720), "共同机制：", font=head_font, fill="#1F4D78")
    mechanisms = [
        "Transformer令牌化与规模化",
        "自监督/弱监督数据引擎",
        "可提示交互接口",
        "扩散、流匹配与一致性蒸馏",
        "长上下文记忆与动作 grounding",
    ]
    start_x, start_y = 160, 785
    chip_x = start_x
    for item in mechanisms:
        bbox = draw.textbbox((0, 0), item, font=small_font)
        chip_w = bbox[2] - bbox[0] + 42
        draw.rounded_rectangle((chip_x, start_y, chip_x + chip_w, start_y + 62), radius=22, fill="#FFFFFF",
                               outline="#C9D6E2", width=2)
        draw.text((chip_x + 21, start_y + 16), item, font=small_font, fill="#273849")
        chip_x += chip_w + 28

    draw.text((120, 960), "图示根据 2023—2026 年公开论文与官方技术报告整理；箭头表示能力主线，不表示单一路径替代。", font=small_font, fill="#6B7280")
    img.save(path, quality=95)


def add_cover(doc: Document) -> None:
    for _ in range(2):
        doc.add_paragraph()
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = p.add_run("计算机视觉基础")
    set_run_font(run, FONT_HEI, size=22, bold=True, color="1F4D78")
    p.paragraph_format.space_after = Pt(10)

    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = p.add_run("课程报告")
    set_run_font(run, FONT_HEI, size=26, bold=True, color="0B2545")
    p.paragraph_format.space_after = Pt(34)

    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = p.add_run("从视觉基础模型到世界模型：\n2023—2026年计算机视觉算法与技术最新进展综述")
    set_run_font(run, FONT_HEI, size=18, bold=True, color="1F2933")
    p.paragraph_format.line_spacing = 1.3
    p.paragraph_format.space_after = Pt(42)

    table = doc.add_table(rows=5, cols=2)
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    set_table_borders(table, color="C9D6E2")
    set_table_widths(table, [3.5, 8.5])
    rows = [
        ("题目", "介绍算法与技术的最新进展"),
        ("专业", "信息工程"),
        ("组员", "待填写姓名 / 学号"),
        ("任课教师", "陆建"),
        ("完成时间", "2026年6月"),
    ]
    for r_idx, (k, v) in enumerate(rows):
        cell_text(table.rows[r_idx].cells[0], k, bold=True, size=11, color="1F4D78", align=WD_ALIGN_PARAGRAPH.CENTER)
        cell_text(table.rows[r_idx].cells[1], v, size=11)
        set_cell_shading(table.rows[r_idx].cells[0], "F4F6F9")
        set_cell_margins(table.rows[r_idx].cells[0], top=120, bottom=120)
        set_cell_margins(table.rows[r_idx].cells[1], top=120, bottom=120)

    doc.add_paragraph()
    p = doc.add_paragraph()
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    run = p.add_run("主题选择：介绍算法与技术的最新进展（含思政内容）")
    set_run_font(run, FONT_SONG, size=10.5, color="555555")
    doc.add_page_break()


def add_abstract(doc: Document) -> None:
    doc.add_heading("摘要", level=1)
    abstract = (
        "2023年以来，计算机视觉的主线已经从单一任务模型转向视觉基础模型、视觉语言模型、生成式视频模型、"
        "三维几何模型和具身智能模型的融合演进。以DINOv2、SAM 2、Florence-2为代表的视觉基础模型，"
        "通过大规模自监督学习、提示式交互和统一任务表示，使检测、分割、描述和跟踪不再完全依赖“一个任务训练一个模型”的范式。"
        "以Qwen2.5-VL、Gemini 1.5、GPT-4o和LLaVA-OneVision为代表的视觉语言模型，把图像、文档、视频、音频和文本纳入统一推理框架，"
        "动态分辨率、超长上下文和多模态指令遵循成为新的能力核心。与此同时，Stable Diffusion 3、Sora、Movie Gen等模型推动视觉生成从静态图像走向长视频、音画同步和可编辑媒体；"
        "3D Gaussian Splatting、pixelSplat、VGGT等技术则把实时三维重建、多视图几何和可交互场景表示推向应用前沿。"
        "更进一步，OpenVLA、π0和V-JEPA 2显示出视觉模型正在从“看懂”走向“预测、规划和行动”。"
        "本文围绕上述技术路线，分析最新算法机制、代表模型、应用价值与风险挑战，并结合人工智能治理、科技自立自强和智能向善等要求，讨论计算机视觉发展应坚持的价值导向。"
    )
    add_body_paragraph(doc, abstract)
    p = doc.add_paragraph()
    run = p.add_run("关键词（关键字）：计算机视觉；视觉基础模型；视觉语言模型；生成式视频；三维重建；具身智能；人工智能治理")
    set_run_font(run, FONT_SONG, size=10.5)
    doc.add_page_break()


def add_contents_and_division(doc: Document) -> None:
    doc.add_heading("目录", level=1)
    contents = [
        "一、引言",
        "二、计算机视觉算法演进的总体趋势",
        "三、正文：算法与技术的最新进展",
        "    3.1 视觉基础模型：从专用网络到通用表征",
        "    3.2 视觉语言模型：从看图问答到多模态推理",
        "    3.3 开放词汇检测、分割与几何估计",
        "    3.4 生成式图像与视频：从合成内容到世界模拟",
        "    3.5 三维重建、多视图视觉与可编辑资产",
        "    3.6 世界模型与具身智能：从理解到行动",
        "四、应用价值与现实挑战",
        "五、思政融入：价值导向、责任边界与科技自立自强",
        "六、展望",
        "七、报告总结",
        "参考文献",
    ]
    for item in contents:
        p = doc.add_paragraph()
        p.paragraph_format.space_after = Pt(3)
        run = p.add_run(item)
        set_run_font(run, FONT_SONG, size=10.5)

    doc.add_heading("小组分工", level=1)
    rows = [
        ["成员1（待填写）", "资料检索、论文阅读、报告撰写与终稿统筹"],
        ["成员2（待填写）", "视觉语言模型与生成式视频部分整理"],
        ["成员3（待填写）", "三维重建、世界模型与具身智能部分整理"],
        ["成员4（待填写）", "图表制作、格式检查、参考文献核对"],
        ["成员5（待填写）", "PPT制作与课堂汇报"],
    ]
    make_table(doc, ["成员", "主要分工"], rows, [4.2, 10.2])
    add_body_paragraph(
        doc,
        "说明：课程要求小组成员最多5人。若实际为个人完成，可在提交前将上表合并为本人姓名，并保留“资料检索、报告撰写、图表制作、格式检查、PPT汇报”等任务说明。",
        first_line=False,
    )
    doc.add_page_break()


def add_main_report(doc: Document) -> None:
    doc.add_heading("一、引言", level=1)
    add_body_paragraph(
        doc,
        "传统计算机视觉课程通常从图像滤波、边缘检测、特征匹配、相机标定和图像配准讲起。"
        "这些内容构成了视觉系统的几何与信号处理基础：图像如何被采样，像素如何被增强，多个视角如何对齐，三维信息如何从二维投影中恢复。"
        "但近三年的研究表明，视觉技术的前沿已经发生明显转向：模型不再只学习某个封闭任务的判别边界，而是通过海量图像、视频、文本和交互数据学习通用表征，并用提示、语言或动作把能力迁移到新任务中。"
    )
    add_body_paragraph(
        doc,
        "因此，讨论“算法与技术的最新进展”不能只列举若干模型排行榜。更重要的问题是：这些模型为什么能统一多种视觉任务？"
        "视觉语言模型如何突破固定分辨率和短上下文限制？生成式视频为什么被称为世界模拟器？三维重建和具身智能又如何把视觉从识别系统推进到行动系统？"
        "本文以截至2026年6月可公开核验的论文和官方技术报告为依据，按“表征—理解—生成—三维—行动”的顺序梳理最新进展。"
    )

    doc.add_heading("二、计算机视觉算法演进的总体趋势", level=1)
    add_body_paragraph(
        doc,
        "第一条趋势是基础模型化。DINOv2通过大规模自监督学习获得稳健视觉特征，证明在没有人工标注类别的情况下，视觉编码器仍能迁移到分类、检索、密集预测等任务[1]。"
        "SAM 2进一步把“可提示分割”从静态图像扩展到视频，利用流式记忆机制在视频中保持目标身份和交互效率[2]。"
        "Florence-2则把检测、描述、定位、分割等任务统一为提示到序列的框架，并通过大规模自动标注数据训练统一视觉表示[3]。"
        "这些工作共同说明，视觉模型正在从专用工具变成可组合的通用能力层。"
    )
    add_body_paragraph(
        doc,
        "第二条趋势是多模态推理化。视觉语言模型不再只是给图片配字幕，而是要理解图表、文档、视频事件、屏幕界面和现实场景。"
        "Qwen2.5-VL在动态分辨率、细粒度定位、文档理解和长视频理解方面继续增强[6]；Gemini 1.5把百万级上下文引入多模态场景[7]；GPT-4o强调原生多模态交互与实时响应[8]。"
        "这意味着视觉系统的输出从“类别标签”变成了“可解释、可追问、可执行的语义信息”。"
    )
    add_body_paragraph(
        doc,
        "第三条趋势是生成与几何融合。Stable Diffusion 3采用多模态扩散Transformer和整流流机制，提高了高分辨率图像生成的可扩展性[14]；Sora和Movie Gen把视频压缩为时空潜变量再进行生成，使视频模型开始具备镜头连贯性、物体持久性和可编辑能力[17][18]。"
        "与此同时，3D Gaussian Splatting实现实时新视角渲染[12]，VGGT尝试用统一Transformer处理相机位姿、深度和点云等几何任务[11]。"
        "视觉算法正在同时追求语义理解、物理一致性和三维可交互表示。"
    )

    doc.add_picture(str(FIGURE_PATH), width=Cm(14.3))
    add_caption(doc, "图1  2023—2026年计算机视觉算法与技术演进路线")

    trend_rows = [
        ["通用表征", "DINOv2、SAM 2、Florence-2", "自监督学习、提示式分割、统一任务序列化", "降低迁移成本，使视觉能力可复用"],
        ["多模态推理", "Qwen2.5-VL、Gemini 1.5、GPT-4o、LLaVA-OneVision", "动态分辨率、长上下文、图文视频联合推理", "视觉系统从识别走向解释、对话和任务执行"],
        ["开放词汇与密集预测", "YOLO-World、Depth Anything V2", "文本条件检测、大规模弱监督/合成数据", "减少类别封闭假设，提升真实场景适应性"],
        ["生成式视觉", "SD3、PIXART-δ、DyDiT、Sora、Movie Gen", "DiT、整流流、一致性蒸馏、时空潜变量", "提高内容生产、仿真和视频编辑能力"],
        ["三维与具身智能", "3DGS、pixelSplat、VGGT、OpenVLA、π0、V-JEPA 2", "显式高斯表示、多视图Transformer、VLA动作头、预测式世界模型", "连接机器人、AR/VR和物理世界任务"],
    ]
    make_table(doc, ["技术主线", "代表模型/技术", "核心机制", "意义"], trend_rows, [2.5, 3.4, 4.0, 4.5])
    add_caption(doc, "表1  计算机视觉最新进展的主线归纳")

    doc.add_heading("三、正文：算法与技术的最新进展", level=1)
    doc.add_heading("3.1 视觉基础模型：从专用网络到通用表征", level=2)
    add_body_paragraph(
        doc,
        "早期深度视觉模型通常围绕ImageNet分类、COCO检测或特定分割数据集优化，模型结构与训练目标高度绑定。"
        "DINOv2的意义在于，它把自监督视觉特征训练提升到基础模型层面：模型不依赖人工类别标签，而是通过视觉自身的相似性、局部—全局一致性和大规模数据过滤形成可迁移特征[1]。"
        "这种特征对下游任务有两个价值：一是减少标注成本，二是让不同任务共享同一个视觉编码器，便于工业系统中的统一部署。"
    )
    add_body_paragraph(
        doc,
        "SAM 2代表了另一个方向：不是只输出一个固定类别，而是让用户用点、框、掩码或历史记忆提示模型分割目标。"
        "相比图像版SAM，SAM 2面向视频引入streaming memory，使模型能在连续帧中保持目标信息，并通过model-in-the-loop数据引擎不断改善交互质量[2]。"
        "这类模型适合医疗影像轮廓标注、工业缺陷定位、视频编辑和遥感对象提取等场景。它的启示是，未来视觉模型的交互方式将更接近“协作式标注助手”，而不只是一次性预测器。"
    )
    add_body_paragraph(
        doc,
        "Florence-2进一步提出统一任务接口：把视觉任务都表示为文本提示和序列输出，例如“请描述图像”“请找出某物体位置”“请输出区域掩码”等[3]。"
        "这与大语言模型的指令范式相似，使视觉系统能够通过自然语言或结构化提示选择任务。"
        "从课程知识角度看，这并没有否定传统图像处理和几何视觉，而是把底层特征、区域、边界和语义包装成更高层的可调用能力。"
    )

    doc.add_heading("3.2 视觉语言模型：从看图问答到多模态推理", level=2)
    add_body_paragraph(
        doc,
        "视觉语言模型的发展速度尤其快。2024年的Qwen2-VL强调“任意分辨率”感知，通过动态分辨率把不同尺寸图像转化为不同数量视觉token，并结合多维旋转位置编码处理二维图像和视频时间信息[5]。"
        "2025年的Qwen2.5-VL继续加强文档解析、细粒度定位、视频事件理解和视觉agent能力[6]。"
        "这类设计解决了一个实际痛点：真实图像并不总是固定尺寸，文档截图、医学图像、监控画面和长视频都可能因为缩放而丢失关键信息。"
    )
    add_body_paragraph(
        doc,
        "Gemini 1.5展示了另一种能力路线：超长上下文。论文报告模型能够处理包含长文本、长视频、音频和代码的百万级上下文[7]。"
        "对于计算机视觉而言，长上下文意味着模型可以一次性理解更完整的过程，例如一段实验视频的全部步骤、一场课堂录屏的关键节点，或一组多视角图像之间的关系。"
        "GPT-4o和其他原生多模态模型则强调低延迟音视频交互，使视觉理解更接近实时人机协作[8]。"
    )
    add_body_paragraph(
        doc,
        "开源视觉语言模型也在缩小与闭源模型的差距。LLaVA-OneVision通过统一单图、多图和视频任务迁移，说明视觉语言模型可以从单图对话扩展到跨媒体理解[9]。"
        "PaliGemma 2和Idefics2等模型表明，紧凑视觉编码器、语言模型和高质量训练流程结合后，也能在OCR、图像描述、细粒度识别和文档理解中取得实用效果[23][24]。"
        "这对教学和科研尤其重要，因为开放模型便于复现实验、理解机制和构建国产化应用。"
    )

    doc.add_heading("3.3 开放词汇检测、分割与几何估计", level=2)
    add_body_paragraph(
        doc,
        "真实世界的视觉任务往往存在开放类别。传统检测器需要预先定义类别集合，遇到训练集中没有的对象就会失效。"
        "YOLO-World把文本嵌入与实时检测框架结合，使检测器能够根据文本提示识别开放词汇目标[4]。"
        "这类方法适合仓储盘点、安防巡检、机器人抓取等场景，因为用户可以临时指定要找的对象，而不是重新标注并训练整个检测器。"
    )
    add_body_paragraph(
        doc,
        "密集几何估计也出现基础模型化趋势。Depth Anything V2通过大规模数据和更强教师模型提升单目深度估计泛化能力[10]。"
        "单目深度本质上是不适定问题，因为一张图像缺少真实尺度；但大规模预训练能学习常见场景的几何先验，使模型在自动驾驶、室内导航、AR测量和三维重建中提供更稳定的初值。"
        "需要注意的是，深度基础模型仍可能在透明物体、反光表面、极端光照和罕见场景中失效，因此工程应用必须结合相机标定、多传感器融合和异常检测。"
    )

    doc.add_heading("3.4 生成式图像与视频：从合成内容到世界模拟", level=2)
    add_body_paragraph(
        doc,
        "生成式视觉的核心变化是骨干结构和采样方式的变化。Stable Diffusion 3使用多模态扩散Transformer与整流流训练，说明扩散模型正在从U-Net主干走向Transformer主干，并更重视文本—图像对齐和高分辨率生成[14]。"
        "PIXART-δ通过潜空间一致性模型把高质量图像生成压缩到少步采样[15]，DyDiT则尝试根据时间步和空间token动态调整扩散Transformer计算量[16]。"
        "这些工作说明生成模型的竞争不再只是“画得更逼真”，还包括更快、更可控、更低成本。"
    )
    add_body_paragraph(
        doc,
        "视频生成是近年最受关注的方向。Sora官方技术报告将视频和图像表示为时空patch，并在压缩后的潜空间中训练生成模型，使同一框架能够处理不同长度、分辨率和宽高比的视频[17]。"
        "Movie Gen进一步覆盖文本生成视频、个性化视频、视频编辑和音频生成，被定位为一组媒体基础模型[18]。"
        "Google DeepMind的Veo系列则展示了高质量视频生成、镜头控制和声音结合能力[19]。"
        "这些模型让视觉生成从静态图片合成走向内容生产流程，但也带来深度伪造、版权归属、训练数据透明度和物理一致性不足等问题。"
    )
    add_body_paragraph(
        doc,
        "把视频生成称为“世界模拟器”并不意味着模型真正理解物理定律。更准确地说，模型学到了大量视觉动态的统计规律：物体如何移动，镜头如何变化，动作如何影响场景。"
        "当这些规律足够强时，模型可以为机器人训练、自动驾驶仿真和影视预演提供低成本数据。"
        "但它仍可能在因果关系、物体守恒、长期一致性和可控性方面出错，所以不能把生成视频直接等同于可靠仿真。"
    )

    doc.add_heading("3.5 三维重建、多视图视觉与可编辑资产", level=2)
    add_body_paragraph(
        doc,
        "三维视觉长期依赖多视图几何、SLAM、NeRF和深度传感器。2023年的3D Gaussian Splatting用显式三维高斯表示场景，在保证较高渲染质量的同时实现实时新视角渲染[12]。"
        "与需要大量体渲染采样的NeRF相比，高斯表示更适合交互式浏览、编辑和AR/VR显示。"
        "pixelSplat则从图像对直接预测3D Gaussian，使可泛化三维重建更接近即时生成[13]。"
    )
    add_body_paragraph(
        doc,
        "2025年的VGGT把视觉几何任务进一步统一化：模型尝试从一个或多个视图中预测相机参数、深度图、点云和跟踪信息[11]。"
        "这与课程中相机标定、图像配准和三维重建的知识直接相关。传统方法强调几何约束和优化，基础模型强调数据驱动的先验与端到端预测。"
        "更合理的未来方向不是二选一，而是把深度学习的强先验与几何约束结合起来：用模型给出初值和语义理解，用几何优化保证尺度、位姿和一致性。"
    )

    doc.add_heading("3.6 世界模型与具身智能：从理解到行动", level=2)
    add_body_paragraph(
        doc,
        "计算机视觉的最终目标之一是让机器理解并参与真实世界。OpenVLA把视觉语言模型接入机器人动作输出，形成开源视觉—语言—动作模型[21]；π0使用视觉语言条件和flow matching策略学习通用机器人控制[22]。"
        "这些方法把视觉输入、语言指令和低层动作连接起来，使模型不只回答“图中有什么”，还要决定“接下来怎么做”。"
    )
    add_body_paragraph(
        doc,
        "V-JEPA 2代表预测式世界模型路线：模型通过自监督视频学习形成对未来状态和场景变化的预测能力，并把理解、预测和规划连接起来[25]。"
        "DeepMind的Genie 2则把世界模型用于可交互环境生成，强调从图像或文本提示中生成可操作的虚拟世界[20]。"
        "这说明视觉算法正在进入一个新的问题域：模型需要理解时间、因果、动作结果和任务目标。"
        "从算法角度看，这要求更好的长时记忆、物理一致性、可验证规划和跨机器人平台泛化。"
    )

    model_rows = [
        ["DINOv2", "2023", "自监督视觉表征", "无标注特征学习、数据过滤、大规模ViT", "迁移分类、检索、密集预测"],
        ["SAM 2", "2024", "提示式图像/视频分割", "流式记忆、交互提示、数据引擎", "视频目标分割、医学/工业标注"],
        ["Qwen2.5-VL", "2025", "视觉语言模型", "动态分辨率、定位、长视频和文档理解", "多模态助手、OCR、视觉agent"],
        ["Sora / Movie Gen", "2024", "视频生成", "时空潜变量、DiT/扩散、音视频生成与编辑", "内容创作、仿真、视频后期"],
        ["3DGS / VGGT", "2023/2025", "三维视觉", "显式高斯表示、多视图几何Transformer", "AR/VR、数字孪生、机器人感知"],
        ["OpenVLA / π0", "2024", "具身智能", "VLM接动作头、flow policy、机器人演示数据", "机器人控制、通用操作任务"],
    ]
    make_table(doc, ["模型/技术", "年份", "类型", "核心机制", "典型应用"], model_rows, [2.7, 1.5, 2.5, 4.1, 3.6])
    add_caption(doc, "表2  代表性最新视觉算法与技术对照")

    doc.add_heading("四、应用价值与现实挑战", level=1)
    add_body_paragraph(
        doc,
        "从应用角度看，最新视觉算法的价值主要体现在四类场景。第一是工业制造。开放词汇检测、视频分割和三维重建可以用于缺陷检测、工件定位、产线安全和数字孪生。"
        "第二是医疗与公共服务。提示式分割和多模态文档理解可辅助医生标注病灶、整理影像报告，但必须由专业人员复核，不能替代诊断责任。"
        "第三是交通与城市治理。深度估计、视频理解和世界模型可服务自动驾驶仿真、道路风险识别和应急响应。"
        "第四是教育、文化和科研。生成式视觉和三维重建可以用于虚拟实验、文物数字化、课程可视化和科研数据增强。"
    )
    add_body_paragraph(
        doc,
        "挑战同样突出。首先是数据与隐私问题。视觉模型训练常依赖海量图像和视频，若数据来源、授权和脱敏流程不清晰，容易侵犯个人信息和知识产权。"
        "其次是可靠性问题。视觉语言模型可能产生幻觉，生成式视频可能违反物理规律，深度估计和三维重建可能在特殊材质或极端场景中失败。"
        "再次是算力与能耗问题。基础模型规模越大，对训练算力、推理成本和部署设备的要求越高。"
        "最后是评价体系问题。很多榜单只衡量静态数据集表现，却难以评估模型在真实开放环境中的安全性、稳定性和可解释性。"
    )
    add_body_paragraph(
        doc,
        "因此，未来视觉系统的工程落地应采用“模型能力 + 任务约束 + 人工复核 + 持续评估”的方式。"
        "例如在工业质检中，模型可先给出缺陷候选区域，再由规则或人工复核关键样本；在医疗场景中，模型输出应作为辅助信息并保留审计记录；"
        "在生成式内容场景中，应加入水印、来源标注和滥用检测。这样的系统设计比单纯追求模型排行榜更符合现实需求。"
    )

    doc.add_heading("五、思政融入：价值导向、责任边界与科技自立自强", level=1)
    add_body_paragraph(
        doc,
        "计算机视觉的最新进展不仅是算法问题，也关系到国家科技竞争力、数字经济发展和社会治理。"
        "《新一代人工智能发展规划》提出要把人工智能作为推动科技跨越发展、产业优化升级和生产力整体跃升的重要战略技术[26]。"
        "视觉基础模型、三维重建和具身智能正是人工智能从互联网应用走向实体经济的重要接口：它们让机器能够感知生产线、交通道路、农田矿山和医疗影像。"
        "学习这些技术，不应停留在调用模型接口，而应理解数据、算法、算力和应用场景之间的系统关系，增强科技自立自强意识。"
    )
    add_body_paragraph(
        doc,
        "同时，技术越强，责任边界越重要。生成式视觉能够降低创作门槛，也可能被用于深度伪造、谣言传播和侵犯肖像权；"
        "视觉监控能够提升公共安全，也可能造成过度采集和算法歧视；视觉语言模型能提升服务效率，也可能在关键场景中给出不可靠建议。"
        "《生成式人工智能服务管理暂行办法》强调生成式人工智能服务应遵守法律法规、尊重社会公德伦理、保护个人信息和知识产权[27]。"
        "这提示我们，算法研究必须与数据治理、安全评估、可解释性和责任追溯同步推进。"
    )
    add_body_paragraph(
        doc,
        "从青年学生角度看，思政要求不是在技术报告末尾附加口号，而是贯穿问题选择、方法设计和应用落地。"
        "在选择研究方向时，应关注服务国家重大需求和人民生活质量的视觉任务，例如智能制造、智慧医疗、灾害监测、无障碍辅助和文化遗产保护。"
        "在设计系统时，应坚持以人为本，把人的安全、尊严、隐私和知情权放在效率之前。"
        "在评价成果时，应同时看精度、鲁棒性、公平性、能耗和社会影响。"
        "只有这样，计算机视觉的最新进展才能真正转化为可信、可控、可持续的生产力。"
    )

    doc.add_heading("六、展望", level=1)
    add_body_paragraph(
        doc,
        "第一，视觉模型会继续向统一多模态模型演进。未来模型可能同时处理图像、视频、音频、三维场景、传感器数据和机器人动作，并通过统一接口完成观察、理解、生成和控制。"
        "第二，长视频和长期记忆会成为关键能力。真实任务往往持续数分钟甚至数小时，模型需要记住目标、环境变化和任务进度，而不是只理解单帧图像。"
        "第三，三维和物理一致性会重新获得重要地位。生成式模型若要服务自动驾驶、机器人和工业仿真，就必须接受几何约束、动力学约束和可验证评估。"
    )
    add_body_paragraph(
        doc,
        "第四，高效部署会成为基础研究的重要指标。边缘设备、移动终端和机器人无法承受无限算力，动态计算、模型蒸馏、量化和小模型迁移将持续发展。"
        "第五，可信治理会从外部约束变成模型设计的一部分。未来视觉系统需要内置水印、数据来源记录、不确定性估计、拒答机制和审计接口。"
        "第六，开源生态和国产模型会更加重要。只有在可复现、可审计、可本地化部署的生态中，视觉算法才能更好服务教育、科研和产业升级。"
    )

    doc.add_heading("七、报告总结", level=1)
    add_body_paragraph(
        doc,
        "本文围绕“介绍算法与技术的最新进展”这一主题，梳理了2023—2026年计算机视觉从基础表征到世界模型的主要变化。"
        "总体来看，最新进展可以概括为三句话：第一，视觉模型正在基础模型化，分割、检测、描述和几何估计逐渐统一到可提示、可迁移的框架中；"
        "第二，视觉语言模型和生成式视频模型正在把视觉系统从静态识别推向多模态推理、内容生成和世界模拟；"
        "第三，三维视觉和具身智能正在把视觉能力连接到物理行动，使“看见”最终服务“理解、预测和执行”。"
    )
    add_body_paragraph(
        doc,
        "这些进展令人振奋，但也提醒我们不能把算法能力等同于社会价值。"
        "优秀的计算机视觉系统既要有高精度和高效率，也要有安全边界、数据合规、可解释机制和面向真实需求的应用设计。"
        "对学生而言，学习最新算法的意义不仅是掌握模型名称和论文结论，更是理解技术演进背后的科学问题、工程约束和价值责任。"
        "只有把专业学习、国家需求和社会责任结合起来，才能让计算机视觉技术在未来真正发挥积极作用。"
    )


def add_references(doc: Document) -> None:
    doc.add_heading("参考文献", level=1)
    refs = [
        "Oquab M, Darcet T, Moutakanni T, et al. DINOv2: Learning Robust Visual Features without Supervision[EB/OL]. arXiv:2304.07193, 2023. https://arxiv.org/abs/2304.07193",
        "Ravi N, Gabeur V, Hu Y T, et al. SAM 2: Segment Anything in Images and Videos[EB/OL]. arXiv:2408.00714, 2024. https://arxiv.org/abs/2408.00714",
        "Xiao B, Wu H, Xu W, et al. Florence-2: Advancing a Unified Representation for a Variety of Vision Tasks[EB/OL]. arXiv:2311.06242, 2023. https://arxiv.org/abs/2311.06242",
        "Cheng T, Song L, Ge Y, et al. YOLO-World: Real-Time Open-Vocabulary Object Detection[EB/OL]. arXiv:2401.17270, 2024. https://arxiv.org/abs/2401.17270",
        "Wang P, Bai S, Tan S, et al. Qwen2-VL: Enhancing Vision-Language Model's Perception of the World at Any Resolution[EB/OL]. arXiv:2409.12191, 2024. https://arxiv.org/abs/2409.12191",
        "Bai S, Chen K, Liu X, et al. Qwen2.5-VL Technical Report[EB/OL]. arXiv:2502.13923, 2025. https://arxiv.org/abs/2502.13923",
        "Gemini Team, Georgiev P, Lei V I, et al. Gemini 1.5: Unlocking Multimodal Understanding across Millions of Tokens of Context[EB/OL]. arXiv:2403.05530, 2024. https://arxiv.org/abs/2403.05530",
        "OpenAI. GPT-4o System Card[EB/OL]. 2024. https://openai.com/index/gpt-4o-system-card/",
        "Li B, Zhang Y, Guo D, et al. LLaVA-OneVision: Easy Visual Task Transfer[EB/OL]. arXiv:2408.03326, 2024. https://arxiv.org/abs/2408.03326",
        "Yang L, Kang B, Huang Z, et al. Depth Anything V2[EB/OL]. arXiv:2406.09414, 2024. https://arxiv.org/abs/2406.09414",
        "Wang J, Chen M, Karaev N, et al. VGGT: Visual Geometry Grounded Transformer[EB/OL]. arXiv:2503.11651, 2025. https://arxiv.org/abs/2503.11651",
        "Kerbl B, Kopanas G, Leimkühler T, et al. 3D Gaussian Splatting for Real-Time Radiance Field Rendering[EB/OL]. arXiv:2308.04079, 2023. https://arxiv.org/abs/2308.04079",
        "Charatan D, Li S, Tagliasacchi A, et al. pixelSplat: 3D Gaussian Splats from Image Pairs for Scalable Generalizable 3D Reconstruction[EB/OL]. arXiv:2312.12337, 2023. https://arxiv.org/abs/2312.12337",
        "Esser P, Kulal S, Blattmann A, et al. Scaling Rectified Flow Transformers for High-Resolution Image Synthesis[EB/OL]. arXiv:2403.03206, 2024. https://arxiv.org/abs/2403.03206",
        "Chen J, Wu Y, Luo S, et al. PIXART-δ: Fast and Controllable Image Generation with Latent Consistency Models[EB/OL]. arXiv:2401.05252, 2024. https://arxiv.org/abs/2401.05252",
        "Zhao W, Han Y, Tang J, et al. Dynamic Diffusion Transformer[EB/OL]. arXiv:2410.03456, 2024. https://arxiv.org/abs/2410.03456",
        "OpenAI. Video Generation Models as World Simulators[EB/OL]. 2024. https://openai.com/index/video-generation-models-as-world-simulators/",
        "Polyak A, Zohar A, Brown A, et al. Movie Gen: A Cast of Media Foundation Models[EB/OL]. arXiv:2410.13720, 2024. https://arxiv.org/abs/2410.13720",
        "Google DeepMind. Veo 3.1[EB/OL]. https://deepmind.google/models/veo/",
        "Google DeepMind. Genie 2: A Large-Scale Foundation World Model[EB/OL]. 2024. https://deepmind.google/blog/genie-2-a-large-scale-foundation-world-model/",
        "Kim M J, Pertsch K, Karamcheti S, et al. OpenVLA: An Open-Source Vision-Language-Action Model[EB/OL]. arXiv:2406.09246, 2024. https://arxiv.org/abs/2406.09246",
        "Black K, Brown N, Driess D, et al. π0: A Vision-Language-Action Flow Model for General Robot Control[EB/OL]. arXiv:2410.24164, 2024. https://arxiv.org/abs/2410.24164",
        "Beyer L, Steiner A, Pinto A S, et al. PaliGemma 2: A Family of Versatile VLMs for Transfer[EB/OL]. arXiv:2412.03555, 2024. https://arxiv.org/abs/2412.03555",
        "Laurençon H, Tronchon L, Cord M, et al. What Matters when Building Vision-Language Models?[EB/OL]. arXiv:2405.02246, 2024. https://arxiv.org/abs/2405.02246",
        "Assran M, Bardes A, Fan D, et al. V-JEPA 2: Self-Supervised Video Models Enable Understanding, Prediction and Planning[EB/OL]. arXiv:2506.09985, 2025. https://arxiv.org/abs/2506.09985",
        "国务院. 国务院关于印发新一代人工智能发展规划的通知[EB/OL]. 2017. https://www.gov.cn/zhengce/content/2017-07/20/content_5211996.htm",
        "国家互联网信息办公室等. 生成式人工智能服务管理暂行办法[EB/OL]. 2023. https://www.cac.gov.cn/2023-07/13/c_1690898327029107.htm",
    ]
    for idx, ref in enumerate(refs, 1):
        p = doc.add_paragraph()
        p.paragraph_format.first_line_indent = Cm(-0.74)
        p.paragraph_format.left_indent = Cm(0.74)
        p.paragraph_format.line_spacing = 1.2
        p.paragraph_format.space_after = Pt(4)
        run = p.add_run(f"[{idx}] {ref}")
        set_run_font(run, FONT_SONG, size=9.3)


def structural_audit(doc_path: Path) -> None:
    doc = Document(doc_path)
    text = "\n".join(p.text for p in doc.paragraphs)
    required = [
        "摘要",
        "关键词",
        "目录",
        "小组分工",
        "引言",
        "正文：算法与技术的最新进展",
        "思政融入",
        "展望",
        "报告总结",
        "参考文献",
    ]
    missing = [item for item in required if item not in text]
    if missing:
        raise RuntimeError(f"Missing required sections: {missing}")
    if len(doc.inline_shapes) < 1:
        raise RuntimeError("Expected at least one embedded figure.")
    if len(doc.tables) < 3:
        raise RuntimeError("Expected cover/division/summary tables.")
    if text.count("arXiv") < 15:
        raise RuntimeError("Reference list looks incomplete.")


def main() -> None:
    create_roadmap_figure(FIGURE_PATH)
    doc = Document()
    configure_document(doc)

    footer = doc.sections[0].footer.paragraphs[0]
    add_page_number(footer)

    add_cover(doc)
    add_abstract(doc)
    add_contents_and_division(doc)
    add_main_report(doc)
    add_references(doc)
    doc.save(OUT_DOCX)
    structural_audit(OUT_DOCX)
    print(OUT_DOCX)
    print(FIGURE_PATH)


if __name__ == "__main__":
    main()
