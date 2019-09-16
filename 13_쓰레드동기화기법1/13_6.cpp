#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

LONG gTotalCount = 0;
HANDLE hMutex;

//이 함수의 문제점은 뮤텍스를 획득한 이후에 반환하는 코드 없이 함수를 종료한다는 것.
//IncreaseCountTwo 함수를 쓰레드함수로 하는 쓰레드는 뮤텍스를 얻지 못하는 상황에 놓이게 된다.
//이러한 상황을 감지한 Windows는 뮤텍스의 소유를 대기하는 쓰레드가 뮤텍스를 획득할 수 있도록 뮤텍스의 상태를 변경.
unsigned int WINAPI IncreaseCountOne(LPVOID lpParam)
{
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;
	return 0;
}

unsigned int WINAPI IncreaseCountTwo(LPVOID lpParam)
{
	DWORD dwWaitResult = 0;
	//뮤텍스의 획득을 기대하는 쓰레드는 반환값 WAIT_ABANDONED을 얻게된다.
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		ReleaseMutex(hMutex);
		break;
	case WAIT_ABANDONED:
		_tprintf(_T("WAIT_ABANDONED\n"));
		break;
	}
	gTotalCount++;
	ReleaseMutex(hMutex);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadIDOne;
	DWORD dwThreadIDTwo;

	HANDLE hThreadOne;
	HANDLE hThreadTwo;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL)
		_tprintf(_T("CreateMutex error:%d\n"), GetLastError());

	//무례한 쓰레드
	hThreadOne = (HANDLE)_beginthreadex(
		NULL, 0, IncreaseCountOne, NULL, 0, (unsigned*)&dwThreadIDOne
	);
	//쓰레드의 실행을 늦추기 위해 CREATE_SUSPENDED을 전달.
	hThreadTwo = (HANDLE)_beginthreadex(
		NULL, 0, IncreaseCountTwo, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadIDTwo
	);
	//약 0.1초 후에 함수를 호출시키면서 실행이 시작.
	//두 번째 쓰레드의 실행시간을 늦춰 첫 번째 쓰레드가 먼저 뮤텍스를 얻도록 하기 위함.
	Sleep(1000);
	ResumeThread(hThreadTwo);

	WaitForSingleObject(hThreadTwo, INFINITE);
	_tprintf(_T("total count:%d\n"), gTotalCount);

	CloseHandle(hThreadOne);
	CloseHandle(hThreadTwo);
	CloseHandle(hMutex);

	return 0;
}