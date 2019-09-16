//DuplicateHandle 함수의 이해
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hProcess;
	TCHAR cmdString[1024];

	//GetCurrentProcess함수를 통해서 얻게 되는 가짜 핸들을 진짜 핸들로 구성해서 핸들 테이블에 등록하고 있다.
	//핸들 테이블에 등록된 정보는 자식 프로세스로 상속이 가능하니까 자식프로세스는 부모프로세스의 핸들을 얻는다.
	//여섯번째 인자로 TRUE를 전달해서 상속 가능한 핸들로 만든다.
	DuplicateHandle(
		GetCurrentProcess(), GetCurrentProcess(),
		GetCurrentProcess(), &hProcess, 0,
		TRUE, DUPLICATE_SAME_ACCESS
	);

	_stprintf(cmdString, _T("%s %u"), _T("ChildProcess.exe"), (unsigned)hProcess);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	//이제 자식 프로세스는 부모 프로세스의 핸들 정보를 얻게 되었다.
	BOOL isSuccess = CreateProcess(NULL, cmdString, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL,
		NULL, &si, &pi);

	if (isSuccess == FALSE)
	{
		_tprintf(_T("CreateProcess failed\n"));
		return -1;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_tprintf(_T("[Parent Process]\n"));
	_tprintf(_T("oooooooooooooooooooops!\n"));
	return 0;
}