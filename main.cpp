#include"Process.h"


int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 重复运行
	{
		show();  // 绘制
		updateWithoutInput();  // 和输入无关的更新
		updateWithInput();  // 和输入相关的更新
	}
	return 0;
}