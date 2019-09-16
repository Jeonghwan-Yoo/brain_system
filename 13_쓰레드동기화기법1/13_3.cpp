//크리티컬 섹션과 뮤텍스 비교
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//뮤텍스는 커널 오브젝트이므로 HANDLE타입의 변수에 핸들값을 저장한다.
//CRITICAL_SECTION gCriticalSection;
HANDLE hMutex;

void IncreaseCount()
{
	//뮤텍스를 얻기위해
	//EnterCriticalSection(&gCriticalSection);
	WaitForSingleObject(hMutex, INFINITE);

	gTotalCount++;

	//획득한 뮤텍스를 반환하고 뮤텍스가 Signaled상태가 된다.
	//LeaveCriticalSection(&gCriticalSection);
	ReleaseMutex(hMutex);
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

	//뮤텍스를 생성하고 있다. FALSE는 누구에게도 소유되지 않은 상태로 생성된다. Signaled상태로 뮤텍스 생성.
	//InitializeCriticalSection(&gCriticalSection);
	hMutex = CreateMutex(
		NULL, //디폴트 보안 관리자
		FALSE, //누구나 소유할 수 있는 상태로 생성
		NULL //unnamed mutex
	);
	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error : %d\n"), GetLastError());
	}

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
	
	//할당받은 리소스의 해제.
	//함수를 호출하는 시점에서 운영체제에 의해 할당된 커널 오브젝트가 소멸된다.(Usage Count = 0)
	//DeleteCriticalSection(&gCriticalSection);
	CloseHandle(hMutex);
	return 0;
}