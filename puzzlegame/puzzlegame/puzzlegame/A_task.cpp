/**
 * @file    A_task.cpp
 * @brief   主菜单模块实现
 *        负责主菜单背景/按钮绘制、开始/退出交互、背景音乐播放。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include <stdio.h>
#include "main.h"
#include <easyx.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

ExMessage msg = { 0 };

/**
 * @brief 检测鼠标坐标是否在指定矩形区域内
 * @param mx, my  鼠标坐标
 * @param x, y    矩形左上角
 * @param w, h    矩形宽高
 * @return true 在区域内
 */
bool inArea(int mx, int my, int x, int y, int w, int h)
{
    return (mx > x && mx < x + w && my > y && my < y + h);
}

/**
 * @brief 检测左键单击是否落在按钮区域内
 * @return true 单击有效
 */
bool button(int x, int y, int w, int h, const char* text)
{
    return (msg.message == WM_LBUTTONDOWN && inArea(msg.x, msg.y, x, y, w, h));
}

/**
 * @brief 弹出退出确认对话框
 * @return true  用户确认退出（关闭图形窗口、停止音乐、退出进程）
 * @return false 用户取消
 */
bool change()
{
    HWND hnd = GetHWnd();
    SetWindowText(hnd, "拼图大闯关");
    int is_ok = MessageBox(hnd, "确认退出游戏？", "确认弹窗", MB_OKCANCEL);
    if (is_ok == IDOK)
    {
        printf("[退出] 用户确认退出\n");
        closegraph();
        mciSendString("stop music", NULL, 0, NULL);
        mciSendString("close music", NULL, 0, NULL);
        exit(0);
    }
    else if (is_ok == IDCANCEL)
    {
        printf("[退出] 用户取消\n");
        return false;
    }
    return false;
}

/**
 * @brief 绘制主菜单窗口
 *        显示背景、标题、开始/退出按钮，并播放背景音乐。
 * @return 0
 */
int start_window()
{
    cleardevice();
    putimage(0, 0, &img_menu);                     // 背景

    putimage(184, 394, &img_startmask, NOTSRCERASE);
    putimage(184, 394, &img_start, SRCINVERT);     // 开始游戏按钮

    putimage(597, 394, &img_exitmask, NOTSRCERASE);
    putimage(597, 394, &img_exit, SRCINVERT);      // 退出游戏按钮

    putimage(328, 166, &img_titlemask, NOTSRCERASE);
    putimage(328, 166, &img_title, SRCINVERT);     // 标题

    mciSendString("open assets/01.mp3 alias music", NULL, 0, NULL);
    mciSendString("play music repeat", NULL, 0, NULL);
    mciSendString("setaudio music volume to 160", NULL, 0, NULL);

    return 0;
}

/**
 * @brief 处理主菜单鼠标事件
 *        点击"开始游戏" → 进入关卡选择；
 *        点击"退出游戏" → 弹出确认框。
 */
void start_or_exit()
{
    if (peekmessage(&msg, EX_MOUSE))
    {
        BeginBatchDraw();
        if (button(218, 416, 260, 110, "开始游戏"))
        {
            printf("[菜单] 点击开始游戏\n");
            gameState = LEVEL_SELECT;
            mciSendString("stop music", NULL, 0, NULL);
            mciSendString("close music", NULL, 0, NULL);
        }
        if (button(618, 416, 260, 110, "退出游戏"))
        {
            printf("[菜单] 点击退出游戏\n");
            if (change())
            {
                closegraph();
                mciSendString("stop music", NULL, 0, NULL);
                mciSendString("close music", NULL, 0, NULL);
            }
        }
        EndBatchDraw();
        msg.message = 0;  // 清空消息，避免一次点击触发多次
    }
    Sleep(20);
}

