//단순 출력 프로그램
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//우선순위 계층을 NORMAL_PRIORITY_CLASS로 설정한다. 디폴트 우선순위이기도 하다.
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0;i < 10000;i++)
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!

		//Sleep(10);

		_fputts(_T("NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}
	return 0;
}