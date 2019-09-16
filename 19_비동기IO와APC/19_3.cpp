//비동기 파일 I/O의 오류
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//파일에 순차적으로 저장하고자 하는 데이터들.
TCHAR strData1[] = _T("Nobody was farther off base than ~\n");
TCHAR strData2[] = _T("Royal Liverpool was outdated and not worthy of ~\n");
TCHAR strData3[] = _T("for the first time since 1967. The Hoylake track ~\n");

VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");

	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS,
		FILE_FLAG_OVERLAPPED, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault!\n"));
		return -1;
	}

	OVERLAPPED overlappedInstOne;
	memset(&overlappedInstOne, 0, sizeof(OVERLAPPED));
	overlappedInstOne.hEvent = (HANDLE)_T("First I/O");
	//각각 문자열을 완료루틴 기반의 확장 I/O 방식으로 저장하고 있다.
	//물론 WriteFileEx 함수 호출 이전에 필요한 모든 준비(OVERLAPPED 구조체 초기화)는 완료된 상태.
	WriteFileEx(hFile, strData1, sizeof(strData1), &overlappedInstOne, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstTwo;
	memset(&overlappedInstTwo, 0, sizeof(OVERLAPPED));
	overlappedInstTwo.hEvent = (HANDLE)_T("Second I/O");
	WriteFileEx(hFile, strData2, sizeof(strData2), &overlappedInstTwo, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstThree;
	memset(&overlappedInstThree, 0, sizeof(OVERLAPPED));
	overlappedInstThree.hEvent = (HANDLE)_T("Third I/O");
	WriteFileEx(hFile, strData3, sizeof(strData3), &overlappedInstThree, FileIOCompletionRoutine);

	SleepEx(INFINITE, TRUE);
	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransfered, LPOVERLAPPED overlapped)
{
	_tprintf(_T("**********File write result**********\n"));
	_tprintf(_T("Error code:%u\n"), errorCode);
	_tprintf(_T("Transfered bytes len:%u\n"), numOfBytesTransfered);
	_tprintf(_T("The other info:%s\n"), (TCHAR*)overlapped->hEvent);
}