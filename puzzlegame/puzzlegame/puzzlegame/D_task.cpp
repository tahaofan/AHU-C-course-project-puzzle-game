//----------- D_task.cpp 优化版本 -----------
#include "main.h"

MOUSEMSG mouseMsg;                  // 鼠标消息
ScrollBar scrollBar;
void InitScrollBar(int level) {
    scrollBar.pageIndex = 0;
    // 关联碎片图片
    for (int i = 0; i < 12; ++i) {
        scrollBar.pieces[i] = &img_pieces[level - 1][i];
    }
    
}

//原始按钮检测参数:
//| 按钮 | X范围 | Y起始 | Y结束   |
//|  1 | 20 - 40 | 470 | 490    |
//|  2 | 20 - 40 | 500 | 520    |
//|  3 | 20 - 40 | 530 | 550 |

void UpdateScrollBar() {
    while (MouseHit()) {
        mouseMsg = GetMouseMsg();
        if (mouseMsg.uMsg == WM_LBUTTONDOWN) {
            // 调试输出

            printf("点击坐标: (%d, %d)\n", mouseMsg.x, mouseMsg.y);
            printf("原始按钮检测参数:\n");
            printf("| 按钮 |   X范围  |   Y起始   |   Y结束   |\n");
            // 垂直排列按钮检测
            for (int i = 0; i < 3; ++i) {
                int btnTop = BUTTON_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
                int btnBottom = btnTop + BUTTON_HEIGHT;

                // 扩大横向点击范围到整个左侧区域
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
            bool iny = (mouseMsg.y >= 10 && mouseMsg.y <= 110);
            bool inx1 = (mouseMsg.x >= 790 && mouseMsg.x <= 890);
            bool inx2 = (mouseMsg.x >= 900 && mouseMsg.x <= 1000);
            if (inx1 && iny) {
                // 重新初始化拼图
                InitPuzzle(currentLevel);
                // 重置滚动条
                InitScrollBar(currentLevel);
                // 调试输出
                printf("重新开始关卡%d\n", currentLevel);
                break;
            }
            if (inx2 && iny) {
                returnToMainMenu();
            }
        }
    }
}

void DrawScrollBar() {

    
    putimage(0, 0, &img_leveliconsbk[currentLevel-1]);

//绘制按钮
    putimage(900, 10, &img_menuiconmask, NOTSRCERASE);
    putimage(900, 10, &img_menuicon, SRCINVERT);
    putimage(790, 10, &img_start_againmask, NOTSRCERASE);
    putimage(790, 10, &img_start_again, SRCINVERT);
   
    // 绘制背景（保持原样）
    setfillcolor(RGB(80, 80, 80));
    solidrectangle(0, SCROLLBAR_Y, 1024, SCROLLBAR_Y + 6);
    setfillcolor(RGB(50, 50, 50));
    solidrectangle(0, SCROLLBAR_Y + 6, 1024, SCROLLBAR_Y + 96);
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(0, SCROLLBAR_Y + 96, 1024, SCROLLBAR_Y + SCROLLBAR_H);

    // 绘制垂直排列的按钮
    for (int i = 0; i < 3; ++i) {
        int btnY = BUTTON_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);

        // 按钮背景（带2px边框）
        setfillcolor(scrollBar.pageIndex == i ? 0x4CAF50 : 0x555555);
        setlinecolor(RGB(200, 200, 200));
        fillroundrect(BUTTON_X, btnY,
            BUTTON_X + BUTTON_WIDTH, btnY + BUTTON_HEIGHT, 8, 8);

        // 按钮数字（带文字阴影）
        settextstyle(24, 0, _T("Arial"));
        TCHAR numStr[] = { _T('1' + i), 0 };
        RECT textRect = { BUTTON_X, btnY, BUTTON_X + BUTTON_WIDTH, btnY + BUTTON_HEIGHT };

        settextcolor(RGB(50, 50, 50));
        drawtext(numStr, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        settextcolor(scrollBar.pageIndex == i ? RGB(240, 240, 240) : RGB(180, 180, 180));
        drawtext(numStr, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    // 绘制碎片（向右偏移避开按钮）
    int startIndex = scrollBar.pageIndex * 5;
    int xPos = BUTTON_X + BUTTON_WIDTH + 20; // 按钮右侧留出50px
    int maxWidth = 1024 - xPos; // 计算可用宽度

    for (int i = 0; i < PIECE_COUNT; ++i) {
        if (pieces[i].isVisible && pieces[i].state == IN_SCROLLBAR) {
            putimage_alpha(pieces[i].x, pieces[i].y, scrollBar.pieces[i]);
        }
    }
}