#include"Object.h"


void Rocket::draw() // ��ʾ��������Ϣ	
{
	// �������Ͻ���ʾlife�����ͼƬ����ʾ���������
	for (int i = 0; i < life; i++)
		putimagePng(i * width * 0.9, 0, &im_rocket);

	// �������Ϸ���ʾ����˶�����
	TCHAR s[20];
	setbkmode(TRANSPARENT); // ��������͸��
	_stprintf_s(s, _T("%d��"), liveSecond);
	settextcolor(WHITE); // �趨������ɫ
	settextstyle(40, 0, _T("����"));//  �趨���ִ�С����ʽ
	outtextxy(WIDTH * 0.85, 20, s); //  �����������

	if (life > 0) // ��������û������ʾ��ͬ��ͼƬ
		putimagePng(x - width / 2, y - height / 2, &im_rocket);  // ��Ϸ����ʾ���ͼƬ
	else
		putimagePng(x - width / 2, y - height / 2, &im_blowup);  // ��Ϸ����ʾ��ըͼƬ
}

void Rocket::update(float mx, float my) // ���������������»����λ��
{
	x = mx;
	y = my;
}

void Rocket::updateWhenLifeLost() // ���������ʱִ�еĲ���
{
	PlayMusicOnce(_T("explode.mp3"));  // ����һ�α�ը��Ч
	life--; // ��������
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bullet::draw()// ��ʾ�ӵ�	
{
	putimagePng(x - radius, y - radius, &im_bullet);
}

void Bullet::update() // �����ӵ���λ�á��ٶ�
{
	x += vx;
	y += vy;
	if (x <= 0 || x >= WIDTH)
		vx = -vx;
	if (y <= 0 || y >= HEIGHT)
		vy = -vy;
}

int Bullet::isCollideRocket(Rocket rocket) // �ж��ӵ��Ƿ�ͻ����ײ
{
	float distance_x = fabsf(rocket.x - x);
	float distance_y = fabsf(rocket.y - y);
	if (distance_x < rocket.width / 2 && distance_y < rocket.height / 2)
		return 1; // ������ײ����1
	else
		return 0; // ����ײ����0	
}

///////////////////////////////////////////////////////////////////////////////


void SmartUFO::updateVelforTarge(Rocket targetRocket) // �÷ɵ����ٶ�����Ŀ����
{
	float scalar = 1 * rand() / double(RAND_MAX) + 1; // �ٶȴ�С��һ���������
	if (targetRocket.x > x) // Ŀ���ڷɵ���ߣ��ɵ�x�����ٶ�����
		vx = scalar;
	else if (targetRocket.x < x) // Ŀ���ڷɵ��ұߣ��ɵ�x�����ٶ�����
		vx = -scalar;
	if (targetRocket.y > y) // Ŀ���ڷɵ��·����ɵ�y�����ٶ�����
		vy = scalar;
	else if (targetRocket.y < y) // Ŀ���ڷɵ��Ϸ����ɵ�y�����ٶ�����
		vy = -scalar;
}