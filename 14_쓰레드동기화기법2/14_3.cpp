#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h> //_beginthreadex, _endthreadex

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

//서로 관계가 깊은 데이터들은 구조체나 클래스로 묶는 것이 좋은 코드.
//생산자/소비자 모델을 구성하는 주 매개체인 문자열 배열과, 이 배열에 접근하는데 있어서 동기화를 제공하기 위한
//이벤트와 뮤텍스를 하나의 구조체로 묶고 있다.
typedef struct _SynchString {
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
} SynchString;

SynchString gSynString;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThreads[2];
	DWORD dwThreadIDs[2];

	gSynString.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	gSynString.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (gSynString.hEvent == NULL || gSynString.hMutex == NULL)
	{
		_fputts(_T("kernel object creation error\n"), stdout);
		return -1;
	}

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadIDs[0]);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, CountThreadFunction, NULL, 0, (unsigned*)&dwThreadIDs[1]);

	if (hThreads[0] == 0 || hThreads[1] == 0)
	{
		_fputts(_T("Thraed creation error\n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string:"), stdout);
	_fgetts(gSynString.string, 30, stdin);

	SetEvent(gSynString.hEvent);
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	CloseHandle(gSynString.hEvent);
	CloseHandle(gSynString.hMutex);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSynString.hEvent, INFINITE);
	WaitForSingleObject(gSynString.hMutex, INFINITE);

	_fputts(_T("Output string:"), stdout);
	_fputts(gSynString.string, stdout);

	ReleaseMutex(gSynString.hMutex);
	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSynString.hEvent, INFINITE);
	WaitForSingleObject(gSynString.hMutex, INFINITE);
	_tprintf(_T("Output string length:%d\n"), _tcslen(gSynString.string) - 1);

	ReleaseMutex(gSynString.hMutex);
	return 0;
}