#ifndef PROCESS_H
#define PROCESS_H

#include <time.h>
// ���� Windows Multimedia API
#pragma comment(lib,"Winmm.lib")

#include"Object.h"

//IMAGE im_bk, im_bullet, im_rocket, im_blowup, im_UFO;  // ����ͼ�����	
//Bullet bullet[MaxBulletNum]; // �����ӵ���������
//Rocket rocket;  // ����������
//SmartUFO ufo;  // ����ɵ�����
//int bulletNum = 0; // �����ӵ��ĸ���

void startup();  //  ��ʼ������

void show();  // ���ƺ���

void updateWithoutInput(); // �������޹صĸ���

void updateWithInput();  // ��������صĸ���


#endif // !PROCESS_H
