/**
 * @file    B_task.cpp
 * @brief   关卡选择模块实现
 *        显示 7 个关卡图标（4+3 布局），点击后进入对应关卡。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include "main.h"

extern MOUSEMSG mouseMsg;

/*------------ 局部常量 ------------*/
static const int ICON_W = 128;      // 关卡图标宽度
static const int ICON_H = 72;      // 关卡图标高度
static const int H_SPACE = 30;     // 图标水平间距
static const int V_SPACE = 40;     // 图标垂直间距
static const int BASE_Y = 180;     // 第一行起始 Y

/**
 * @brief 关卡选择主循环：绘制界面并等待鼠标点击
 */
void select_level() {
    cleardevice();
    drawLevelSelect();
    while (gameState == LEVEL_SELECT) {
        if (MouseHit()) {
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONDOWN) {
                handleLevelSelectClick(mouseMsg.x, mouseMsg.y);
            }
        }
        Sleep(10);
    }
    cleardevice();
}

/**
 * @brief 绘制关卡选择界面
 *        背景 + 返回按钮 + 两行图标（第一行 4 个，第二行 3 个）
 */
void drawLevelSelect() {
    printf("[关卡选择] 绘制界面\n");
    cleardevice();
    putimage(0, 0, &img_choosebk);
    putimage(10, 10, &img_menuiconmask, NOTSRCERASE);
    putimage(10, 10, &img_menuicon, SRCINVERT);

    // 第一行：关卡 1~4
    int totalW = 4 * ICON_W + 3 * H_SPACE;
    int startX = (1024 - totalW) / 2;
    for (int i = 0; i < 4; i++) {
        int x = startX + i * (ICON_W + H_SPACE);
        putimage(x, BASE_Y, ICON_W, ICON_H, &img_levelicons[i], 0, 0);
    }

    // 第二行：关卡 5~7
    int row2Y = BASE_Y + ICON_H + V_SPACE;
    totalW = 3 * ICON_W + 2 * H_SPACE;
    startX = (1024 - totalW) / 2;
    for (int i = 4; i < 7; i++) {
        int x = startX + (i - 4) * (ICON_W + H_SPACE);
        putimage(x, row2Y, ICON_W, ICON_H, &img_levelicons[i], 0, 0);
    }

    FlushBatchDraw();
}

/**
 * @brief 处理关卡选择界面的点击事件
 * @param x, y 鼠标点击坐标
 *        返回按钮（左上角）→ 返回主菜单
 *        关卡图标 → 进入对应关卡
 */
void handleLevelSelectClick(int x, int y) {
    // 返回主菜单按钮
    if (x >= 10 && x <= 330 && y >= 10 && y <= 150) {
        printf("[关卡选择] 返回主菜单\n");
        returnToMainMenu();
        return;
    }

    // 第一行检测（关卡 1~4）
    int totalW = 4 * ICON_W + 3 * H_SPACE;
    int startX = (1024 - totalW) / 2;
    for (int i = 0; i < 4; i++) {
        int iconX = startX + i * (ICON_W + H_SPACE);
        if (x >= iconX && x <= iconX + ICON_W &&
            y >= BASE_Y && y <= BASE_Y + ICON_H) {
            currentLevel = i + 1;
            printf("[关卡选择] 选择关卡 %d\n", currentLevel);
            startGame(currentLevel);
            return;
        }
    }

    // 第二行检测（关卡 5~7）
    int row2Y = BASE_Y + ICON_H + V_SPACE;
    totalW = 3 * ICON_W + 2 * H_SPACE;
    startX = (1024 - totalW) / 2;
    for (int i = 0; i < 3; i++) {
        int iconX = startX + i * (ICON_W + H_SPACE);
        if (x >= iconX && x <= iconX + ICON_W &&
            y >= row2Y && y <= row2Y + ICON_H) {
            currentLevel = i + 5;
            printf("[关卡选择] 选择关卡 %d\n", currentLevel);
            startGame(i + 5);
            return;
        }
    }
}

void returnToMainMenu() {
    gameState = MAIN_MENU;
}

void startGame(int level) {
    gameState = IN_GAME;
}

