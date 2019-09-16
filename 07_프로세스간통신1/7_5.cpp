//1. 1~10까지 덧셈하여 출력
//2. 문제점을 지니고 있는 예제
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	DWORD return_val1;
	DWORD return_val2;
	
	//PartAdder.exe의 실행을 위한 문자열 배열을 선언하고 있다.
	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);
	//command1을 기반으로 프로세스를 생성하고 있다.
	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);
	//command2을 기반으로 프로세스를 생성하고 있다.
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);

	//자식 프로세스들이 종료하면서 전달하는 종료코드를 얻기 위해서 함수를 호출한다.
	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	//자식 프로세스가 비정상적인 종료를 했는지 확인한다.
	if (return_val1 == -1 || return_val2 == -1)
		return -1; //비정상적 종료

	//두 자식 프로세스가 반환해준 값을 더해 출력을 진행한다.
	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("total : %d\n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}