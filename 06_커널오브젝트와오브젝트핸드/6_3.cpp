//커널 오브젝트 공유 예제
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
			//PROCESS_INFORMATION구조체 변수의 주소값을 인자로 전달하면서 새로운 프로세스를 생성하고 있다.
			//hProcess는 새로 생성된 프로세스의 핸들 정보로 채워지게 된다.
			//NORMAL_PRIORITY_CLASS로 변경하여 우선순위를 다시 되돌리는 효과.
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);
	}
	return 0;
}