//완료루틴 타이머에 대한 이해
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

VOID CALLBACK TimerAPCProc(LPVOID, DWORD, DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));
	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));
	//타이머의 완료루틴을 설정하면서, 완료루틴 호출 시 인자로 문자열을 전달하도록 지정하였다.
	//타이머가 신호를 받을 때마다 완료루틴 호출에 의해 변경 이전과 동일하게 작동.
	SetWaitableTimer(hTimer, &liDueTime, 5000, TimerAPCProc, (LPVOID)_T("Timer was signaled.\n"), FALSE);

	while (1)
		//SleepEx 함수 호출은 프로그램 종료를 막는 역할 이외에도 추가적인 기능을 제공한다.
		//쓰레드를 알림이 가능한 상태로 만들어서 완료루틴 실행을 실질적으로 돕는다.
		SleepEx(INFINITE, TRUE);

	return 0;
}

VOID CALLBACK TimerAPCProc(LPVOID lpArg, DWORD timerLowVal, DWORD timerHighVal)
{
	_tprintf(_T("%s"), (TCHAR*)lpArg);
	MessageBeep(MB_ICONEXCLAMATION);
}