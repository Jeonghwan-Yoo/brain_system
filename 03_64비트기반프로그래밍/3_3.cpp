#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(void)
{
	//파일을 개방하는 함수이다.
	//존재하지 않는 파일을 열도록 설정해 놓았으니 함수의 호출은 실패로 돌아갈 것이다.
	//CreateFile함수는 호출 실패할 경우 INVALID_HANDLE_VALUE를 반환한다.
	HANDLE hFile = CreateFile(_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL); //Windows system 함수
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//The system cannot find the file specified.
		_tprintf(_T("error code : %d\n"), GetLastError());
		return 0;
	}
	return 0;
}