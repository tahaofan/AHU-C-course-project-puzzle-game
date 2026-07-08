/**
 * @file    C_task.cpp
 * @brief   拼图核心逻辑实现
 *        管理 12 块拼图的状态（待选区/拼图区/锁定），
 *        处理鼠标拖拽、网格吸附、完成判定。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include "main.h"

Piece pieces[PIECE_COUNT];
int currentLevel = 1;

/**
 * @brief 获取离 (x, y) 最近的网格对齐坐标
 * @param x, y 当前坐标
 * @return 对齐后的左上角坐标
 */
POINT getNearestGrid(int x, int y) {
    int col = (int)round((x - start_x) / (float)grid_width);
    int row = (int)round((y - start_y) / (float)grid_height);
    col = max(0, min(col, PIECE_COLS - 1));
    row = max(0, min(row, PIECE_ROWS - 1));
    return { start_x + col * grid_width, start_y + row * grid_height };
}

/**
 * @brief 初始化指定关卡的拼图
 *        将 12 块碎片随机摆放在滚动条区域，设置目标位置。
 * @param level 关卡编号（1~7）
 */
void InitPuzzle(int level) {
    LevelData data = getLevelData(level);

    for (int i = 0; i < PIECE_COUNT; i++) {
        pieces[i].state = IN_SCROLLBAR;
        pieces[i].pageIndex = i / piecesPerPage;
        // 初始只显示第一页，其他页不可见
        pieces[i].isVisible = (pieces[i].pageIndex == 0);
        pieces[i].x = 100 + (i % 5) * (grid_width + 20);
        pieces[i].y = SCROLLBAR_Y + 20;
        pieces[i].targetx = data.pieces[i].x;
        pieces[i].targety = data.pieces[i].y;
        pieces[i].isDragging = false;
        pieces[i].pieceImg = &img_pieces[level - 1][i];
        printf("[Init] Piece[%d] Target: (%d, %d)\n", i, data.pieces[i].x, data.pieces[i].y);
    }
}

/**
 * @brief 处理鼠标拖拽拼图块
 *        按下 → 选中拼图块并切换状态；
 *        移动 → 实时跟随鼠标；
 *        松开 → 停止拖拽。
 */
void HandlePieceDrag() {
    static int dragIndex = -1;
    ExMessage msg;

    if (peekmessage(&msg, EM_MOUSE)) {
        if (msg.message == WM_LBUTTONDOWN) {
            for (int i = 0; i < PIECE_COUNT; i++) {
                if (pieces[i].isVisible &&
                    pieces[i].state != LOCKED &&
                    msg.x >= pieces[i].x && msg.x <= pieces[i].x + grid_width &&
                    msg.y >= pieces[i].y && msg.y <= pieces[i].y + grid_height)
                {
                    dragIndex = i;
                    pieces[i].isDragging = true;
                    pieces[i].state = IN_PUZZLE_AREA;
                    pieces[i].isVisible = true;
                    break;
                }
            }
        }
        else if (msg.message == WM_MOUSEMOVE && dragIndex != -1) {
            pieces[dragIndex].x = msg.x - grid_width / 2;
            pieces[dragIndex].y = msg.y - grid_height / 2;
        }
        else if (msg.message == WM_LBUTTONUP && dragIndex != -1) {
            pieces[dragIndex].isDragging = false;
            dragIndex = -1;
        }
    }
}

/**
 * @brief 检查所有拼图块是否全部锁定（拼图完成）
 * @return true 全部就位
 */
bool CheckPuzzleComplete() {
    for (int i = 0; i < PIECE_COUNT; i++) {
        if (pieces[i].state != LOCKED)
            return false;
    }
    return true;
}

/**
 * @brief 更新拼图状态：对拼图区且未拖拽的块执行网格吸附
 */
void UpdatePuzzle() {
    for (int i = 0; i < PIECE_COUNT; i++) {
        if (pieces[i].state == IN_PUZZLE_AREA && !pieces[i].isDragging) {
            POINT target = getNearestGrid(pieces[i].x, pieces[i].y);
            pieces[i].x = target.x;
            pieces[i].y = target.y;
            if (pieces[i].x == pieces[i].targetx && pieces[i].y == pieces[i].targety) {
                pieces[i].state = LOCKED;
                printf("[吸附] 拼图 %d 已就位 (%d,%d)\n", i, pieces[i].x, pieces[i].y);
            } else {
                printf("[吸附] 拼图 %d 未达目标 (%d,%d)\n", i, pieces[i].x, pieces[i].y);
            }
        }
    }
}

/**
 * @brief 绘制拼图区域网格及所有已拖出的拼图块
 */
void DrawPuzzle() {
    // 网格线
    setlinecolor(RGB(200, 200, 200));
    for (int x = start_x; x <= start_x + PIECE_COLS * grid_width; x += grid_width)
        line(x, start_y, x, start_y + PIECE_ROWS * grid_height);
    for (int y = start_y; y <= start_y + PIECE_ROWS * grid_height; y += grid_height)
        line(start_x, y, start_x + PIECE_COLS * grid_width, y);

    // 绘制已被拖出的拼图块
    for (int i = 0; i < PIECE_COUNT; i++) {
        if (pieces[i].state != IN_SCROLLBAR) {
            putimage_alpha(pieces[i].x, pieces[i].y, pieces[i].pieceImg);
            if (pieces[i].isDragging) {
                setlinecolor(YELLOW);
                rectangle(pieces[i].x, pieces[i].y,
                    pieces[i].x + grid_width, pieces[i].y + grid_height);
            }
        }
    }

    // 标记所有目标位置（绿点）
    setfillcolor(0x00FF00);
    for (int i = 0; i < PIECE_COUNT; i++) {
        fillcircle(pieces[i].targetx, pieces[i].targety, 5);
    }
}

/**
 * @brief 绘制带透明通道的图片（逐像素复制）
 * @param x, y 绘制位置
 * @param img  源图片指针
 */
void putimage_alpha(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    DWORD* src = GetImageBuffer(img);
    IMAGE* pWorkingImg = GetWorkingImage();
    DWORD* dst = GetImageBuffer(pWorkingImg);

    for (int iy = 0; iy < h; iy++) {
        for (int ix = 0; ix < w; ix++) {
            int pos = (y + iy) * 1024 + (x + ix);
            if (pos >= 0 && pos < 1024 * 576) {
                dst[pos] = src[iy * w + ix];
            }
        }
    }
}

