#ifndef OBJECT_H
#define OBJECT_H

#include"Parameter.h"
#include"sleep.h"
#include"PlayMusicOnce.h"

#include "EasyXPng.h"  // ������ʾ��͸��ͨ����pngͼƬ

class Rocket  // ��������
{
public:
	IMAGE im_rocket; // ���ͼ��
	IMAGE im_blowup; // ��ըͼ��
	float x, y; // �������
	float width, height; // ���ͼƬ�Ŀ�ȡ��߶�
	int liveSecond; // �������˶೤ʱ��
	int life;  // ����м�����

	void draw(); // ��ʾ��������Ϣ	

	void update(float mx, float my); // ���������������»����λ��

	void updateWhenLifeLost(); // ���������ʱִ�еĲ���
};

class Bullet  // �����ӵ���
{
public:
	IMAGE im_bullet; // �ӵ�ͼ��
	float x, y; // �ӵ�����
	float vx, vy; // �ӵ��ٶ�
	float radius; // �ӽ�������ӵ��뾶��С

	void draw();// ��ʾ�ӵ�	

	void update(); // �����ӵ���λ�á��ٶ�

	int isCollideRocket(Rocket rocket); // �ж��ӵ��Ƿ�ͻ����ײ
};

class SmartUFO : public Bullet // ���ܷɵ��࣬��Bullet����������
{
public:
	void updateVelforTarge(Rocket targetRocket); // �÷ɵ����ٶ�����Ŀ����
};

#endif // !OBJECT_H
