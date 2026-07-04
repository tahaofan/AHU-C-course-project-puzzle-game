//----------- D_task.h 精简版本 -----------
#ifndef D_TASK_H
#define D_TASK_H

#include "F_task.h" // 包含基础定义和IMAGE数组

// 碎片栏几何参数
const int SCROLLBAR_Y = 450;       // 起始Y坐标（距窗口顶部）
const int SCROLLBAR_H = 126;       // 总高度=90+6+30（碎片+装饰+轨道）
const int PIECE_WIDTH = 160;       // 碎片宽度
const int PIECE_HEIGHT = 90;       // 碎片高度
const int PIECE_SPACING = 20;      // 碎片水平间距
const int VISIBLE_PIECES = 5;      // 可视碎片数量
const int VERTICAL_PADDING = 6;    // 碎片区顶部装饰线高度


const int BUTTON_WIDTH = 20;       // 增大按钮尺寸
const int BUTTON_HEIGHT = 20;
const int BUTTON_X = 20;           // 按钮起始X坐标
const int BUTTON_Y = SCROLLBAR_Y + 20; // 按钮Y坐标
const int BUTTON_SPACING = 10;     // 垂直间距

// 滚动条控制结构
struct ScrollBar {
    int pageIndex;         // 当前页码（0-2）
    IMAGE* pieces[12];      // 碎片指针数组
};

extern ScrollBar scrollBar; // 全局实例

// 功能接口
void InitScrollBar(int level);  // 初始化
void UpdateScrollBar();         // 更新逻辑
void DrawScrollBar();           // 绘制

#endif
