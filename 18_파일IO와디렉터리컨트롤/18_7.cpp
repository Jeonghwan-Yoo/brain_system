//파일이름 기반으로 완전경로 얻어오기
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	TCHAR fileFullPathName[STRING_LEN];
	LPTSTR filePtr;

	GetFullPathName(fileName, STRING_LEN, fileFullPathName, &filePtr);

	_tprintf(_T("%s\n"), fileFullPathName);
	_tprintf(_T("%s\n"), filePtr);

	return 0;
}