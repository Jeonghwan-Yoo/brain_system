//디렉터리 내에 존재하는 파일 리스트 출력
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR DirSpec[MAX_PATH];

	_tprintf(_T("Insert tartget directory:"));
	//검색하고자 하는 디렉터리 정보를 입력받음.
	//"C:\Best"라고 하면 그 안에 존재하는 파일과 디렉터리 이름을 모두 출력하고자 하는 것.
	_tscanf(_T("%s"), DirSpec);
	//만들고자 하는 것은 디렉터리의 내용을 모두 보여주는 프로그램.
	//*는 All의 의미를 내포하는 Wildcard 문자.
	//"C:\Best\*"가 된다.
	//만약 확장자가 exe로 끝나는 파일만 검색하기 원한다면 "C:\Best\*.exe"
	_tcsncat(DirSpec, _T("\\*"), 3);

	//조건에 맞는 첫 번째 파일을 찾고 있으며,
	hFind = FindFirstFile(DirSpec, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Invalid file handle\n"));
		return -1;
	}
	else
	{
		_tprintf(_T("First file name is %s\n"), FindFileData.cFileName);
		//두 번째 이후 파일을 찾고 있다.
		//FindNextFile 함수는 대상을 찾지 못하면 0을 반환한다.
		//0을 반환할 때까지 이 함수를 호출하므로, 조건에 맞는 모든 파일을 찾게 된다.
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			_tprintf(_T("Next file name is %s\n"), FindFileData.cFileName);
		}
		//핸들을 닫아 주고 있다.
		FindClose(hFind);
	}
	return 0;
}