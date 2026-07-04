//E_task.cpp
#include <graphics.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <easyx.h>
#include "main.h"

using namespace std;

// 全局变量
bool isNextLevelHovered = false;
bool isReturnToSelectHovered = false;
bool isReturnToMenuHovered = false;

/*------------ 函数声明 ------------*/
void drawWinPopup();
void handleWinPopupClick(int x, int y);
void startNextLevel();


/*------------ 下一关 ------------*/
void startNextLevel() {
    currentLevel++;
    if (currentLevel > 7) {
        currentLevel = 1; // 循环关卡
    }
    gameState = IN_GAME;

}

/*------------ 绘制通关弹窗 ------------*/
void drawWinPopup() {

    static IMAGE gameBackground;
    if (gameBackground.getwidth() == 0) {  // 仅首次创建
        gameBackground.Resize(1024, 576);
    }
    getimage(&gameBackground, 0, 0, 1024, 576);

    // 弹窗循环
    BeginBatchDraw();
    while (gameState == IN_POP_UP_WINDOW)
    {
        putimage(0, 0, &gameBackground);
        // 绘制弹窗背景
        putimage(280, 100, &img_popupwindowmask, NOTSRCERASE);
        putimage(280, 100, &img_popupwindow, SRCINVERT);

        // 绘制选项按钮
        putimage(350, 290, &img_nextmask, NOTSRCERASE);//下一关
        putimage(350, 290, &img_next, SRCINVERT);//下一关

        putimage(550, 290, &img_backmenumask, NOTSRCERASE);//返回菜单
        putimage(550, 290, &img_backmenu, SRCINVERT);//返回菜单
        FlushBatchDraw();
        

        if (MouseHit()) { // 检测鼠标点击
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                handleWinPopupClick(msg.x, msg.y);
            }
        }

    }
}
/*------------ 处理通关弹窗点击事件 ------------*/
void handleWinPopupClick(int x, int y) {
    // 检测是否点击了下一关按钮
    if (x >= 350 && x <= 510 && y >= 290 && y <= 360) {
        startNextLevel();
        return;
    }

    // 检测是否点击了返回主菜单按钮
    if (x >= 550 && x <= 710 && y >= 290 && y <= 360) {
        returnToMainMenu();
        return;
    }
}

void runPuzzleGame() {
    loadresources();
    InitPuzzle(currentLevel);
    InitScrollBar(currentLevel);

    BeginBatchDraw(); // 开始双缓冲
    while (gameState == IN_GAME) {
        HandlePieceDrag();
        UpdateScrollBar();
        UpdatePuzzle();

        cleardevice(); // 每帧清屏
        DrawScrollBar();
        DrawPuzzle();
       
        if (CheckPuzzleComplete()) {
            gameState = IN_POP_UP_WINDOW;
        }

        FlushBatchDraw(); // 统一刷新
        Sleep(1);
    }
    EndBatchDraw(); // 结束双缓冲

}
