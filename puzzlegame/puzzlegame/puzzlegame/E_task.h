//----------- 修改 E_task.h -----------
#ifndef E_TASK_H
#define E_TASK_H

#include <graphics.h>

// 游戏常量（移至此处定义）
const int MAX_LEVEL = 7;  // 统一定义

// 全局变量声明
extern int currentLevel;
extern int elapsedTime;
extern bool isNextLevelHovered;
extern bool isReturnToSelectHovered;
extern bool isReturnToMenuHovered;

// 函数声明
void drawWinPopup();
void handleWinPopupClick(int x, int y);
void startNextLevel();
void runPuzzleGame();

#endif
