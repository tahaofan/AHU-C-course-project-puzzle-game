//B_task.h
#pragma once
#include <stdio.h>
#include <easyx.h>
#include <string>
using namespace std;
extern void drawLevelSelect();
extern void handleLevelSelectClick(int x, int y);
extern void returnToMainMenu();
extern void startGame(int level);
extern void select_level();