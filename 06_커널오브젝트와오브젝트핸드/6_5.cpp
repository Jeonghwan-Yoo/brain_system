//CloseHandle 함수 이해2
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD n = 0;
	//100회에 걸쳐 문자열을 출력한다.
	while (n < 100)
	{
		//실행속도를 늦춰 진행되는 상황을 용이하게 파악.
		for (DWORD i = 0;i < 10000;i++)
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!!

		_fputts(_T("KernelObjProb2.exe\n"), stdout);
		n++;
	}
	return 0;
}