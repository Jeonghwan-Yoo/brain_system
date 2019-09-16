//유니코드 기반의 파일 입력
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	TCHAR fileData[STRING_LEN];
	//파일을 읽기 모드로 개방하고 있다.
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD numOfByteRead = 0;
	//저장된 데이터를 읽어 들인다.
	ReadFile(hFile, fileData, sizeof(fileData), &numOfByteRead, NULL);
	//읽어 들인 데이터를 문자열로 구성한다.
	//저장된 데이터가 문자열의 형태로 저장되었다면 문제될 것 없지만, 그렇지 않으면
	//출력을 위해 데이터의 끝에 문자열의 끝을 의미하는 NULL(0)을 넣어준다.
	fileData[numOfByteRead / sizeof(TCHAR)] = 0;

	_tprintf(_T("Read data size:%u\n"), numOfByteRead);
	_tprintf(_T("Read string:%s\n"), fileData);

	CloseHandle(hFile);
	return 0;
}