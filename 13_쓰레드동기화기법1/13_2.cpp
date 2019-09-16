//생성 가능한 쓰레드의 개수 측정
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//크리티컬 섹션 오브젝트가 선언.
CRITICAL_SECTION hCriticalSection;

void IncreaseCount()
{
	//임계영역 진입 이전에 EnterCriticalSection, 빠져나오면서 LeaveCriticalSection.
	//임계 영역은 쓰레드에 의해 동시에 실행되는 일이 발생하지 않도록 완전히 동기화.
	EnterCriticalSection(&hCriticalSection);
	gTotalCount++; //둘 이상의 쓰레드에 의해 진행되는 코드여서 임계 영역을 형성하는 원인.
	LeaveCriticalSection(&hCriticalSection);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0;i < 1000;i++)
	{
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	//크리티컬 섹션 오브젝트의 초기화.
	//크리티컬 섹션 동기화에 필요한 모든 초기화가 이뤄진다.
	InitializeCriticalSection(&hCriticalSection);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		hThread[i] = 
			(HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		ResumeThread(hThread[i]);
	}

	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count : %d\n"), gTotalCount);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		CloseHandle(hThread[i]);
	}

	DeleteCriticalSection(&hCriticalSection);
	return 0;
}