import math


def progress_bar(progress: float, width: int):
    # 0 <= progress <= 1
    progress = min(1, max(0, progress))
    whole_width = math.floor(progress * width)
    remainder_width = (progress * width) % 1
    part_width = math.floor(remainder_width * 8)
    part_char = [" ", "▏", "▎", "▍", "▌", "▋", "▊", "▉"][part_width]
    if (width - whole_width - 1) < 0:
        part_char = ""
    line = "[" + "█" * whole_width + part_char + " " * (width - whole_width - 1) + "]"
    return line
