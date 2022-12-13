#include"Process.h"


IMAGE im_bk, im_bullet, im_rocket, im_blowup, im_UFO;  // ����ͼ�����	
Bullet bullet[MaxBulletNum]; // �����ӵ���������
Rocket rocket;  // ����������
SmartUFO ufo;  // ����ɵ�����
int bulletNum = 0; // �����ӵ��ĸ���

void startup()  //  ��ʼ������
{
	mciSendString(_T("open game_music.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // ѭ������

	srand(time(0)); // ��ʼ���������
	loadimage(&im_bk, _T("background.png")); // ���뱳��ͼƬ
	loadimage(&im_bullet, _T("bullet.png")); // �����ӵ�ͼƬ
	loadimage(&im_rocket, _T("rocket.png")); // ������ͼƬ
	loadimage(&im_blowup, _T("blowup.png")); // ���뱬ըͼƬ
	loadimage(&im_UFO, _T("ufo.png")); // ����ɵ�ͼƬ

	// �Էɵ���һЩ��Ա������ʼ��
	ufo.x = WIDTH / 2;  // ���÷ɵ�λ��
	ufo.y = 10;
	ufo.im_bullet = im_UFO; // ���÷ɵ�ͼƬ
	ufo.radius = im_UFO.getwidth() / 2; // ���÷ɵ��뾶��С
	ufo.updateVelforTarge(rocket); // ���·ɵ����ٶ�

	// ��rocketһЩ��Ա������ʼ��
	rocket.im_rocket = im_rocket;  // ���û��ͼƬ
	rocket.im_blowup = im_blowup;  // ���û����ըͼƬ
	rocket.width = im_rocket.getwidth(); // ���û�����
	rocket.height = im_rocket.getheight(); // ���û���߶�
	rocket.life = 5; // �����ʼ5���� 

	initgraph(WIDTH, HEIGHT); // �¿�һ������
	BeginBatchDraw(); // ��ʼ��������
}

void show()  // ���ƺ���
{
	putimage(0, 0, &im_bk);	// ��ʾ����	
	ufo.draw();  // ��ʾ�ɵ�
	for (int i = 0; i < bulletNum; i++)
		bullet[i].draw();  // ��ʾ���е��ӵ�
	rocket.draw();  // ��ʾ����������Ϣ
	FlushBatchDraw(); // ��������
	sleep(10); // ��ͣ
}

void updateWithoutInput() // �������޹صĸ���
{
	if (rocket.life <= 0) // ���û�����ˣ�������
		return; // ֱ�ӷ���

	static int lastSecond = 0; // ��¼ǰһ�γ��������˶�����
	static int nowSecond = 0; // ��¼��ǰ���������˶�����
	static clock_t start = clock(); // ��¼��һ������ʱ��
	clock_t now = clock(); // ��õ�ǰʱ��
	// �������Ŀǰһ�������˶�����
	nowSecond = (int(now - start) / CLOCKS_PER_SEC);
	rocket.liveSecond = nowSecond; // ��������˶����븳ֵ

	if (nowSecond == lastSecond + 1) // ʱ�����1���ӣ������·ɵ����ٶ�
		ufo.updateVelforTarge(rocket); // ufo�ٶȷ�����׼���

	if (nowSecond == lastSecond + 2) // ʱ�����2���ӣ�����һ���ӵ�
	{
		lastSecond = nowSecond; // ������lastSecond����
		// ���û�г�������ӵ���Ŀ�����ƣ�����һ���µ��ӵ�
		if (bulletNum < MaxBulletNum)
		{
			bullet[bulletNum].x = WIDTH / 2; // �ӵ���ʼλ��
			bullet[bulletNum].y = 10;
			float angle = (rand() / double(RAND_MAX) - 0.5) * 0.9 * PI;
			float scalar = 2 * rand() / double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar * sin(angle); // �ӵ�����ٶ�
			bullet[bulletNum].vy = scalar * cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;  // �����ӵ�ͼ��
			bullet[bulletNum].radius = im_bullet.getwidth() / 2; // �ӵ��뾶ΪͼƬ���һ��
		}
		bulletNum++; // �ӵ���Ŀ��һ
	}

	for (int i = 0; i < bulletNum; i++) // ���������е��ӵ�
	{
		bullet[i].update(); // �����ӵ���λ�á��ٶ�		
		if (bullet[i].isCollideRocket(rocket)) // �ж��ӵ��Ƿ�ͻ����ײ
		{
			rocket.updateWhenLifeLost(); // ���������ز���
			bullet[i].x = 5; // ��ǰ�ӵ��ƿ�����ֹ�ظ���ײ
			bullet[i].y = 5;
			break; // �����ը�������ٺ������ӵ��Ƚ���
		}
	}

	ufo.update(); // ���·ɵ���λ�á��ٶ�		
	if (ufo.isCollideRocket(rocket)) // �жϷɵ��Ƿ�ͻ����ײ
	{
		rocket.updateWhenLifeLost(); // ���������ʱִ�еĲ���
		ufo.x = 5; // ��ǰ�ɵ��ƿ�����ֹ�ظ���ײ
		ufo.y = 5;
	}
}

void updateWithInput()  // ��������صĸ���
{
	if (rocket.life <= 0) // ���û�����ˣ�������
		return; // ֱ�ӷ���

	MOUSEMSG m;		// ���������Ϣ
	while (MouseHit())  // ��⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)  // ������ƶ�ʱ			
			rocket.update(m.x, m.y); // �����λ�õ���������ڵ�λ��
	}
}