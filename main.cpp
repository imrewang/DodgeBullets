#include"Process.h"


int main() // ������
{
	startup();  // ��ʼ��	
	while (1)  // �ظ�����
	{
		show();  // ����
		updateWithoutInput();  // �������޹صĸ���
		updateWithInput();  // ��������صĸ���
	}
	return 0;
}