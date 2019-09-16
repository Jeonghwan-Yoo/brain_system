#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//Ÿ�̸� ������Ʈ ����
	//�� ��° �������ڰ� FALSE�� �ڵ� ���¸�� Ÿ�̸� ������Ʈ�� �����ȴ�.
	//FALSE�� �Ǿ�� �ڵ����� Ÿ�̸Ӱ� Non-Signaled ���°� �Ǿ� ��ӵǴ� �˶��� �����ϰ� �ȴ�.
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	//�˶��� 10�� �Ŀ�, �׸��� 5�� �������� �����Ѵ�.
	//�� ��° �������ڴ� 1/1000�� ������ ���ǹǷ� 5�� �������� �˶�.
	SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

	//Ÿ�̸��� �˶��� ���
	while (1)
	{
		//���� �ݺ��� ���鼭 Ÿ�̸� ������Ʈ�� Signaled ���°� �Ǳ⸦ ��ٸ��� �ִ�.
		//ù �˶� ���Ŀ� 5�� �������� �˶��� �︮�Ƿ� 5�ʿ� �� ���� ���ŷ�� �Լ��� �������� �˶��� �︰��.
		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was signaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}
	return 0;
}