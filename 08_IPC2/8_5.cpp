//이름없는 파이프의 기본 원리 파악
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hReadPipe, hWritePipe; //pipe handle

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD bytesRead;

	//pipe 생성
	//이 파이프를 기반으로 문자열이 전송 및 수신된다.
	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

	//pipe의 한쪽 끝을 이용한 데이터 송신
	WriteFile(
		hWritePipe, sendString,
		lstrlen(sendString) * sizeof(TCHAR), &bytesWritten, NULL);
	_tprintf(_T("string send : %s\n"), sendString);

	//pipe의 다른 한쪽 끝을 이용한 데이터 수신
	ReadFile(
		hReadPipe, recvString,
		bytesWritten, &bytesRead, NULL);

	recvString[bytesRead / sizeof(TCHAR)] = 0;
	_tprintf(_T("string recv : %s\n"), recvString);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);

	return 0;
}