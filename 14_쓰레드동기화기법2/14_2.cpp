#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h> //_beginthreadex, _endthreadex

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread[2];
	DWORD dwThreadID[2];

	//이벤트 오브젝트가 Signaled 상태가 되면서 하나의 쓰레드만 WairForSingleObject 함수를 빠져 나와 실행.
	//이벤트 오브젝트가 자동 리셋 모드로 생성.
	//이벤트 오브젝트가 자동으로 Non-Signaled 상태가 되므로, 두 번째 쓰레드는 여전히 WaitForSingleObject
	//함수를 빠져 나오지 못한다.
	//수동 리셋 모드로 이벤트를 생성시키면 Signaled 상태에서 Non-Signaled로 자동 변경되지 않는다.
	//이벤트 오브젝트가 Signaled 상태가 되기를 기다리는 모든 쓰레드는 블로킹된 WaitForSingleObject 함수를
	//빠져 나와서 실행을 완성할 수 있다.
	hEvent = CreateEvent( //event object 생성
		NULL, //상속 불가
		FALSE, //auto-reset mode로 생성
		FALSE, //non-signaled 상태로 생성
		NULL //이름없는 event
	);
	if (hEvent == NULL)
	{
		_fputts(_T("Event object creation error\n"), stdout);
		return -1;
	}
	
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID[0]);
	//CountThreadFunction함수를 호출하는 쓰레드를 하나 더 생성한다.
	//이 쓰레드는 입력된 문자열의 길이를 계산하는 쓰레드이므로, 이벤트가 Signaled상태가 되기를 기다린다.
	//즉 하나의 이벤트 오브젝트가 Signaled 상태가 되기를 기다리를 쓰레드가 총 두 개가 된 것.
	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, CountThreadFunction, NULL, 0, (unsigned*)&dwThreadID[1]);

	if (hThread[0] == 0 || hThread[1] == 0)
	{
		_fputts(_T("Thread creation error\n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string:"), stdout);
	_fgetts(string, 30, stdin);

	SetEvent(hEvent); //event의 state를 signaled 상태로 변경

	WaitForMultipleObjects(
		2, //배열의 길이
		hThread, //핸들의 배열
		TRUE, //모든 핸들이 신호받은 상태로 될 때 리턴.
		INFINITE //무한 대기
	);
	
	CloseHandle(hEvent); //event 오브젝트 소멸
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	_fputts(_T("output string:"), stdout);
	_fputts(string, stdout);

	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);
	_tprintf(_T("output string length:%d\n"), _tcslen(string) - 1);
	return 0;
}