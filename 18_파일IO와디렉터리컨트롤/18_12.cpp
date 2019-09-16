//시스템 디렉터리와 Windows 디렉터리의 확인
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//MAX_PATH는 헤더파일 windef.h에 선언되어 있다.
	//이는 디폴트 최대경로 길이 248을 고려하여 선언된 매크로 상수이다.
	//따라서 파일 이름(완전 경로를 포함하는)을 저장하기 위한 문자열 버퍼를 선언할 때 활용할 수 있다.
	//#define MAX_PATH 260
	TCHAR sysPathBuf[MAX_PATH];
	TCHAR winPathBuf[MAX_PATH];

	GetSystemDirectory(sysPathBuf, MAX_PATH);
	GetWindowsDirectory(winPathBuf, MAX_PATH);

	_tprintf(_T("System dir:%s\n"), sysPathBuf);
	_tprintf(_T("Windows dir:%s\n"), winPathBuf);
	return 0;
}