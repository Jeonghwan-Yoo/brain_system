//유니코드 기반의 파일 출력
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	TCHAR fileData[] = _T("Just test string~");

	//파일을 쓰기 모드로 개방하고 있다.
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault!\n"));
		return -1;
	}

	DWORD numOfByteWritten = 0;
	//하나의 문자열을 저장한다.
	//유니코드 기반으로 선언되어 있어, 한 문자당 2바이트씩 저장된다.
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);

	_tprintf(_T("Written data size:%u\n"), numOfByteWritten);
	CloseHandle(hFile);

	return 0;
}