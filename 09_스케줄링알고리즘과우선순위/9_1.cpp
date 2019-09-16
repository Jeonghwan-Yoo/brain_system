//두 개의 자식 프로세스를 생성하는 부모 프로세스
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO siNORMAL = { 0, };
	PROCESS_INFORMATION piNORMAL;
	TCHAR commandOne[] = _T("NORMAL_PRIORITY_CLASS.exe");

	STARTUPINFO siBELOW = { 0, };
	PROCESS_INFORMATION piBELOW;
	TCHAR commandTwo[] = _T("BELOW_NORMAL_PRIORITY_CLASS.exe");

	siNORMAL.cb = sizeof(siNORMAL);
	siBELOW.cb = sizeof(siBELOW);

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	//자식 프로세스 생성.
	CreateProcess(NULL, commandOne, NULL, NULL, TRUE, 0, NULL, NULL, &siNORMAL, &piNORMAL);
	CreateProcess(NULL, commandTwo, NULL, NULL, TRUE, 0, NULL, NULL, &siBELOW, &piBELOW);

	//메시지 출력을 반복.
	while (1)
	{
		//프로세스가 쉬는 것이 아니라 여전히 일을 하고 있는 상황이다. 절대로 다른 프로세스에게
		//실행의 기회를 넘기는 코드가 아니다.
		for (DWORD i = 0;i < 10000;i++)
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!

		//Sleep(10);
		//프로세스의 실행을 멈추는 역할을 한다.
		//0.01초 동안 Blocked 상태로 존재하다가 Ready 상태로 전환될 것이다.
		//우선순위가 일반 프로세스보다 높게 설정되어 있으므로 스케줄러에 의해 다시 Running상태로 이동.
		_fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}