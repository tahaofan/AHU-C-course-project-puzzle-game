/**
 * @file    C_task.h
 * @brief   拼图核心逻辑模块 —— 拼图块数据管理、拖拽、吸附、完成判定
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#pragma once
#include <graphics.h>
#include "F_task.h"

#define PIECE_COUNT 12
#define SNAP_RADIUS 80

// 滚动条分页参数
const int piecesPerPage = 5;
const int pageCount = 3;

extern Piece pieces[PIECE_COUNT];
extern int currentLevel;

void InitPuzzle(int level);
void HandlePieceDrag();
void UpdatePuzzle();
bool CheckPuzzleComplete();
void DrawPuzzle();
void putimage_alpha(int x, int y, IMAGE* img);
