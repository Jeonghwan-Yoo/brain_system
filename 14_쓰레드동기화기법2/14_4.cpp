//"아래의 프로그램은 Windows NT이상에서 실행하겠습니다. 그러니 SetWaitableTime 함수호출을 허용해주세요.
#define _WIN32_WINNT 0x0400

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	//LARGE_INTEGER라는 자료형은 Windows에서 union으로 선언되어 있는 자료형이다.
	//이 자료형은 64비트 정수를 표현하기 위해 등장한 자료형.
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	//타이머 오브젝트 생성
	//이때 얻은 핸들을 인자로 전달하면서 뒤에서 알람 시간을 설정.
	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}
	_tprintf(_T("Waiting for 10 seconds...\n"));

	//타이머의 알람을 10초로 설정
	//두 번째 인자는 0보다 작은 값으로 상대시간으로 알람이 설정된 것.
	//100000000나노초 후(10초 후에) 알람이 울릴 것이다. 즉 타이머 오브젝트가 Signaled 상태가 될 것.
	//세 번째 전달인자는 0으로 타이머의 알람이 주기적으로 울리지 않고 한 번만 울리도록 설정한다는 의미.
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);

	//타이머의 알람을 대기
	//타이머 오브젝트가 Signaled 상태가 되기만을 기다린다.
	//10초 후에는 Signaled 상태가 되어 WaitForSingleObject 함수를 빠져나오고,
	//MessageBeep함수를 호출하면 작은 소리를 내게 된다.
	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(_T("Timer was signaled.\n"));
	MessageBeep(MB_ICONEXCLAMATION);

	return 0;
}