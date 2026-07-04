
//A_task.cpp
//头文件
#include <stdio.h>
#include "main.h"
#include <easyx.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")  

ExMessage msg = { 0 };

//明确一个区域
bool inArea(int mx, int my, int x, int y, int w, int h)
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}

//此区域中用鼠标左键点击会显示信息
bool button(int x, int y, int w, int h, const char* text)
{
	if (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h))
	{
		return true;
	}
	return false;
}
bool change()
{
	HWND hnd = GetHWnd();

	SetWindowText(hnd, "很高兴认识你");

	int is_ok = MessageBox(hnd, "HXD，真的不再玩一会儿吗？","确认窗口", MB_OKCANCEL);
	if (is_ok == IDOK)
	{
		printf("你点击了OK\n");
		closegraph();
		mciSendString("stop music", NULL, 0, NULL);
		mciSendString("close music", NULL, 0, NULL);

		exit(0);
	}
	else if (is_ok == IDCANCEL)
	{
		printf("你点击了cancel\n");
		return false;
	}
	return false;
}


  //主函数，有关窗口绘制以及音乐播放
int start_window()
{
	cleardevice();

	putimage(0, 0, &img_menu);  //主菜单封面

	putimage(184, 394, &img_startmask, NOTSRCERASE);  //开始游戏
	putimage(184, 394, &img_start, SRCINVERT);  //开始游戏

	putimage(597, 394, &img_exitmask, NOTSRCERASE);  //结束游戏
	putimage(597, 394, &img_exit, SRCINVERT);  //结束游戏

	putimage(328, 166, &img_titlemask, NOTSRCERASE);   //标题
	putimage(328, 166, &img_title, SRCINVERT);   //标题

	mciSendString("open assets/01.mp3 alias music", NULL, 0, NULL);
	mciSendString("play music repeat", NULL, 0, NULL);
	mciSendString("setaudio music volume to 160", NULL, 0, NULL); //调节音量


	return 0;
}

void start_or_exit()
{

	if (peekmessage(&msg, EX_MOUSE))
	{

		BeginBatchDraw();
		if (button(218, 416, 260, 110, "开始游戏"))
		{
			printf("开始游戏\n");

			gameState = LEVEL_SELECT;
			mciSendString("stop music", NULL, 0, NULL);
			mciSendString("close music", NULL, 0, NULL);
		}
		if (button(618, 416, 260, 110, "结束游戏"))
		{
			printf("结束游戏\n");
			if (change())  // 如果用户点击确认
			{
				closegraph();
				mciSendString("stop music", NULL, 0, NULL);
				mciSendString("close music", NULL, 0, NULL);

			}
		}
		EndBatchDraw();

		msg.message = 0;  //重置，确保点击按钮之后只打开一个文件
	}
	Sleep(20);  //降低内存

}