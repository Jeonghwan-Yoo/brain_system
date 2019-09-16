//쓰레드의 상태 변경
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	while (1)
	{
		_tprintf(_T("Running State!\n"));
		Sleep(10000);
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId;
	HANDLE hThread;
	DWORD susCnt; //suspend count를 확인하기 위한 변수

	//쓰레드가 하는 일은 문자열을 출력하는 것이다.
	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, 
		//쓰레드 생성에 관련된 인자에 CREATE_SUSPENDED가 전달되면 쓰레드가 생성되자마자 서스팬드 카운트는 1.
		//즉 쓰레드가 생성되자나자 Blocked상태로 되는 것.
		CREATE_SUSPENDED,
		(unsigned*)&dwThreadId);

	//쓰레드 생성 확인
	if (hThread == NULL)
		_tprintf(_T("Thraed creation fault!\n"));

	//Blocked상태에 있으니 실행을 위해서 ResumeThread함수를 호출해줘야 한다.
	//호출된 이후, 쓰레드는 실행을 시작할 것이다.
	//그리고 함수 호출 시 반환 값을 1이다.
	//왜냐하면 감소하기 이전의 서스팬드 카운트를 반환하기 때문.
	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);
	Sleep(10000);

	//두 번 호출되니 서스팬드 카운트는 2가되고 ResumeThread함수가 두 번 호출되어야 쓰레드 실행이 재개된다.
	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);

	//프로세스의 종료를 막아 쓰레드의 실행을 확인하기 위해.
	WaitForSingleObject(hThread, INFINITE);
	return 0;
}