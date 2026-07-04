//A_task.h

//头文件
#include <stdio.h>
#include <easyx.h>
#include <windows.h>
#include <mmsystem.h>
#include "F_task.h"
#pragma comment(lib, "winmm.lib")

//定义函数
bool inArea(int mx, int my, int x, int y, int w, int h);  //明确区域
bool button(int x, int y, int w, int h, const char* text); //此区域中用鼠标左键点击会显示信息
bool change();										//
int start_window();									//绘制开始界面窗口
void start_or_exit();
