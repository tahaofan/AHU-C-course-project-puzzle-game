//F_task.h
#pragma once
#include <stdio.h>
#include <easyx.h>
#include <string>
using namespace std;
//定义全局图片变量
extern IMAGE img_menu;					//主菜单封面(尺寸看着来）
extern IMAGE img_choosebk;
extern IMAGE img_levelicons[7];		//关卡图片
extern IMAGE img_leveliconsbk[7];			//关卡图片背景
extern IMAGE img_title;			//拼图大闯关字
extern IMAGE img_titlemask;				//拼图大闯关字

extern IMAGE img_start;				//开始游戏
extern IMAGE img_startmask;				//开始游戏

extern IMAGE img_exit;					//退出游戏
extern IMAGE img_exitmask;

extern IMAGE img_menuicon;				//返回主菜单按钮
extern IMAGE img_menuiconmask;				//返回主菜单按钮

extern IMAGE img_start_again;
extern IMAGE img_start_againmask;

extern IMAGE img_backmenu;				//弹窗中返回主菜单
extern IMAGE img_backmenumask;				//弹窗中返回主菜单

extern IMAGE img_next;              //下一关
extern IMAGE img_nextmask;                 //下一关

extern IMAGE img_popupwindow;			//闯关成功后弹窗
extern IMAGE img_popupwindowmask;			//闯关成功后弹窗

extern IMAGE img_pieces[7][12];		//拼图碎片


// 修改后（适应16:9比例）
const int start_x = 160;        // 拼图区域起始X
const int start_y = 90;        // 拼图区域起始Y
const int grid_width = 160;    // 格子宽度（16的倍数）
const int grid_height = 90;    // 格子高度（9的倍数）
const int PIECE_COLS = 4;      // 横向4列
const int PIECE_ROWS = 3;      // 纵向3行


//定义碎片位置结构体
struct pieceposition { int x, y; };
//定义关卡数据结构，包括关卡图片路径，碎片的目标位置
struct LevelData {
    string imagepath;
    pieceposition pieces[12];          //碎片正确位置
};

typedef enum {
    IN_SCROLLBAR,
    IN_PUZZLE_AREA,
    LOCKED
} PieceState;

//定义碎片结构体
struct Piece
{
    int x, y;							//碎片目前位置
    int targetx, targety;				//目标位置
    PieceState state;
    BOOL isDragging;
    int pageIndex;
    bool isVisible;
    IMAGE* pieceImg;
};
enum GameState {
    MAIN_MENU,      // 主菜单
    LEVEL_SELECT,   // 关卡选择
    IN_GAME,        // 游戏中
    IN_POP_UP_WINDOW
};


extern GameState gameState;
void loadresources();					//加载图片资源			
LevelData getLevelData(int level);
extern GameState gameState;  // 全局游戏状态