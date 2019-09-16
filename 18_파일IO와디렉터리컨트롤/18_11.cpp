//현재 디렉터리의 이해
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100
TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	HANDLE hFileWrite;
	HANDLE hFileRead;
	DWORD numOfByteWritten;

	//file write
	//파일을 생성하고 있다.
	//생성될 경로 정보를 추가하지 않았으므로 현재 디렉터리에 생성.
	hFileWrite = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFileWrite, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	CloseHandle(hFileWrite);

	//현재 디렉터리 변경
	SetCurrentDirectory(_T("D:\\"));

	//file read
	//생성한 파일을 개방하고 있다.
	//파일의 위치 정보(디렉터리 정보)를 전달하지 않았으므로 현재 디렉터리에서 파일을 찾는다.
	//현재 디렉터리 정보가 변경되어 실패하게 된다.
	hFileRead = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFileRead == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File open error!\n"));
		return -1;
	}

	ReadFile(hFileRead, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);
	CloseHandle(hFileRead);

	return 0;
}