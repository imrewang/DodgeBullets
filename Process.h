#ifndef PROCESS_H
#define PROCESS_H

#include <time.h>
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#include"Object.h"

//IMAGE im_bk, im_bullet, im_rocket, im_blowup, im_UFO;  // 定义图像对象	
//Bullet bullet[MaxBulletNum]; // 定义子弹对象数组
//Rocket rocket;  // 定义火箭对象
//SmartUFO ufo;  // 定义飞碟对象
//int bulletNum = 0; // 已有子弹的个数

void startup();  //  初始化函数

void show();  // 绘制函数

void updateWithoutInput(); // 和输入无关的更新

void updateWithInput();  // 和输入相关的更新


#endif // !PROCESS_H
