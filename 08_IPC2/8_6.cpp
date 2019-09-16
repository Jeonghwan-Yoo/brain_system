//이름있는 파이프 서버
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024
int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	//여러 클라이언트와 통신 가능하지만 한 순간에 한 클라이언트와만 가능!
	//이름있는 파이프를 생성하고, 클라이언트 연결 요청을 수락하는 구조의 반복.
	while (1)
	{
		//양방향으로 읽고 쓰는 것이 가능하되 메시지 기반으로 동작한다.
		//입력 버퍼와 출력 버퍼의 사이즈는 BUF_SIZE이고, 티폴트 클라이언트 타임아웃은 20초로 설정.
		hPipe = CreateNamedPipe(
			pipeName, //파이프 이름
			PIPE_ACCESS_DUPLEX, //읽기, 쓰기 모드 지정.
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //메시지 기반
			PIPE_UNLIMITED_INSTANCES, //최대 파이프 개수. 생성 가능한 파이프의 개수.
			BUF_SIZE, //출력 버퍼 사이즈
			BUF_SIZE, //입력 버퍼 사이즈
			20000, //클라이언트 타임아웃
			NULL //디폴트 보안 속성
		);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreatePipe failed"));
			return -1;
		}

		BOOL isSuccess = 0;
		//클라이언트의 연결 요청을 수락하는 역할을 한다.
		//이미 요청이 들어와 있는 상태면 바로 반환되어 그 이후 작업을 진행하지만 
		//요청이 없는 상태라면 연결 요청이 들어올 때까지 블로킹된다.
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess)
			CommToClient(hPipe);
		else
			CloseHandle(hPipe);
	}
	return 1;
}

//클라이언트와 연결이 성립되면, 이때 사용된 파이프 핸들을 전달하면서 이 함수가 호출된다.
//데이터를 수신하는 함수(ReadFile), 데이터를 전송하는 함수(WriteFile)
//파이프의 연결을 종료하는 함수(FlushFileBuffers, DisconnedtNamedPipe)
int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile(
		hPipe, //파이프 핸들
		fileName, //read 버퍼 지정
		MAX_PATH * sizeof(TCHAR), //read 버퍼 사이즈
		&fileNameSize, //수신한 데이터 크기
		NULL
	);

	if (!isSuccess || fileNameSize == 0)
	{
		_tprintf(_T("Pipe read message error!\n"));
		return -1;
	}

	FILE* filePtr = _tfopen(fileName, _T("r"));
	if (filePtr == NULL)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile(
			hPipe, //파이프 핸들
			dataBuf, //전송할 데이터 버퍼
			bytesRead, //전송할 데이터 크기
			&bytesWritten, //전송된 데이터 크기
			NULL);
		
		if (bytesRead != bytesWritten)
		{
			_tprintf(_T("Pipe write message error!\n"));
			break;
		}
	}

	//파이프 연결을 종료하기 위해서 사용되는 함수들.
	//출력 버퍼를 비우는 역할로 목적지로의 전송을 의미.
	//기본적으로 Windows는 파일 시스템을 포함한 대부분의 입출력 상황에서 버퍼링을 한다.
	//따라서 이미 전송되었다고 생각되는 데이터들이 목적지의 상황에 따라 아직까지 시스템 메모리에 남아 있을 수 있다.
	FlushFileBuffers(hPipe); 
	//클라이언트가 에러 메시지를 받을 수 있도록 도와준다.
	//파이프 연결이 끊기고 나면, 클라이언트는 파이프 접근 시 에러가 발생한다.
	//따라서 클라이언트 역시 이에 따른 적절한 처리가 가능해진다.
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}