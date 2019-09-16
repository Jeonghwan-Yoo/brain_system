//프로그램 실행 결과에 따른 반환값 확인
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	DWORD state;

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	si.lpTitle = const_cast<LPWSTR>(_T("return & exit"));

	TCHAR command[] = _T("OperationStateChild.exe");

	//새로운 프로세스를 생성하고 있다.
	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	//자식 프로세스가 종료될 것을 기다리는 코드이다.
	//자식 프로세스가 충분히 실행 완료될 것이라는 가정이 깔려 있다.
	//실제로는 아래있는 함수를 실행하는데 자식프로세스가(인자로 전달된 핸들이 가리킨 프로세스가)
	//종료될 때까지 기다리는 기능의 함수이다.
	//for (DWORD i = 0;i < 10000;i++) //Child Process의 우선종료 위해
		//for (DWORD i = 0;i < 10000;i++);
	WaitForSingleObject(pi.hProcess, INFINITE);

	GetExitCodeProcess(pi.hProcess, &state);
	if (state == STILL_ACTIVE)
		_tprintf(_T("STILL_ACTIVE\n\n"));
	else
		_tprintf(_T("staete : %d\n\n"), state);
	
	//CloseHandle(pi.hProcess);
	return 0;
}