//CloseHandle �Լ� ����1
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int agrc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("KernelObjProb2.exe");
	//���μ����� �����Ǹ� Ŀ�� ������Ʈ�� �����ǰ� Ŀ�� ������Ʈ�� �ڵ��� pi�� ���ؼ� ��� �ȴ�.
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	//������ ���μ��� �ڵ��� ���ڷ� �����Ͽ� ȣ��
	CloseHandle(pi.hProcess);

	return 0;
}