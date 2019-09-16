#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//타이머 오브젝트 생성
	//두 번째 전달인자가 FALSE로 자동 리셋모드 타이머 오브젝트가 생성된다.
	//FALSE가 되어야 자동으로 타이머가 Non-Signaled 상태가 되어 계속되는 알람에 반응하게 된다.
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	//알람을 10초 후에, 그리고 5초 간격으로 설정한다.
	//세 번째 전달인자는 1/1000초 단위로 계산되므로 5초 간격으로 알람.
	SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

	//타이머의 알람을 대기
	while (1)
	{
		//무한 반복을 돌면서 타이머 오브젝트가 Signaled 상태가 되기를 기다리고 있다.
		//첫 알람 이후에 5초 간격으로 알람이 울리므로 5초에 한 번씩 블로킹된 함수를 빠져나와 알람을 울린다.
		WaitForSingleObject(hTimer, INFINITE);
		_tprintf(_T("Timer was signaled.\n"));
		MessageBeep(MB_ICONEXCLAMATION);
	}
	return 0;
}