//임계 영역에 대한 이해
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//전역변수를 1씩 증가시키는 역할.
//생성된 여섯 개의 쓰레드는 입장객의 수를 전역변수에 등록하게 된다.
void IncreaseCount()
{
	gTotalCount++; //임계 영역
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0;i < 1000;i++)
	{
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR** argv)
{
	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		hThread[i] = 
			//CREATE_SUSPEND를 전달하므로 생성된 쓰레드는 바로실행되지 않는다.
			(HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		//함수가 호출되는 시점에서 쓰레드가 실행.
		//쓰레드의 생성은 상대적으로 시간이 걸리기 때문에 쓰레드를 먼저 생성해 놓고 동시에 실행을 시켜,
		//쓰레드 실행에 있어서 발생하는 시간차를 최소화하려고 하였다.
		ResumeThread(hThread[i]);
	}
	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count : %d\n"), gTotalCount);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		CloseHandle(hThread[i]);
	}
	return 0;
}