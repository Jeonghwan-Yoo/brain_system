//이름있는 파이프 클라이언트
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	//파이프의 이름은 "\\servername\pipe\pipename"
	//클라이언트는 서버 이름을 통해서 원격에 존재하는 컴퓨터의 파이프에 연결을 한다.
	//그래서 클라이언트 코드의 파이프 이름 구성에는 서버 이름이 필요하다.
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	
	while (1)
	{
		//파일을 생성하거나 개방하는 Windows 시스템 함수이다.
		//클라이언트 영역에서 서버 측 파이프로의 연결 요청 기능도 지닌다.
		//첫번째 전달인자를 통해 연결 대상인 파이프 이름을 지정한다.
		//두번째 전달인자를 통해 읽기, 쓰기가 동시에 가능하도록 모드를 설정.
		//전달된 값은 파일 생성 시 읽기, 쓰기 모드를 설정할 때 사용되는 상수들이다.
		hPipe = CreateFile(
			pipeName, //연결할 파이프 이름
			GENERIC_READ | GENERIC_WRITE, //읽기, 쓰기 모드 동시 지정
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		//연결되면 while루프를 빠져나가서 다음 작업을 진행한다.
		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		//ERROR_PIPE_BUSY는 연결 요청이 Pending(여분의 파이프가 없어 기다리는)상태에 놓여있음을 의미한다.
		//ERROR_PIPE_BUSY가 반환되면 잠시 후 다시 시도해 봐야 한다.
		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}

		//연결 가능한 상태가 되면 TRUE를 반환하겠다.
		//연결 가능한 상태가 될 때까지 블로킹 상태에 두겠다.
		if (!WaitNamedPipe(pipeName, 20000))
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}
	}
	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT; //메시지 기반으로 모드 변경
	//파이프와의 연결 속성을 변경시킨다.
	//파이프와 연결 시 파일 관련 함수인 CreateFile를 사용하다 보니 설정에 필요한 정보를 완전히 반영할 수 없다.
	//그래서 이 함수를 통해 파이프와의 연결 속성을 원하는 대로 변경시키는 추가적인 작업.
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe, //서버 파이프와 연결된 핸들
		&pipeMode, //변경할 모드 정보.
		NULL,
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("SetNamedPipeHandleState failed"));
		return 0;
	}

	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;

	//실제적인 통신이 시작된다.
	//수신하고자 하는 문자열 데이터를 담고 있는 파일 이름을 전달한다.
	isSuccess = WriteFile(
		hPipe, //서버 파이프와 연결된 핸들
		fileName, //전송할 메시지
		(_tcslen(fileName) + 1) * sizeof(TCHAR), //메시지 길이
		&bytesWritten, //전송된 바이트 수
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("WriteFile failed"));
		return 0;
	}

	DWORD bytesRead = 0;
	while (1)
	{
		//전달된 데이터를 읽는다.
		isSuccess = ReadFile(
			hPipe, //서버 파이프와 연결된 핸들
			readDataBuf, //데이터 수신할 버퍼
			BUF_SIZE * sizeof(TCHAR), //버퍼 사이즈
			&bytesRead, //수신한 바이트 수
			NULL);
		//서버에서 데이터를 완전히 전송하고 파이프 연결을 끊을 경우, 프로그램을 종료하게 된다.
		//서버가 전송한 문자열의 길이가 ReadFile함수에서 지정한 버퍼의 길이를 초과할 경우, 한 번에
		//전체 문자열을 읽어 들일 수 없기 때문에 FALSE를 반환하면서, GetLastError함수 호출의 결과가
		//ERROR_MORE_DATA가 된다.
		//이런 경우에는 루프를 빠져나가지 않고 나머지 부분을 읽기 위해 고려하는 부분.
		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;
		
		readDataBuf[bytesRead] = 0;
		_tprintf(_T("%s\n"), readDataBuf);
	}
	CloseHandle(hPipe);
	return 0;
}