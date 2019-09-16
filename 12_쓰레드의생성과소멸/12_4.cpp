//전역변수를 이용한 쓰레드 기반 Adder
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//전역변수 total을 선언
//이 변수는 어디에서나 접근 가능하다.
static int total = 0;

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD* nPtr = (DWORD*)lpParam;
	DWORD numOne = *nPtr;
	DWORD numTwo = *(nPtr + 1);

	for (DWORD i = numOne;i < numTwo;i++)
	{
		total += i;
	}
	return 0; //정상적 종료
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];

	DWORD paramThread[] = { 1,3,4,7,8,10 };

	hThread[0] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[0]), 0, &dwThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[1]), 2, &dwThreadID[1]);
	hThread[2] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[2]), 4, &dwThreadID[2]);

	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault!\n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);

	return 0;
}