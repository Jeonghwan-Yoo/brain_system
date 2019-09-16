//디렉터리의 생성과 소멸
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//조건부 컴파일문에 의해 생성한다 0으로 둘 경우 삭제.
#define CREATE_DIRECTORY 0

int _tmain(int argc, TCHAR* argv[])
{
	//각각 상대경로의 디렉터리 생성과 절대경로의 디렉터리 생성을 보여주기 위해 각각의 경로를 임의로 선언.
	//주의할 사항은 절대경로 지정 시 마지막 디렉터리만 생성해준다.

	TCHAR dirReletivePath[] = _T("GoodDirectoryOne");
	TCHAR dirFullPath[] = _T("D:\\GoodDirectoryTwo");

#if CREATE_DIRECTORY
	CreateDirectory(dirReletivePath, NULL);
	CreateDirectory(dirFullPath, NULL);
#else
	RemoveDirectory(dirReletivePath);
	RemoveDirectory(dirFullPath);
#endif
	return 0;
}