//CloseHandle 함수 이해1
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int agrc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("KernelObjProb2.exe");
	//프로세스가 생성되면 커널 오브젝트도 생성되고 커널 오브젝트의 핸들은 pi를 통해서 얻게 된다.
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	//생성한 프로세스 핸들을 인자로 전달하여 호출
	CloseHandle(pi.hProcess);

	return 0;
}