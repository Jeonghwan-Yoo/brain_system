//�ý��� ���͸��� Windows ���͸��� Ȯ��
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//MAX_PATH�� ������� windef.h�� ����Ǿ� �ִ�.
	//�̴� ����Ʈ �ִ��� ���� 248�� ����Ͽ� ����� ��ũ�� ����̴�.
	//���� ���� �̸�(���� ��θ� �����ϴ�)�� �����ϱ� ���� ���ڿ� ���۸� ������ �� Ȱ���� �� �ִ�.
	//#define MAX_PATH 260
	TCHAR sysPathBuf[MAX_PATH];
	TCHAR winPathBuf[MAX_PATH];

	GetSystemDirectory(sysPathBuf, MAX_PATH);
	GetWindowsDirectory(winPathBuf, MAX_PATH);

	_tprintf(_T("System dir:%s\n"), sysPathBuf);
	_tprintf(_T("Windows dir:%s\n"), winPathBuf);
	return 0;
}