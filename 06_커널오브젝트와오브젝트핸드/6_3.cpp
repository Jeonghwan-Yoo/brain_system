//Ŀ�� ������Ʈ ���� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("Operation2.exe");

	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	DWORD timing = 0;
	while (1)
	{
		for (DWORD i = 0;i < 10000;i++)
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!!

		_fputts(_T("Parent\n"), stdout);

		timing += 1;
		if (timing == 2)
			//PROCESS_INFORMATION����ü ������ �ּҰ��� ���ڷ� �����ϸ鼭 ���ο� ���μ����� �����ϰ� �ִ�.
			//hProcess�� ���� ������ ���μ����� �ڵ� ������ ä������ �ȴ�.
			//NORMAL_PRIORITY_CLASS�� �����Ͽ� �켱������ �ٽ� �ǵ����� ȿ��.
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);
	}
	return 0;
}