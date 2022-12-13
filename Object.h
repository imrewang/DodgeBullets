#ifndef OBJECT_H
#define OBJECT_H

#include"Parameter.h"
#include"sleep.h"
#include"PlayMusicOnce.h"

#include "EasyXPng.h"  // 用于显示带透明通道的png图片

class Rocket  // 定义火箭类
{
public:
	IMAGE im_rocket; // 火箭图像
	IMAGE im_blowup; // 爆炸图像
	float x, y; // 火箭坐标
	float width, height; // 火箭图片的宽度、高度
	int liveSecond; // 火箭存活了多长时间
	int life;  // 火箭有几条命

	void draw(); // 显示火箭相关信息	

	void update(float mx, float my); // 根据输入的坐标更新火箭的位置

	void updateWhenLifeLost(); // 当火箭减命时执行的操作
};

class Bullet  // 定义子弹类
{
public:
	IMAGE im_bullet; // 子弹图像
	float x, y; // 子弹坐标
	float vx, vy; // 子弹速度
	float radius; // 接近球体的子弹半径大小

	void draw();// 显示子弹	

	void update(); // 更新子弹的位置、速度

	int isCollideRocket(Rocket rocket); // 判断子弹是否和火箭碰撞
};

class SmartUFO : public Bullet // 智能飞碟类，由Bullet类派生出来
{
public:
	void updateVelforTarge(Rocket targetRocket); // 让飞碟的速度瞄向目标火箭
};

#endif // !OBJECT_H
