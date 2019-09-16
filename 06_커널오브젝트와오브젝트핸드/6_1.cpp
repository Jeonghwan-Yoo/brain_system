//단순 출력 프로그램1
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	TCHAR command[] = _T("Operation2.exe");

	//Operation2.exe라는 이름의 실행파일 실행으로 이어진다.
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	
	while (1)
	{
		//출력 속도를 늦추기 위함. 하지만 Sleep과는 다르다.
		for (DWORD i = 0;i < 10000;i++)
		{
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!! 대기상태
			//프로세스가 루프를 완전히 돌 때까지 다음 줄이 실행되지 않기 떄문에 멈춰보인다.
			//Sleep함수를 이용해 프로세스의 실행을 늦춘다면 프로세스는 Blocked상태가 되서 다른 프로세스 실행.
		}
		_fputts(_T("Operation1.exe\n"), stdout);
	}
	return 0;
}