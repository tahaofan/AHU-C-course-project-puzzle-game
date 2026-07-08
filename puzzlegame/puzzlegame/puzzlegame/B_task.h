/**
 * @file    B_task.h
 * @brief   关卡选择模块 —— 关卡网格展示、点击选关、返回主菜单
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#pragma once
#include <stdio.h>
#include <easyx.h>
#include <string>
using namespace std;

void drawLevelSelect();
void handleLevelSelectClick(int x, int y);
void returnToMainMenu();
void startGame(int level);
void select_level();

