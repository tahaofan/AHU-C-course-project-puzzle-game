/**
 * @file    F_task.h
 * @brief   全局资源与数据结构定义
 *        声明所有 IMAGE 全局变量、拼图/关卡数据结构、
 *        网格布局常量及游戏状态枚举。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#pragma once
#include <stdio.h>
#include <easyx.h>
#include <string>
using namespace std;

/*------------ 图片资源全局变量 ------------*/
extern IMAGE img_menu;                  // 主菜单背景
extern IMAGE img_choosebk;              // 关卡选择背景
extern IMAGE img_levelicons[7];         // 关卡图标（彩色）
extern IMAGE img_leveliconsbk[7];       // 关卡图标（黑白/背景）

extern IMAGE img_title;                 // 标题（默认）
extern IMAGE img_titlemask;             // 标题（悬停）

extern IMAGE img_start;                 // 开始游戏（默认）
extern IMAGE img_startmask;             // 开始游戏（悬停）

extern IMAGE img_exit;                  // 退出游戏（默认）
extern IMAGE img_exitmask;              // 退出游戏（悬停）

extern IMAGE img_menuicon;              // 返回菜单按钮（默认）
extern IMAGE img_menuiconmask;          // 返回菜单按钮（悬停）

extern IMAGE img_start_again;           // 重新开始（默认）
extern IMAGE img_start_againmask;       // 重新开始（悬停）

extern IMAGE img_backmenu;              // 返回菜单（默认）
extern IMAGE img_backmenumask;          // 返回菜单（悬停）

extern IMAGE img_next;                  // 下一关（默认）
extern IMAGE img_nextmask;              // 下一关（悬停）

extern IMAGE img_popupwindow;           // 通关弹窗（默认）
extern IMAGE img_popupwindowmask;       // 通关弹窗（悬停）

extern IMAGE img_pieces[7][12];         // 拼图碎片（7关×12块）

/*------------ 拼图网格常量 ------------*/
const int start_x = 160;        // 拼图区域左上角 X
const int start_y = 90;         // 拼图区域左上角 Y
const int grid_width = 160;     // 网格单元格宽度
const int grid_height = 90;     // 网格单元格高度
const int PIECE_COLS = 4;       // 列数
const int PIECE_ROWS = 3;       // 行数

/*------------ 数据结构 ------------*/
// 碎片目标位置坐标
struct pieceposition { int x, y; };

// 关卡数据：图片路径 + 12块碎片的正确位置
struct LevelData {
    string imagepath;
    pieceposition pieces[12];
};

// 碎片状态枚举
typedef enum {
    IN_SCROLLBAR,    // 在滚动条区（未拖出）
    IN_PUZZLE_AREA,  // 在拼图区（已拖出但未锁定）
    LOCKED           // 已锁定到正确位置
} PieceState;

// 拼图碎片结构体
struct Piece {
    int x, y;               // 碎片当前坐标
    int targetx, targety;   // 目标正确坐标
    PieceState state;       // 当前状态
    BOOL isDragging;        // 是否正在被拖拽
    int pageIndex;          // 所在页码
    bool isVisible;         // 是否可见
    IMAGE* pieceImg;        // 碎片图片指针
};

// 游戏状态枚举
enum GameState {
    MAIN_MENU,       // 主菜单
    LEVEL_SELECT,    // 关卡选择
    IN_GAME,         // 游戏进行中
    IN_POP_UP_WINDOW // 通关弹窗
};

extern GameState gameState;

void loadresources();
LevelData getLevelData(int level);
