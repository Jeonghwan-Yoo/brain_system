//swap ���̺귯���� Ȱ��
#include <stdio.h>
#include <tchar.h>
//swap.h������ include���� ���� ���Ե� �� �ִ� ��ο� �����ؾ� �ȴ�.(������Ʈ ������ ��ġ).
//��� SwapStaticLib.lib�� ���̳ʸ��� �����ϴ� swap �Լ��� ȣ���� ����������, ���輺�� ��ũ������ ���� ����.
//�����Ϸ��� swap�Լ� ȣ�� ������ �������� ���ϹǷ� include ����� �Ѵ�.
#include "swap.h"

//#pragma comment(lib, "SwapStaticLib.lib")

int _tmain(int argc, TCHAR* argv[])
{
	int a = 10;
	int b = 20;
	_tprintf(_T("Before:%d, %d\n"), a, b);

	swap(&a, &b);
	_tprintf(_T("After:%d, %d\n"), a, b);
	
	return 0;
}