#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePath[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	_tprintf(_T("Insert name of the file to find:"));
	//찾고자 하는 파일의 이름을 입력받아
	_tscanf(_T("%s"), fileName);
	//경로를 찾기 위한 SearchPath 함수를 호출한다.
	//첫 번째 인자가 NULL이어서 특정 디렉터리 위치를 지정하지 않은 것.
	//따라서 프로그램이 로드된 디렉터리를 시작으로 환경변수 PATH에 등록된 디렉터리들까지 순차적으로 검색.
	result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart);
	if (result == 0)
	{
		_tprintf(_T("File not found!\n"));
	}
	else
	{
		_tprintf(_T("File path:%s\n"), bufFilePath);
		_tprintf(_T("File name only:%s\n"), lpFilePart);
	}
	return 0;
}