//main.cpp
//主函数
#include <stdio.h>
#include <easyx.h>
#include "main.h"

void main(void)
{
	initgraph(1024, 576);
	loadresources();
	GameState lastState = MAIN_MENU; // 初始状态

	while (true)
	{
		if (gameState != lastState) {
			printf("状态变更: %d -> %d\n", lastState, gameState);
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