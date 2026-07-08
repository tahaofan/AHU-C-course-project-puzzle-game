/**
 * @file    E_task.cpp
 * @brief   通关弹窗与游戏主循环实现
 *        拼图完成时弹出通关弹窗，提供"下一关"和"返回菜单"选项；
 *        runPuzzleGame 为游戏主循环，驱动拖拽、更新、绘制。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <easyx.h>
#include "main.h"

using namespace std;

bool isNextLevelHovered = false;
bool isReturnToSelectHovered = false;
bool isReturnToMenuHovered = false;

/**
 * @brief 进入下一关，若超过最大关卡则回到第 1 关
 */
void startNextLevel() {
    currentLevel++;
    if (currentLevel > MAX_LEVEL) {
        currentLevel = 1;
    }
    gameState = IN_GAME;
}

/**
 * @brief 绘制通关弹窗
 *        保存当前画面作为背景，在上面绘制弹窗和按钮，等待点击。
 */
void drawWinPopup() {
    static IMAGE gameBackground;
    if (gameBackground.getwidth() == 0) {
        gameBackground.Resize(1024, 576);
    }
    getimage(&gameBackground, 0, 0, 1024, 576);

    BeginBatchDraw();
    while (gameState == IN_POP_UP_WINDOW)
    {
        putimage(0, 0, &gameBackground);
        putimage(280, 100, &img_popupwindowmask, NOTSRCERASE);
        putimage(280, 100, &img_popupwindow, SRCINVERT);

        putimage(350, 290, &img_nextmask, NOTSRCERASE);
        putimage(350, 290, &img_next, SRCINVERT);          // 下一关

        putimage(550, 290, &img_backmenumask, NOTSRCERASE);
        putimage(550, 290, &img_backmenu, SRCINVERT);      // 返回菜单

        FlushBatchDraw();

        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                handleWinPopupClick(msg.x, msg.y);
            }
        }
    }
}

/**
 * @brief 处理通关弹窗的点击事件
 * @param x, y 鼠标坐标
 *        "下一关" → startNextLevel
 *        "返回菜单" → returnToMainMenu
 */
void handleWinPopupClick(int x, int y) {
    if (x >= 350 && x <= 510 && y >= 290 && y <= 360) {
        startNextLevel();
        return;
    }
    if (x >= 550 && x <= 710 && y >= 290 && y <= 360) {
        returnToMainMenu();
    }
}

/**
 * @brief 游戏主循环
 *        初始化关卡数据，循环处理拖拽、滚动条、拼图更新，
 *        完成拼图后切换到通关弹窗状态。
 */
void runPuzzleGame() {
    loadresources();
    InitPuzzle(currentLevel);
    InitScrollBar(currentLevel);

    BeginBatchDraw();
    while (gameState == IN_GAME) {
        HandlePieceDrag();
        UpdateScrollBar();
        UpdatePuzzle();

        cleardevice();
        DrawScrollBar();
        DrawPuzzle();

        if (CheckPuzzleComplete()) {
            gameState = IN_POP_UP_WINDOW;
        }

        FlushBatchDraw();
        Sleep(1);
    }
    EndBatchDraw();
}
