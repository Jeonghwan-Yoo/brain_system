//���α׷� ���� ����� ���� ��ȯ�� Ȯ��
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

	//���ο� ���μ����� �����ϰ� �ִ�.
	state = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	//�ڽ� ���μ����� ����� ���� ��ٸ��� �ڵ��̴�.
	//�ڽ� ���μ����� ����� ���� �Ϸ�� ���̶�� ������ ��� �ִ�.
	//�����δ� �Ʒ��ִ� �Լ��� �����ϴµ� �ڽ����μ�����(���ڷ� ���޵� �ڵ��� ����Ų ���μ�����)
	//����� ������ ��ٸ��� ����� �Լ��̴�.
	//for (DWORD i = 0;i < 10000;i++) //Child Process�� �켱���� ����
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