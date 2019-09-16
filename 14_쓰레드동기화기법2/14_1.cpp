#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h> //_beginthreadex, _endthreadex

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID;

	//main쓰레드가 하는일. 동기화를 이벤트 오브젝트를 생성한다. 수동 리셋 모드로 생성하고 있다.
	hEvent = CreateEvent( //event object 생성
		NULL, //상속불가
		TRUE, //manual-reset mode로 생성
		FALSE, //non-signaled 상태로 생성
		NULL //이름없는 event
	);
	if (hEvent == NULL)
	{
		_fputts(_T("Event object creation error\n"), stdout);
		return -1;
	}

	//OutputThreadFunction을 main으로 하는 쓰레드를 생성하고 있다.
	//생성하자마자 앞서 생성한 이벤트 오브젝트가 Signaled 상태가 될 것을 기다린다.
	hThread = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread == 0)
	{
		_fputts(_T("Thread creation error\n"), stdout);
		return -1;
	}
	_fputts(_T("Insert string:"), stdout);
	//main쓰레드는 콘솔로부터 문자열을 입력받은 후에 이벤트 오브젝트를 Signaled 상태로 변경시킨다.
	//문자열을 입력받고 난 다음,
	_fgetts(string, 30, stdin);

	SetEvent(hEvent); //event의 state를 signaled상태로 변경

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent); //event 오브젝트 소멸
	CloseHandle(hThread);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	//event가 signaled 상태가 되기를 기다린다.
	//이벤트 오브젝트가 Signaled 상태가 되었으므로, 블로킹된 쓰레드는 함수를 빠져 나와서 나머지 부분(콘솔출력)을
	//실행한다. 수동리셋모드로 이벤트를 생성하였으므로 WaitForSingleObject를 빠져나온 다음에도 Signaled 상태.
	//굳이 이벤트 오브젝트를 Non-Signaled 상태로 변경할 필요가 없어 변경하는 코드는 없다.
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string:"), stdout);
	_fputts(string, stdout);

	return 0;
}