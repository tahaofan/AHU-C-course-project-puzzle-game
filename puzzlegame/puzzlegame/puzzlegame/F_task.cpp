/**
 * @file    F_task.cpp
 * @brief   全局资源与关卡数据实现
 *        定义所有 IMAGE 全局变量、游戏状态变量，
 *        实现图片资源加载函数和各关卡碎片位置数据。
 * @author  EasyX Puzzle Team
 * @date    2025-03
 */
#include <stdio.h>
#include <easyx.h>
#include <string>
#include "main.h"
#include <ctime>

using namespace std;

/*------------ 图片资源定义 ------------*/
IMAGE img_menu;
IMAGE img_choosebk;
IMAGE img_levelicons[7];
IMAGE img_leveliconsbk[7];

IMAGE img_title;
IMAGE img_titlemask;

IMAGE img_start;
IMAGE img_startmask;

IMAGE img_exit;
IMAGE img_exitmask;

IMAGE img_menuicon;
IMAGE img_menuiconmask;

IMAGE img_start_again;
IMAGE img_start_againmask;

IMAGE img_backmenu;
IMAGE img_backmenumask;

IMAGE img_next;
IMAGE img_nextmask;

IMAGE img_popupwindow;
IMAGE img_popupwindowmask;

IMAGE img_pieces[7][12];

GameState gameState = MAIN_MENU;

/**
 * @brief 加载所有图片资源
 *        包括背景、按钮、关卡图标、拼图碎片等，
 *        在程序启动时调用一次。
 */
void loadresources()
{
    // 主菜单
    loadimage(&img_menu, "assets/主菜单封面.jpg");
    loadimage(&img_choosebk, "assets/选择关卡背景.jpg");
    loadimage(&img_title, "assets/拼图大闯关.jpg");
    loadimage(&img_titlemask, "assets/拼图大闯关2.jpg");
    loadimage(&img_start, "assets/开始游戏.jpg");
    loadimage(&img_startmask, "assets/开始游戏2.jpg");
    loadimage(&img_exit, "assets/退出游戏.jpg");
    loadimage(&img_exitmask, "assets/退出游戏2.jpg");

    // 弹窗与按钮
    loadimage(&img_popupwindow, "assets/弹窗.jpg", 500, 320);
    loadimage(&img_popupwindowmask, "assets/弹窗2.jpg", 500, 320);
    loadimage(&img_backmenu, "assets/返回菜单.jpg", 160, 70);
    loadimage(&img_backmenumask, "assets/返回菜单2.jpg", 160, 70);
    loadimage(&img_next, "assets/下一关.jpg", 160, 70);
    loadimage(&img_nextmask, "assets/下一关2.jpg", 160, 70);
    loadimage(&img_menuicon, "assets/主菜单.jpg", 100, 100);
    loadimage(&img_menuiconmask, "assets/主菜单2.jpg", 100, 100);
    loadimage(&img_start_again, "assets/重新开始.jpg", 100, 100);
    loadimage(&img_start_againmask, "assets/重新开始2.jpg", 100, 100);

    // 关卡图标
    char filename[50];
    for (int i = 0; i < 7; i++) {
        sprintf_s(filename, "assets/关卡%d.jpg", i + 1);
        loadimage(&img_levelicons[i], filename, 128, 72);
    }

    // 关卡背景
    for (int i = 0; i < 7; i++) {
        sprintf_s(filename, "assets/关卡%dbk.jpg", i + 1);
        loadimage(&img_leveliconsbk[i], filename);
    }

    // 拼图碎片（7关 × 12块）
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            sprintf_s(filename, "assets/关卡%d碎片/关卡%d_%d.jpg", i + 1, i + 1, j + 1);
            loadimage(&img_pieces[i][j], filename, 160, 90);
        }
    }
}

/**
 * @brief 获取指定关卡的碎片目标位置数据
 * @param level 关卡编号 (1~7)
 * @return LevelData 包含图片路径和 12 块碎片的目标坐标
 */
