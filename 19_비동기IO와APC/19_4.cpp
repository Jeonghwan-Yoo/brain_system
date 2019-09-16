//비동기 파일 I/O 정정
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

TCHAR strData1[] = _T("Nobody was farther off base than ~\n");
TCHAR strData2[] = _T("Royal Liverpool was outdated and not worthy of ~\n");
TCHAR strData3[] = _T("for the first time since 1967. The Hoylake track ~\n");

VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

OVERLAPPED overlappedFilePtr; //Default 0 초기화!

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
	//함수 호출에서 전송할 데이터 크기를 계산하고 있다.
	//이 값은 전역으로 선언된 OVERLAPPED 구조체 변수에 저장된다.
	WriteFileEx(hFile, strData1, sizeof(strData1), &overlappedInstOne, FileIOCompletionRoutine);
	//이렇게 저장된 값은 WriteFileEx 함수를 호출하기 전에 OVERLAPPED 구조체 변수 초기화 과정에서 사용된다.
	overlappedFilePtr.Offset += _tcslen(strData1) * sizeof(TCHAR);

	OVERLAPPED overlappedInstTwo;
	memset(&overlappedInstTwo, 0, sizeof(OVERLAPPED));
	//앞서 저장해 놓았던 파일의 위치 값으로 초기화하고 있다.
	//첫 번째 WriteFileEx 함수 호출로 인해 데이터가 쓰여질 위치의 뒤를 이어 데이터를 쓰겠다는 의미.
	overlappedInstTwo.Offset = overlappedFilePtr.Offset;
	overlappedInstTwo.hEvent = (HANDLE)_T("Second I/O");
	WriteFileEx(hFile, strData2, sizeof(strData2), &overlappedInstTwo, FileIOCompletionRoutine);
	//전송할 데이터 크기를 계산해서 저장하고 있다.
	//다음 번 WriteFileEx 함수 호출을 위한 것.
	overlappedFilePtr.Offset += _tcslen(strData2) * sizeof(TCHAR);

	OVERLAPPED overlappedInstThree;
	memset(&overlappedInstThree, 0, sizeof(OVERLAPPED));
	overlappedInstThree.Offset = overlappedFilePtr.Offset;
	overlappedInstThree.hEvent = (HANDLE)_T("Third I/O");
	WriteFileEx(hFile, strData3, sizeof(strData3), &overlappedInstThree, FileIOCompletionRoutine);
	overlappedFilePtr.Offset += _tcslen(strData3) * sizeof(TCHAR);

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