/**
 * @file    main.cpp
 * @brief   程序入口，初始化窗口并驱动游戏主循环
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include <stdio.h>
#include <easyx.h>
#include "main.h"

/**
 * @brief 程序主入口
 *        初始化 1024x576 图形窗口，加载资源，根据 gameState
 *        状态机轮询执行主菜单、关卡选择、游戏进行、通关弹窗等模块。
 */
void main(void)
{
    initgraph(1024, 576);
    loadresources();
    GameState lastState = MAIN_MENU;

    while (true)
    {
        if (gameState != lastState) {
            printf("[状态切换] %d -> %d\n", lastState, gameState);
            lastState = gameState;
        }
        switch (gameState)
        {
        case MAIN_MENU:
            start_window();
            start_or_exit();
            break;
        case LEVEL_SELECT:
            select_level();
            break;
        case IN_GAME:
            runPuzzleGame();
            break;
        case IN_POP_UP_WINDOW:
            drawWinPopup();
            break;
        }
    }
    closegraph();
}
