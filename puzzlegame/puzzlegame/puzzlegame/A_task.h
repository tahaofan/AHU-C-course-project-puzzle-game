/**
 * @file    A_task.h
 * @brief   主菜单模块 —— 开始界面显示、按钮交互、退出确认
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#pragma once
#include <stdio.h>
#include <easyx.h>
#include <windows.h>
#include <mmsystem.h>
#include "F_task.h"
#pragma comment(lib, "winmm.lib")

bool inArea(int mx, int my, int x, int y, int w, int h);          // 矩形区域命中检测
bool button(int x, int y, int w, int h, const char* text);        // 按钮点击检测
bool change();                                                     // 退出确认弹窗
int  start_window();                                               // 绘制主菜单界面
void start_or_exit();                                              // 处理主菜单鼠标事件
