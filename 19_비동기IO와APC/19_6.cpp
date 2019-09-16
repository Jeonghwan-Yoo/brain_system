//APC Queue에 직접 정보 전달
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

VOID CALLBACK APCProc(ULONG_PTR);

int _tmain(int argc, TCHAR* argv[])
{
	//main 쓰레드 핸들을 얻고 있다.
	HANDLE hThread = GetCurrentThread();
	//총 5번에 걸쳐 비동기로 호출될 함수를 등록하고 있다.
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)1);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)2);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)3);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)4);
	QueueUserAPC(APCProc, hThread, (ULONG_PTR)5);
	//위에 지정한 함수가 바로 호출되지 않음을 확인하기 위해.
	Sleep(5000);
	//여기서 알림 가능 상태가 된다.
	//따라서 이 시점에서 APC Queue에 등록된 함수들이 호출된다.
	SleepEx(INFINITE, TRUE);
	return 0;
}

VOID CALLBACK APCProc(ULONG_PTR dwParam)
{
	_tprintf(_T("Asynchronous procedure call num %u\n"), (DWORD)dwParam);
}