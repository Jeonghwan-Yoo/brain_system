//DuplicateHandle 함수의 이해
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hParent = (HANDLE)_ttoi(argv[1]);
	//WaitForSingleObject함수를 호출하면서 부모 프로세스의 핸들을 인자로 받고 있다.
	//부모 프로세스가 종료될 때까지 기다리는 것.
	DWORD isSuccess = WaitForSingleObject(hParent, INFINITE);

	_tprintf(_T("[Child Process]\n"));

	if (isSuccess == WAIT_FAILED)
	{
		_tprintf(_T("WAIT_FAILED returned!"));
		Sleep(10000);
		return -1;
	}
	else 
	{
		_tprintf(_T("General Lee said, \"Don't inform") _T("the enemy my death\""));
		Sleep(10000);
		return 0;
	}
}