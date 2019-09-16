//대용량 파일의 파일 포인터 이동
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

	LONG lDistanceLow = sizeof(TCHAR) * 4;
	LONG lDistanceHigh = 0;

	//file write
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	CloseHandle(hFile);

	//file read
	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	//파일 포인터를 맨 앞으로 이동
	//4GB 이상의 대용량 파일 위치 정보를 표현하려면 8바이트가 필요한데, SetFilePointer 함수는 반환형이건,
	//매개변수 자료형이건 어느 것도 8B를 표현할 수 있는 것이 없다.
	//모두 4바이트 자료형으로 선언되어 있고 상위 4바이트와 하위 4바이트를 나눠서 표현하도록 함수가 정의.
	//이것이 이 함수의 사용법을 번거롭게하는 이유고, 파일 포인터 이동이라는 작업을 번거롭게 한다.
	//두 번째, 세 번째 전달되는 인자가 각각 하위 4B와 상위 4B 정보를 표현한다. (상위를 0으로 초기화했다).
	//그런데 전달되는 인자 타입이 다른데, 두 번째는 하위 4B정보를 단순히 전달하는 용도(Call By Value).
	//그러나 세 번째 전달인자는 정보의 획득을 위해서도 사용되기 때문에 포인터를 인자로 전달(Call By Pointer).
	//64비트 기반 코드 구현에서는 호출 성공 시 64비트 위치 정보를 반환해줘야 하는데 반환 타입이 
	//4B 자료형이라 불가능하다.
	//그래서 SetFilePointer 함수 호출 성공 시 파일 포인터의 하위 4바이트 정보를 반환값을 통해서,
	//상위 4바이트 정보는 SetFilePointer 함수의 세 번째 전달인자가 가리키는 변수를 통해 반환하기로 정의.
	dwPtr = SetFilePointer(hFile, lDistanceLow, &lDistanceHigh, FILE_BEGIN);
	//함수의 반환값을 통해 오류검사를 하고 있다.
	if ((dwPtr == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR))
	{
		_tprintf(_T("SetFilePointer Error\n"));
		return -1;
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	CloseHandle(hFile);
	return 0;
}