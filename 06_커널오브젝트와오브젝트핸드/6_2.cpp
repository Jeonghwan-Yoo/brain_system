//단순 출력 프로그램2
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//첫 번째 인자는 전달된 핸들이 가리키는 프로세스의 우선순위를 두 번째 인자로 전달된 우선순위 값으로 변경.
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	while (1)
	{
		for (DWORD i = 0;i < 10000;i++)
		{
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!!
		}
		_fputts(_T("Operation2.exe\n"), stdout);
	}
	return 0;
}