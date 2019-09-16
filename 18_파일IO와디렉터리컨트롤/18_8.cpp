//파일 포인터의 이동 32비트 버전
//abcd.dat라는 이름의 파일을 생성한 다음 알파벳을 입력한다.
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100
TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	HANDLE hFile;
	DWORD numOfByteWritten = 0;
	DWORD dwPtr = 0;

	//file write
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	CloseHandle(hFile);

	//file read
	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	//파일 포인터를 맨 앞으로 이동
	//SetFilePointer 함수의 호출을 통해 파일 포인터 위치를 맨 앞으로 이동한 다음에, 문자 4개의 위치만큼
	//뒤로 건너 뛰고 있다.
	//sizeof(TCHAR)로 4개의 위치를 지정하였으므로 유니코드 기반이라면 8바이트를 건너뛰게 된다.
	//세번째 전달인자는 NULL로 4GB 이상이 되는 파일에 대해서는 신경쓰지 않고 지원하지 않는다.
	dwPtr = SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);
	//SetFilePointer 함수의 반환값이 INVALID_SET_FILE_POINTER라면 오류가 발생하였음을 의미.
	//#define INVALID_SET_FILE_PIONTER ((DWORD)-1)
	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		_tprintf(_T("SetFilePointer Error\n"));
		return -1;
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	//파일 포인터를 맨 뒤로 이동
	//파일 포인터 위치를 맨 뒤로 이동한 ㄴ다음에, 문자 4개의 위치만큼을 앞으롤 이동시키고 있다.
	//-가 붙어있으므로 앞으로 이동하게 된다.
	dwPtr = SetFilePointer(hFile, -(sizeof(TCHAR) * 4), NULL, FILE_END);
	if (dwPtr == INVALID_SET_FILE_POINTER) //Test for failure
	{
		_tprintf(_T("SetFilePointer Error\n"));
		return -1;
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	CloseHandle(hFile);
	return 0;
}