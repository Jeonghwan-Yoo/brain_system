//DuplicateHandle �Լ��� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hProcess;
	TCHAR cmdString[1024];

	//GetCurrentProcess�Լ��� ���ؼ� ��� �Ǵ� ��¥ �ڵ��� ��¥ �ڵ�� �����ؼ� �ڵ� ���̺� ����ϰ� �ִ�.
	//�ڵ� ���̺� ��ϵ� ������ �ڽ� ���μ����� ����� �����ϴϱ� �ڽ����μ����� �θ����μ����� �ڵ��� ��´�.
	//������° ���ڷ� TRUE�� �����ؼ� ��� ������ �ڵ�� �����.
	DuplicateHandle(
		GetCurrentProcess(), GetCurrentProcess(),
		GetCurrentProcess(), &hProcess, 0,
		TRUE, DUPLICATE_SAME_ACCESS
	);

	_stprintf(cmdString, _T("%s %u"), _T("ChildProcess.exe"), (unsigned)hProcess);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	//���� �ڽ� ���μ����� �θ� ���μ����� �ڵ� ������ ��� �Ǿ���.
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