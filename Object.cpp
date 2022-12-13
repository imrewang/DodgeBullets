#include"Object.h"


void Rocket::draw() // 显示火箭相关信息	
{
	// 窗口左上角显示life个火箭图片，表示火箭生命数
	for (int i = 0; i < life; i++)
		putimagePng(i * width * 0.9, 0, &im_rocket);

	// 窗口正上方显示坚持了多少秒
	TCHAR s[20];
	setbkmode(TRANSPARENT); // 文字字体透明
	_stprintf_s(s, _T("%d秒"), liveSecond);
	settextcolor(WHITE); // 设定文字颜色
	settextstyle(40, 0, _T("黑体"));//  设定文字大小、样式
	outtextxy(WIDTH * 0.85, 20, s); //  输出文字内容

	if (life > 0) // 根据有命没命，显示不同的图片
		putimagePng(x - width / 2, y - height / 2, &im_rocket);  // 游戏中显示火箭图片
	else
		putimagePng(x - width / 2, y - height / 2, &im_blowup);  // 游戏中显示爆炸图片
}

void Rocket::update(float mx, float my) // 根据输入的坐标更新火箭的位置
{
	x = mx;
	y = my;
}

void Rocket::updateWhenLifeLost() // 当火箭减命时执行的操作
{
	PlayMusicOnce(_T("explode.mp3"));  // 播放一次爆炸音效
	life--; // 生命减少
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bullet::draw()// 显示子弹	
{
	putimagePng(x - radius, y - radius, &im_bullet);
}

void Bullet::update() // 更新子弹的位置、速度
{
	x += vx;
	y += vy;
	if (x <= 0 || x >= WIDTH)
		vx = -vx;
	if (y <= 0 || y >= HEIGHT)
		vy = -vy;
}

int Bullet::isCollideRocket(Rocket rocket) // 判断子弹是否和火箭碰撞
{
	float distance_x = fabsf(rocket.x - x);
	float distance_y = fabsf(rocket.y - y);
	if (distance_x < rocket.width / 2 && distance_y < rocket.height / 2)
		return 1; // 发生碰撞返回1
	else
		return 0; // 不碰撞返回0	
}

///////////////////////////////////////////////////////////////////////////////


void SmartUFO::updateVelforTarge(Rocket targetRocket) // 让飞碟的速度瞄向目标火箭
{
	float scalar = 1 * rand() / double(RAND_MAX) + 1; // 速度大小有一定的随机性
	if (targetRocket.x > x) // 目标在飞碟左边，飞碟x方向速度向右
		vx = scalar;
	else if (targetRocket.x < x) // 目标在飞碟右边，飞碟x方向速度向左
		vx = -scalar;
	if (targetRocket.y > y) // 目标在飞碟下方，飞碟y方向速度向下
		vy = scalar;
	else if (targetRocket.y < y) // 目标在飞碟上方，飞碟y方向速度向上
		vy = -scalar;
}