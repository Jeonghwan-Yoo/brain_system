//���� �ڵ鷯�� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR str[2];

	__try
	{
		//�޸� ���簡 �Ͼ�µ�, ���ڿ��� ������ ������ �ξ��� �����ϴ�.
		//���� �Ҵ���� ���� �޸� �������� ���縦 �õ��ϴ� �������� �޸� ���� ������ �߻��Ѵ�.
		//���α׷��� ����ȴ�.
		//�׷��� __try ��� �ȿ��� �߻��� �����̱� ������ __finally ����� ����ȴ�.
		//__finally ����� __try��� ������ ������ �߻��ص� ����ȴ�.
		_tcscpy(str, _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ~"));
		_tprintf(_T("%s\n"), str);
	}
	__finally
	{
		_tprintf(_T("__finally block!\n"));
	}
	return 0;
}