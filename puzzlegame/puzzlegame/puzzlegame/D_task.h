/**
 * @file    D_task.h
 * @brief   滚动条模块 —— 拼图碎片分页显示与翻页交互
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#pragma once
#include "F_task.h"

// 滚动条区域布局参数
const int SCROLLBAR_Y = 450;           // 滚动条起始 Y
const int SCROLLBAR_H = 126;           // 滚动条总高度
const int PIECE_WIDTH = 160;           // 碎片展示宽度
const int PIECE_HEIGHT = 90;           // 碎片展示高度
const int PIECE_SPACING = 20;          // 碎片水平间距
const int VISIBLE_PIECES = 5;          // 每页可见碎片数
const int VERTICAL_PADDING = 6;        // 顶部装饰条高度

// 翻页按钮尺寸
const int BUTTON_WIDTH = 20;
const int BUTTON_HEIGHT = 20;
const int BUTTON_X = 20;
const int BUTTON_Y = SCROLLBAR_Y + 20;
const int BUTTON_SPACING = 10;

// 滚动条数据结构
struct ScrollBar {
    int pageIndex;          // 当前页码 (0~2)
    IMAGE* pieces[12];      // 碎片图片指针数组
};

extern ScrollBar scrollBar;

void InitScrollBar(int level);
void UpdateScrollBar();
void DrawScrollBar();
