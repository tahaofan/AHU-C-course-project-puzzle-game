/**
 * @file    D_task.cpp
 * @brief   滚动条模块实现
 *        底部碎片栏分页显示（每页5块），翻页按钮切换，
 *        同时提供重新开始/返回主菜单功能。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include "main.h"

MOUSEMSG mouseMsg;
ScrollBar scrollBar;

/**
 * @brief 初始化滚动条：设置页码并关联碎片图片
 * @param level 当前关卡 (1~7)
 */
void InitScrollBar(int level) {
    scrollBar.pageIndex = 0;
    for (int i = 0; i < 12; ++i) {
        scrollBar.pieces[i] = &img_pieces[level - 1][i];
    }
}

/**
 * @brief 处理滚动条鼠标事件
 *        翻页按钮（3个竖排）→ 切换页码；
 *        重新开始按钮 → 重置当前关卡；
 *        返回菜单按钮 → 回到主菜单。
 */
void UpdateScrollBar() {
    while (MouseHit()) {
        mouseMsg = GetMouseMsg();
        if (mouseMsg.uMsg == WM_LBUTTONDOWN) {
            // 翻页按钮检测（3个竖排圆角按钮）
            for (int i = 0; i < 3; ++i) {
                int btnTop = BUTTON_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
                int btnBottom = btnTop + BUTTON_HEIGHT;
                bool inY = (mouseMsg.y >= btnTop && mouseMsg.y <= btnBottom);
                bool inX = (mouseMsg.x >= BUTTON_X - 5 && mouseMsg.x <= BUTTON_X + BUTTON_WIDTH + 5);
                if (inX && inY) {
                    scrollBar.pageIndex = i;
                    for (int j = 0; j < PIECE_COUNT; j++) {
                        if (pieces[j].state == IN_SCROLLBAR) {
                            pieces[j].isVisible = (pieces[j].pageIndex == scrollBar.pageIndex);
                        }
                    }
                    break;
                }
            }
            // 重新开始按钮（右上）
            if (mouseMsg.x >= 790 && mouseMsg.x <= 890 &&
                mouseMsg.y >= 10 && mouseMsg.y <= 110) {
                InitPuzzle(currentLevel);
                InitScrollBar(currentLevel);
                printf("[滚动条] 重新开始关卡 %d\n", currentLevel);
                return;
            }
            // 返回主菜单按钮（右上）
            if (mouseMsg.x >= 900 && mouseMsg.x <= 1000 &&
                mouseMsg.y >= 10 && mouseMsg.y <= 110) {
                returnToMainMenu();
            }
        }
    }
}

/**
 * @brief 绘制滚动条区域
 *        包括背景、翻页按钮、碎片展示、重新开始/返回按钮。
 */
void DrawScrollBar() {
    putimage(0, 0, &img_leveliconsbk[currentLevel - 1]);

    // 右上角功能按钮
    putimage(900, 10, &img_menuiconmask, NOTSRCERASE);
    putimage(900, 10, &img_menuicon, SRCINVERT);
    putimage(790, 10, &img_start_againmask, NOTSRCERASE);
    putimage(790, 10, &img_start_again, SRCINVERT);

    // 底部滚动条背景
    setfillcolor(RGB(80, 80, 80));
    solidrectangle(0, SCROLLBAR_Y, 1024, SCROLLBAR_Y + 6);
    setfillcolor(RGB(50, 50, 50));
    solidrectangle(0, SCROLLBAR_Y + 6, 1024, SCROLLBAR_Y + 96);
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(0, SCROLLBAR_Y + 96, 1024, SCROLLBAR_Y + SCROLLBAR_H);

    // 翻页按钮
    for (int i = 0; i < 3; ++i) {
        int btnY = BUTTON_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
        setfillcolor(scrollBar.pageIndex == i ? 0x4CAF50 : 0x555555);
        setlinecolor(RGB(200, 200, 200));
        fillroundrect(BUTTON_X, btnY,
            BUTTON_X + BUTTON_WIDTH, btnY + BUTTON_HEIGHT, 8, 8);

        settextstyle(24, 0, _T("Arial"));
        TCHAR numStr[] = { _T('1' + i), 0 };
        RECT textRect = { BUTTON_X, btnY, BUTTON_X + BUTTON_WIDTH, btnY + BUTTON_HEIGHT };
        settextcolor(RGB(50, 50, 50));
        drawtext(numStr, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        settextcolor(scrollBar.pageIndex == i ? RGB(240, 240, 240) : RGB(180, 180, 180));
        drawtext(numStr, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 绘制当前页可见的碎片
    for (int i = 0; i < PIECE_COUNT; ++i) {
        if (pieces[i].isVisible && pieces[i].state == IN_SCROLLBAR) {
            putimage_alpha(pieces[i].x, pieces[i].y, scrollBar.pieces[i]);
        }
    }
}
