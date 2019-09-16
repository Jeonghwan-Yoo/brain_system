//Memory mapped file 구현
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//1단계:파일 핸들 생성.
	//읽기/쓰기가 모두 가능하도록 접근권한을 지정하고 있다.
	//여기서 생성한 파일에 데이터를 저장한 다음 MMF 기반으로 데이터를 읽어 들인다.
	HANDLE hFile = CreateFile(_T("data.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		_tprintf(_T("Could not open file."));

	TCHAR fileData[] = _T("Best test string~ ^^");
	DWORD numOfByteWritten = 0;
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);

	//2단계:파일 연결 오브젝트 생성.
	//GENERIC_READ 속성을 지녔기 때문에 파일 연결 오브젝트에 PAGE_READONLY 속성을 지정할 수 있는 것.
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hMapFile == NULL)
		_tprintf(_T("Could not create map of file.\n"));

	//3단계:메모리에 연결.
	//가상 메모리로의 연결이 진행되고 그 결과로 얻게 된 포인터는 데이터를 참조하는 데 사용된다.
	TCHAR* pWrite = (TCHAR*)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	if (pWrite == NULL)
		_tprintf(_T("Could not map view of file.\n"));

	_tprintf(_T("String in file:%s\n"), pWrite);
	//MMF를 반환하는 과정을 보여준다.
	//UnmapViewOfFile 함수 호출을 통해서 할당되었던 가상 메모리와의 연결을 끓는 것이 우선.
	UnmapViewOfFile(pWrite);
	CloseHandle(hMapFile);

	CloseHandle(hFile);
	_tprintf(_T("End of process!\n"));
	return 0;
}