LevelData getLevelData(int level)
{
    LevelData data;
    switch (level) {
    case 1:
        data.imagepath = "assets/关卡1.jpg";
        data.pieces[0] = { 160,180 };   data.pieces[1] = { 480, 90 };   data.pieces[2] = { 640, 180 };   data.pieces[3] = { 320, 270 };
        data.pieces[4] = { 160,90 };    data.pieces[5] = { 640,270 };   data.pieces[6] = { 320,180 };   data.pieces[7] = { 160,270 };
        data.pieces[8] = { 320,90 };    data.pieces[9] = { 480,270 };   data.pieces[10] = { 640,90 };  data.pieces[11] = { 480,180 };
        break;
    case 2:
        data.imagepath = "assets/关卡2.jpg";
        data.pieces[0] = { 320, 180 };   data.pieces[1] = { 160, 270 };   data.pieces[2] = { 320, 90 };   data.pieces[3] = { 480,180 };
        data.pieces[4] = { 320,270 };   data.pieces[5] = { 640,90 };    data.pieces[6] = { 640,270 };   data.pieces[7] = { 160,90 };
        data.pieces[8] = { 640,180 };   data.pieces[9] = { 160,180 };   data.pieces[10] = { 480,270 };  data.pieces[11] = { 480,90 };
        break;
    case 3:
        data.imagepath = "assets/关卡3.jpg";
        data.pieces[0] = { 640,90 };    data.pieces[1] = { 480,180 };   data.pieces[2] = { 320,270 };   data.pieces[3] = { 320,90 };
        data.pieces[4] = { 640,180 };   data.pieces[5] = { 480,270 };   data.pieces[6] = { 480,90 };   data.pieces[7] = { 160,270 };
        data.pieces[8] = { 160,180 };   data.pieces[9] = { 640,270 };   data.pieces[10] = { 160,90 };  data.pieces[11] = { 320,180 };
        break;
    case 4:
        data.imagepath = "assets/关卡4.jpg";
        data.pieces[0] = { 480,180 };   data.pieces[1] = { 160,180 };   data.pieces[2] = { 160, 90 };   data.pieces[3] = { 480,270 };
        data.pieces[4] = { 480, 90 };   data.pieces[5] = { 160,270 };   data.pieces[6] = { 640,270 };   data.pieces[7] = { 320,180 };
        data.pieces[8] = { 320,270 };   data.pieces[9] = { 320, 90 };   data.pieces[10] = { 640,180 };  data.pieces[11] = { 640, 90 };
        break;
    case 5:
        data.imagepath = "assets/关卡5.jpg";
        data.pieces[0] = { 480, 90 };   data.pieces[1] = { 160,270 };   data.pieces[2] = { 480,180 };   data.pieces[3] = { 160,180 };
        data.pieces[4] = { 480,270 };   data.pieces[5] = { 320, 90 };   data.pieces[6] = { 640,180 };   data.pieces[7] = { 640,270 };
        data.pieces[8] = { 640, 90 };   data.pieces[9] = { 320,180 };   data.pieces[10] = { 320,270 };  data.pieces[11] = { 160, 90 };
        break;
    case 6:
        data.imagepath = "assets/关卡6.jpg";
        data.pieces[0] = { 320, 90 };   data.pieces[1] = { 320,270 };   data.pieces[2] = { 160,180 };   data.pieces[3] = { 640,180 };
        data.pieces[4] = { 640, 90 };   data.pieces[5] = { 640,270 };   data.pieces[6] = { 160, 90 };   data.pieces[7] = { 480,180 };
        data.pieces[8] = { 480,270 };   data.pieces[9] = { 480, 90 };   data.pieces[10] = { 160,270 };  data.pieces[11] = { 320,180 };
        break;
    case 7:
        data.imagepath = "assets/关卡7.jpg";
        data.pieces[0] = { 160,270 };   data.pieces[1] = { 160, 90 };   data.pieces[2] = { 320,180 };   data.pieces[3] = { 320,270 };
        data.pieces[4] = { 320, 90 };   data.pieces[5] = { 480,180 };   data.pieces[6] = { 640,270 };   data.pieces[7] = { 640, 90 };
        data.pieces[8] = { 480,270 };   data.pieces[9] = { 160,180 };   data.pieces[10] = { 480, 90 };  data.pieces[11] = { 640,180 };
        break;
    }
    return data;
}
