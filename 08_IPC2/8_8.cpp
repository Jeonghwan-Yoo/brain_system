//ȯ�溯�� �����ϴ� �θ� ���μ���
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//ȯ�溯�� ���.
	SetEnvironmentVariable(_T("Good"), _T("morning"));
	SetEnvironmentVariable(_T("Hey"), _T("Ho!"));
	SetEnvironmentVariable(_T("Big"), _T("Boy"));

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	//7��° �������ڸ� ���� �ڽ����μ������� ����ϰ��� ȯ�溯���� ������ �� �ִ�.
	//key = value
	//���⼭�� NULL�� ������, �θ� ���μ����� ��ϵǾ� �ִ� ȯ�溯���� ����ϰڴٴ� �ǹ�.
	CreateProcess(
		NULL, const_cast<LPSTR>(_T("EnvChild")), NULL, NULL, FALSE, 
		CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		NULL, //�θ� ���μ����� ȯ�溯�� ���
		NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}