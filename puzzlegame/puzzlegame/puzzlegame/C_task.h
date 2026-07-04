//----------- 修改后的 C_task.h -----------
#ifndef C_TASK_H
#define C_TASK_H

#include <graphics.h>
#include "F_task.h"

#define PIECE_COUNT 12
#define SNAP_RADIUS 80

// 分页初始化参数
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

#endif
