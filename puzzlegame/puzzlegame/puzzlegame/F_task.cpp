//F_task.cpp
#include <stdio.h>
#include <easyx.h>
#include <string>
#include "main.h"
#include <ctime>

using namespace std;

//变量定义
IMAGE img_menu;					//主菜单封面
IMAGE img_choosebk;
IMAGE img_levelicons[7];		//关卡图片
IMAGE img_leveliconsbk[7];			//锁住关卡图片


IMAGE img_title;				//拼图大闯关字
IMAGE img_titlemask;				//拼图大闯关字

IMAGE img_start;				//开始游戏
IMAGE img_startmask;				//开始游戏

IMAGE img_exit;					//退出游戏
IMAGE img_exitmask;					//退出游戏

IMAGE img_menuicon;				//返回主菜单按钮
IMAGE img_menuiconmask;				//返回主菜单按钮

IMAGE img_start_again;
IMAGE img_start_againmask;

IMAGE img_backmenu;				//弹窗中返回主菜单
IMAGE img_backmenumask;				//弹窗中返回主菜单

IMAGE img_next;                 //下一关
IMAGE img_nextmask;                 //下一关

IMAGE img_popupwindow;			//闯关成功后弹窗
IMAGE img_popupwindowmask;			//闯关成功后弹窗

IMAGE img_pieces[7][12];		//拼图碎片

GameState gameState = MAIN_MENU;

//加载图片资源函数
//用途：加载所有图片资源，包括主菜单、关卡图片、拼图碎片等。
//使用场景：在游戏初始化时调用，确保所有资源加载完成。
//使用方法：
//loadresources(); // 在游戏初始化时调用
void loadresources()
{
    //加载杂七杂八
    loadimage(&img_menu, "assets/主菜单封面.jpg");
    loadimage(&img_choosebk, "assets/选择关卡背景.jpg");
    loadimage(&img_title, "assets/拼图大闯关.jpg");
    loadimage(&img_titlemask, "assets/拼图大闯关2.jpg");
    loadimage(&img_start, "assets/开始游戏.jpg");
    loadimage(&img_startmask, "assets/开始游戏2.jpg");
    loadimage(&img_exit, "assets/退出游戏.jpg");
    loadimage(&img_exitmask, "assets/退出游戏2.jpg");

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



    //加载关卡和拼图图片
    char file_levelname[50];
    for (int i = 0; i < 7; i++)
    {
        sprintf_s(file_levelname, "assets/关卡%d.jpg", i + 1);
        loadimage(&img_levelicons[i], file_levelname, 128, 72);
    }

    //加载对应关卡图片背景
    char file_levelbkname[50];
    for (int i = 0; i < 7; i++)
    {
        sprintf_s(file_levelbkname, "assets/关卡%dbk.jpg", i + 1);
        loadimage(&img_leveliconsbk[i], file_levelbkname);
    }

    //加载拼图碎片
    char file_piecename[50];
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            sprintf_s(file_piecename, "assets/关卡%d碎片/关卡%d_%d.jpg", i + 1, i + 1, j + 1);
            loadimage(&img_pieces[i][j], file_piecename, 160, 90);
        }
    }
}

LevelData getLevelData(int level)
{
  
    LevelData data;
    switch (level) {
    case 1:
        data.imagepath = "assets/关卡1.jpg";
        data.pieces[0] = { 160,180};   data.pieces[1] = { 480, 90 };   data.pieces[2] = { 640, 180 };   data.pieces[3] = { 320, 270 };
        data.pieces[4] = { 160,90};   data.pieces[5] = { 640,270 };   data.pieces[6] = { 320,180 };   data.pieces[7] = { 160,270 };
        data.pieces[8] = { 320,90 };   data.pieces[9] = { 480,270 };   data.pieces[10] = { 640,90 };  data.pieces[11] = { 480,180 };
        break;
    case 2:
        data.imagepath = "assets/关卡2.jpg";
        data.pieces[0] = { 320, 180 };   data.pieces[1] = { 160, 270 };   data.pieces[2] = { 320, 90 };   data.pieces[3] = { 480,180 };
        data.pieces[4] = { 320,270 };   data.pieces[5] = { 640,90 };   data.pieces[6] = { 640,270 };   data.pieces[7] = { 160,90 };
        data.pieces[8] = { 640,180 };   data.pieces[9] = { 160,180 };   data.pieces[10] = { 480,270 };  data.pieces[11] = { 480,90 };
        break;

    case 3:
        data.imagepath = "assets/关卡3.jpg";
        data.pieces[0] = { 640,90 };   data.pieces[1] = { 480,180 };   data.pieces[2] = { 320,270 };   data.pieces[3] = { 320,90 };
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
