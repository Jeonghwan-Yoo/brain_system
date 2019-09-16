//환경변수 설정하는 부모 프로세스
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//환경변수 등록.
	SetEnvironmentVariable(_T("Good"), _T("morning"));
	SetEnvironmentVariable(_T("Hey"), _T("Ho!"));
	SetEnvironmentVariable(_T("Big"), _T("Boy"));

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	//7번째 전달인자를 통해 자식프로세스에게 등록하고픈 환경변수를 설정할 수 있다.
	//key = value
	//여기서는 NULL로 지정해, 부모 프로세스에 등록되어 있는 환경변수를 등록하겠다는 의미.
	CreateProcess(
		NULL, const_cast<LPSTR>(_T("EnvChild")), NULL, NULL, FALSE, 
		CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		NULL, //부모 프로세스의 환경변수 등록
		NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}