#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(void)
{
	//ABC.DAT라는 이름의 파일을 개방하려한다. 존재하지 않으므로 오류가 발생하고 다음 코드 실행.
	HANDLE hFile = CreateFile(_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("error code : %d\n"), GetLastError()); //오류 확인

	//ABC2.DAT라는 이름의 파일을 생성한다. 파일을 생성하는 것이므로 오류가 발생하지 않고 다음 코드 실행.
	hFile = CreateFile(_T("ABC2.DAT"), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, NULL);
	_tprintf(_T("error code : %d\n"), GetLastError()); //오류 확인
	return 0;
}