//���� �ڵ鷯�� ����

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//������ ����� �� __try ��Ͽ��� ����.
	int a, b;

	__try
	{
		_tprintf(_T("input divide string [a/b]:"));
		_tscanf(_T("%d/%d", &a, &b));
		//���� b�� 0�̶��, ���� ��ȯ�ϱ� ���� __finally ����� ����ȴ�.
		if (b == 0)
			return -1;
	}
	//__try��Ͼȿ� �ڵ尡 �� ���̶� ����Ǹ� �ݵ�� �����.
	__finally
	{
		_tprintf(_T("__finally block!\n"));
	}
	_tprintf(_T("result:%d\n"), a / b);
	return 0;
}