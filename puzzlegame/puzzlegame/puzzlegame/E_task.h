/**
 * @file    E_task.h
 * @brief   通关弹窗与游戏主循环模块
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#pragma once
#include <graphics.h>

const int MAX_LEVEL = 7;  // 最大关卡数

extern int currentLevel;
extern int elapsedTime;
extern bool isNextLevelHovered;
extern bool isReturnToSelectHovered;
extern bool isReturnToMenuHovered;

void drawWinPopup();
void handleWinPopupClick(int x, int y);
void startNextLevel();
void runPuzzleGame();

