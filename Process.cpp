#include"Process.h"


IMAGE im_bk, im_bullet, im_rocket, im_blowup, im_UFO;  // 定义图像对象	
Bullet bullet[MaxBulletNum]; // 定义子弹对象数组
Rocket rocket;  // 定义火箭对象
SmartUFO ufo;  // 定义飞碟对象
int bulletNum = 0; // 已有子弹的个数

void startup()  //  初始化函数
{
	mciSendString(_T("open game_music.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // 循环播放

	srand(time(0)); // 初始化随机种子
	loadimage(&im_bk, _T("background.png")); // 导入背景图片
	loadimage(&im_bullet, _T("bullet.png")); // 导入子弹图片
	loadimage(&im_rocket, _T("rocket.png")); // 导入火箭图片
	loadimage(&im_blowup, _T("blowup.png")); // 导入爆炸图片
	loadimage(&im_UFO, _T("ufo.png")); // 导入飞碟图片

	// 对飞碟的一些成员变量初始化
	ufo.x = WIDTH / 2;  // 设置飞碟位置
	ufo.y = 10;
	ufo.im_bullet = im_UFO; // 设置飞碟图片
	ufo.radius = im_UFO.getwidth() / 2; // 设置飞碟半径大小
	ufo.updateVelforTarge(rocket); // 更新飞碟的速度

	// 对rocket一些成员变量初始化
	rocket.im_rocket = im_rocket;  // 设置火箭图片
	rocket.im_blowup = im_blowup;  // 设置火箭爆炸图片
	rocket.width = im_rocket.getwidth(); // 设置火箭宽度
	rocket.height = im_rocket.getheight(); // 设置火箭高度
	rocket.life = 5; // 火箭初始5条命 

	initgraph(WIDTH, HEIGHT); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	
	ufo.draw();  // 显示飞碟
	for (int i = 0; i < bulletNum; i++)
		bullet[i].draw();  // 显示已有的子弹
	rocket.draw();  // 显示火箭及相关信息
	FlushBatchDraw(); // 批量绘制
	sleep(10); // 暂停
}

void updateWithoutInput() // 和输入无关的更新
{
	if (rocket.life <= 0) // 火箭没有命了，不处理
		return; // 直接返回

	static int lastSecond = 0; // 记录前一次程序运行了多少秒
	static int nowSecond = 0; // 记录当前程序运行了多少秒
	static clock_t start = clock(); // 记录第一次运行时刻
	clock_t now = clock(); // 获得当前时刻
	// 计算程序目前一共运行了多少秒
	nowSecond = (int(now - start) / CLOCKS_PER_SEC);
	rocket.liveSecond = nowSecond; // 火箭生成了多少秒赋值

	if (nowSecond == lastSecond + 1) // 时间过了1秒钟，更新下飞碟的速度
		ufo.updateVelforTarge(rocket); // ufo速度方向瞄准火箭

	if (nowSecond == lastSecond + 2) // 时间过了2秒钟，新增一颗子弹
	{
		lastSecond = nowSecond; // 更新下lastSecond变量
		// 如果没有超出最大子弹数目的限制，增加一颗新的子弹
		if (bulletNum < MaxBulletNum)
		{
			bullet[bulletNum].x = WIDTH / 2; // 子弹初始位置
			bullet[bulletNum].y = 10;
			float angle = (rand() / double(RAND_MAX) - 0.5) * 0.9 * PI;
			float scalar = 2 * rand() / double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar * sin(angle); // 子弹随机速度
			bullet[bulletNum].vy = scalar * cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;  // 设置子弹图像
			bullet[bulletNum].radius = im_bullet.getwidth() / 2; // 子弹半径为图片宽度一半
		}
		bulletNum++; // 子弹数目加一
	}

	for (int i = 0; i < bulletNum; i++) // 对所有已有的子弹
	{
		bullet[i].update(); // 更新子弹的位置、速度		
		if (bullet[i].isCollideRocket(rocket)) // 判断子弹是否和火箭碰撞
		{
			rocket.updateWhenLifeLost(); // 火箭减命相关操作
			bullet[i].x = 5; // 当前子弹移开，防止重复碰撞
			bullet[i].y = 5;
			break; // 火箭已炸，不用再和其他子弹比较了
		}
	}

	ufo.update(); // 更新飞碟的位置、速度		
	if (ufo.isCollideRocket(rocket)) // 判断飞碟是否和火箭碰撞
	{
		rocket.updateWhenLifeLost(); // 当火箭减命时执行的操作
		ufo.x = 5; // 当前飞碟移开，防止重复碰撞
		ufo.y = 5;
	}
}

void updateWithInput()  // 和输入相关的更新
{
	if (rocket.life <= 0) // 火箭没有命了，不处理
		return; // 直接返回

	MOUSEMSG m;		// 定义鼠标消息
	while (MouseHit())  // 检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)  // 到鼠标移动时			
			rocket.update(m.x, m.y); // 火箭的位置等于鼠标所在的位置
	}
}