//"�Ʒ��� ���α׷��� Windows NT�̻󿡼� �����ϰڽ��ϴ�. �׷��� SetWaitableTime �Լ�ȣ���� ������ּ���.
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	//LARGE_INTEGER��� �ڷ����� Windows���� union���� ����Ǿ� �ִ� �ڷ����̴�.
	//�� �ڷ����� 64��Ʈ ������ ǥ���ϱ� ���� ������ �ڷ���.
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//Ÿ�̸� ������Ʈ ����
	//�̶� ���� �ڵ��� ���ڷ� �����ϸ鼭 �ڿ��� �˶� �ð��� ����.
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}
	_tprintf(_T("Waiting for 10 seconds...\n"));

	//Ÿ�̸��� �˶��� 10�ʷ� ����
	//�� ��° ���ڴ� 0���� ���� ������ ���ð����� �˶��� ������ ��.
	//100000000������ ��(10�� �Ŀ�) �˶��� �︱ ���̴�. �� Ÿ�̸� ������Ʈ�� Signaled ���°� �� ��.
	//�� ��° �������ڴ� 0���� Ÿ�̸��� �˶��� �ֱ������� �︮�� �ʰ� �� ���� �︮���� �����Ѵٴ� �ǹ�.
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);

	//Ÿ�̸��� �˶��� ���
	//Ÿ�̸� ������Ʈ�� Signaled ���°� �Ǳ⸸�� ��ٸ���.
	//10�� �Ŀ��� Signaled ���°� �Ǿ� WaitForSingleObject �Լ��� ����������,
	//MessageBeep�Լ��� ȣ���ϸ� ���� �Ҹ��� ���� �ȴ�.
	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(_T("Timer was signaled.\n"));
	MessageBeep(MB_ICONEXCLAMATION);

	return 0;
}