//뮤텍스 반환에 관련 종료 핸들러 구성
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 7

LONG gTotalCount = 0;

HANDLE hMutex;

//뮤텍스 획득을 고대하는 WaitForSingleObject 함수 이후 부분을 __try로 묶고 있다.
//이어지는 __finally 블록을 통해 획득한 뮤텍스를 반환하는 ReleaseMutex 함수의 호출문을 삽입.
//그럼 이제 뮤텍스의 반환을 보장받을 수 있다.
//중간에 문제가 발생해 쓰레드를 종료해야만 하는 상황에 놓여도 뮤텍스의 소유권에 관한 문제가 생길 일은 없다.
void IncreaseCount()
{
	__try
	{
		WaitForSingleObject(hMutex, INFINITE);
		gTotalCount++;
	}
	__finally
	{
		ReleaseMutex(hMutex);
	}
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
	DWORD dwThreadIDs[NUM_OF_GATE];
	HANDLE hThreads[NUM_OF_GATE];

	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error:%d\n"), GetLastError());
	}

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		hThreads[i] = (HANDLE)_beginthreadex(
			NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadIDs[i]);

		if (hThreads[i] == NULL)
		{
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		ResumeThread(hThreads[i]);
	}
	WaitForMultipleObjects(NUM_OF_GATE, hThreads, TRUE, INFINITE);

	_tprintf(_T("total count:%d\n"), gTotalCount);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		CloseHandle(hThreads[i]);
	}
	CloseHandle(hMutex);
	return 0;
}