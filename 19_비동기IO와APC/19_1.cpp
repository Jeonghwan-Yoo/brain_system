//이름있는 파이프 서버 중첩 I/O 방식
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024
int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;
	while (1)
	{
		//파이프 생성 시 중첩 속성(혹은 넌플로킹모드 속성)을 부여하기 위해 FILE_FLAG_OVERLAPPED을
		//인자로 추가하고 있다.
		//그래서 생성되는 파이프는 넌블로킹 모드로 동작할 수 있다.
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUF_SIZE / 2, //출력 버퍼 사이즈
			BUF_SIZE / 2, //입력 버퍼 사이즈
			2000, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreateNamedPipe failed"));
			return -1;
		}

		BOOL isSuccess;
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
		if (isSuccess)
			CommToClient(hPipe);
		else
			CloseHandle(hPipe);
	}
	return 1;
}

int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];
	BOOL isSuccess;
	DWORD fileNameSize;

	isSuccess = ReadFile(hPipe, fileName, MAX_PATH * sizeof(TCHAR), &fileNameSize, NULL);
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
	//OVERLAPPED 구조체 변수를 선언하고 0으로 초기화한다.
	//0으로 초기화하지 않으면 결과를 예측할 수 없다.
	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	//이벤트 오브젝트를 생성하고, 핸들을 OVERLAPPED 구조체 변수에 저장하고 있다.
	overlappedInst.hEvent = CreateEvent(
		NULL, //default security attribute
		TRUE, //manual-reset event
		TRUE, //initial state = non-signaled
		NULL); //unnamed event object
	DWORD bytesWritten = 0, bytesRead = 0;
	DWORD bytesWrite = 0, bytesTransfer = 0;
	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);
		bytesWrite = bytesRead;
		//WriteFile 함수를 호출한다.
		//중첩 I/O를 위한 모든 조건이 충족되었으니, 호출된 함수는 이어서 바로 반환하게 된다.
		//데이터 전송이 완료되기도 전에 반환했기 때문에 세 번쨰 전달인자를 통해 얻은 정보(전송된 바이트 수)는
		//사실 의미가 없다.
		//그래서 NULL을 인자로 전달해도 된다.
		isSuccess = WriteFile(hPipe, dataBuf, bytesWrite, &bytesWritten, &overlappedInst);
		if (!isSuccess && GetLastError() != ERROR_IO_PENDING)
		{
			_tprintf(_T("Pipe wrtie message error!\n"));
			break;
		}
		//다른 작업을 할 수 있는 기회
		//이제 I/O연산이 끝났는지 확인해야 한다.
		//I/O연산이 끝나면 이벤트 오브젝트가 Signaled 상태로 변경되는 점을 활용한 것.
		WaitForSingleObject(overlappedInst.hEvent, INFINITE);
		GetOverlappedResult(hPipe, &overlappedInst, &bytesTransfer, FALSE);
		_tprintf(_T("Transferred data size:%u\n"), bytesTransfer);
	}
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}