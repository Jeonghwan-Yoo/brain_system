//1. 1~10���� �����Ͽ� ���
//2. �������� ���ϰ� �ִ� ����
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
	
	//PartAdder.exe�� ������ ���� ���ڿ� �迭�� �����ϰ� �ִ�.
	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);
	//command1�� ������� ���μ����� �����ϰ� �ִ�.
	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);
	//command2�� ������� ���μ����� �����ϰ� �ִ�.
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hThread);

	//�ڽ� ���μ������� �����ϸ鼭 �����ϴ� �����ڵ带 ��� ���ؼ� �Լ��� ȣ���Ѵ�.
	GetExitCodeProcess(pi1.hProcess, &return_val1);
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	//�ڽ� ���μ����� ���������� ���Ḧ �ߴ��� Ȯ���Ѵ�.
	if (return_val1 == -1 || return_val2 == -1)
		return -1; //�������� ����

	//�� �ڽ� ���μ����� ��ȯ���� ���� ���� ����� �����Ѵ�.
	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("total : %d\n"), sum);

	CloseHandle(pi1.hProcess);
	CloseHandle(pi2.hProcess);

	return 0;
}