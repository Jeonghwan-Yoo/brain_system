//APC Queue�� ���� ���� ����
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

VOID CALLBACK APCProc(ULONG_PTR);

int _tmain(int argc, TCHAR* argv[])
{
	//main ������ �ڵ��� ��� �ִ�.
	HANDLE hThread = GetCurrentThread();
	//�� 5���� ���� �񵿱�� ȣ��� �Լ��� ����ϰ� �ִ�.
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)1);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)2);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)3);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)4);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)5);
	//���� ������ �Լ��� �ٷ� ȣ����� ������ Ȯ���ϱ� ����.
	Sleep(5000);
	//���⼭ �˸� ���� ���°� �ȴ�.
	//���� �� �������� APC Queue�� ��ϵ� �Լ����� ȣ��ȴ�.
	SleepEx(INFINITE, TRUE);
	return 0;
}

VOID CALLBACK APCProc(ULONG_PTR dwParam)
{
	_tprintf(_T("Asynchronous procedure call num %u\n"), (DWORD)dwParam);
}