//B_task.cpp
# include<stdio.h>
#include <graphics.h>
#include <windows.h>
#include "main.h"
/*------------ 全局变量定义 ------------*/
extern IMAGE  img_menu;          // 关卡选择背景图（由成员F加载）
extern IMAGE img_levelicons1[7];         // 彩色关卡图标（由成员F加载）
extern IMAGE img_lockicons1[7];          // 黑白关卡图标（由成员F加载）
extern IMAGE img_menuicon;
extern MOUSEMSG mouseMsg;                  // 鼠标消息

/*------------ 函数声明 ------------*/
void drawLevelSelect();
void handleLevelSelectClick(int x, int y);
void returnToMainMenu();
void startGame(int level);

/*------------ 主入口 ------------*/
void select_level() {
    cleardevice();
    drawLevelSelect(); // 绘制关卡选择界面
    while (gameState == LEVEL_SELECT) {
        if (MouseHit()) { // 检测鼠标点击
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONDOWN) {
                handleLevelSelectClick(mouseMsg.x, mouseMsg.y); // 处理点击事件
            }
        }
        Sleep(10); // 降低CPU占用
    }
    cleardevice();
}

/*------------ 绘制关卡选择界面 ------------*/
void drawLevelSelect() {
    printf("正在绘制关卡选择界面");
    cleardevice();
    // 绘制背景（保持原始尺寸）
    putimage(0, 0, &img_choosebk);
    putimage(10, 10, &img_menuiconmask, NOTSRCERASE);
    putimage(10, 10, &img_menuicon, SRCINVERT);


    // 布局参数
    const int iconWidth = 128;    // 新显示宽度
    const int iconHeight = 72;    // 新显示高度
    const int hSpacing = 30;      // 水平间距适当缩小
    const int vSpacing = 40;      // 垂直间距适应新高度
    int baseY = 180;              // 适当上移起始位置

    // 第二行4图标
    int totalWidth = 4 * iconWidth + 3 * hSpacing;
    int startX = (1024 - totalWidth) / 2; // (1024-674)/2=175
    for (int i = 0; i < 4; i++) {
        int x = startX + i * (iconWidth + hSpacing);
        putimage(x, baseY, iconWidth, iconHeight, &img_levelicons[i], 0, 0);
    }

    // 第三行3图标
    baseY += iconHeight + vSpacing; // 120+72+40=232
    totalWidth = 3 * iconWidth + 2 * hSpacing;
    startX = (1024 - totalWidth) / 2; // (1024-444)/2=290
    for (int i = 4; i < 7; i++) {
        int x = startX + (i - 4) * (iconWidth + hSpacing);
        putimage(x, baseY, iconWidth, iconHeight, &img_levelicons[i], 0, 0);
    }

    FlushBatchDraw();
}

/*------------ 处理点击事件 ------------*/
void handleLevelSelectClick(int x, int y) {
    // 检测主菜单按钮（新尺寸）
    if (x >= 10 && x <= 10 + 320 && y >= 10 && y <= 10 + 140) {
        printf("点击了返回主菜单");
        returnToMainMenu();
        return;
    }

    // 布局参数（必须与绘制参数一致）
    const int iconWidth = 128;
    const int iconHeight = 72;
    const int hSpacing = 30;
    int startX, startY = 180; // 与baseY一致

    // 第二行检测
    int totalWidth = 4 * iconWidth + 3 * hSpacing;
    startX = (1024 - totalWidth) / 2;
    for (int i = 0; i < 4; i++) {
        int iconX = startX + i * (iconWidth + hSpacing);
        if (x >= iconX && x <= iconX + iconWidth &&
            y >= startY && y <= startY + iconHeight) {
            currentLevel = i + 1;
            printf("点击了关卡%d\n", currentLevel);
            startGame(currentLevel);
            return;
        }
    }

    // 第三行检测
    startY += iconHeight + 40; // 同步vSpacing
    totalWidth = 3 * iconWidth + 2 * hSpacing;
    startX = (1024 - totalWidth) / 2;
    for (int i = 0; i < 3; i++) {
        int iconX = startX + i * (iconWidth + hSpacing);
        if (x >= iconX && x <= iconX + iconWidth &&
            y >= startY && y <= startY + iconHeight) {
            currentLevel = i + 5;
            printf("点击了关卡%d\n", currentLevel);
            startGame(i + 5); // 索引偏移
            return;
        }
    }
}

void returnToMainMenu() {
    gameState = MAIN_MENU;
}

void startGame(int level) {
    gameState = IN_GAME;
}

