//----------- 修改后的 C_task.cpp -----------
#include "main.h"


Piece pieces[PIECE_COUNT];
int currentLevel = 1;
POINT getNearestGrid(int x, int y) {
    // 计算相对于拼图区域的浮点坐标
    float relativeX = (x - start_x) / (float)grid_width;
    float relativeY = (y - start_y) / (float)grid_height;

    // 四舍五入取最近的网格索引
    int col = static_cast<int>(round(relativeX));
    int row = static_cast<int>(round(relativeY));

    // 边界约束
    col = max(0, min(col, PIECE_COLS - 1));
    row = max(0, min(row, PIECE_ROWS - 1));

    return {
        start_x + col * grid_width, 
        start_y + row * grid_height 
    };
}

void InitPuzzle(int level) {
    LevelData data = getLevelData(level);


    // 初始化所有拼图块到滚动条区域
    for (int i = 0; i < PIECE_COUNT; i++) {

        pieces[i].state = IN_SCROLLBAR;
        pieces[i].pageIndex = i / piecesPerPage;
        pieces[i].isVisible = (pieces[i].pageIndex == 0); // 初始显示第一页
            // 如果碎片已在拼图区，则忽略页码限制
        pieces[i].isVisible = (pieces[i].state == IN_SCROLLBAR) ?
            (pieces[i].pageIndex == 0) : true;
        int col = rand() % 5;
        pieces[i].x = 100 + (i % 5) * (grid_width + 20); // 每行显示5个
        pieces[i].y = SCROLLBAR_Y + 20;
        pieces[i].targetx = data.pieces[i].x;
        pieces[i].targety = data.pieces[i].y;

        pieces[i].isDragging = false;
        pieces[i].pieceImg = &img_pieces[level - 1][i];
        // 在 InitPuzzle 中添加调试输出
        printf("Piece[%d] Target: (%d, %d)\n", i, data.pieces[i].x, data.pieces[i].y);
    }
}

// 修改后的拖拽处理
void HandlePieceDrag() {
    static int dragIndex = -1;
    ExMessage msg;

    if (peekmessage(&msg, EM_MOUSE)) {
        if (msg.message == WM_LBUTTONDOWN) {
            for (int i = 0; i < PIECE_COUNT; i++) {
                if (pieces[i].isVisible &&                    // <-- 新增条件
                    pieces[i].state !=LOCKED &&
                    msg.x >= pieces[i].x && msg.x <= pieces[i].x + grid_width &&
                    msg.y >= pieces[i].y && msg.y <= pieces[i].y + grid_height)
                {
                    dragIndex = i;
                    pieces[i].isDragging = true;
                    pieces[i].state = IN_PUZZLE_AREA;  // 关键修改：更新状态
                    pieces[i].isVisible = true;  // 新增：强制可见
                    break;
                }
            }
        }
        else if (msg.message == WM_MOUSEMOVE && dragIndex != -1) {
            // 实时显示拖拽位置（不立即吸附）
            pieces[dragIndex].x = msg.x - grid_width / 2;
            pieces[dragIndex].y = msg.y - grid_height / 2;
        }
        else if (msg.message == WM_LBUTTONUP && dragIndex != -1) {
            pieces[dragIndex].isDragging = false;           

            dragIndex = -1;
        }
    }
}



bool CheckPuzzleComplete() {
    for (int i = 0; i < PIECE_COUNT; i++) {
        // 双重验证：状态+位置
        if (pieces[i].state != LOCKED)
            return false;

    }
    return true;
}

void UpdatePuzzle() {
    for (int i = 0; i < PIECE_COUNT; i++) {
        if (pieces[i].state == IN_PUZZLE_AREA&& !pieces[i].isDragging) {
            POINT target = getNearestGrid(pieces[i].x, pieces[i].y);
            
                // 对齐到最近网格
                pieces[i].x = target.x ; 
                pieces[i].y = target.y ;
                if (pieces[i].x == pieces[i].targetx && pieces[i].y == pieces[i].targety) {
                    pieces[i].state = LOCKED;
                    printf("[调试] 拼图 %d 已锁定！坐标(%d,%d)\n", i, pieces[i].x, pieces[i].y);
                }
                else {
                    printf("[调试]拼图%d未锁定！坐标(%d,%d)\n", i, pieces[i].x, pieces[i].y);

                }
            
        }
    }
}


void DrawPuzzle() {
    setlinecolor(RGB(200, 200, 200));
    for (int x = start_x; x <= start_x + PIECE_COLS * grid_width; x += grid_width) {
        line(x, start_y, x, start_y + PIECE_ROWS * grid_height);
    }
    for (int y = start_y; y <= start_y + PIECE_ROWS * grid_height; y += grid_height) {
        line(start_x, y, start_x + PIECE_COLS * grid_width, y);
    }

    // 绘制拼图块
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

    // 绘制目标位置（绿色圆点）
    setfillcolor(0x00FF00); // 纯绿色
    for (int i = 0; i < PIECE_COUNT; i++) {
        // 关键点：必须直接使用 target 坐标
        fillcircle(pieces[i].targetx, pieces[i].targety, 5);
    }
}

void putimage_alpha(int x, int y, IMAGE* img) {
    int w = img->getwidth();
    int h = img->getheight();
    DWORD* src = GetImageBuffer(img);
    IMAGE* pWorkingImg = GetWorkingImage(); // 获取当前绘图设备
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
