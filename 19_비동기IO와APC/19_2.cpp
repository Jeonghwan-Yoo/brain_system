//파일 기반의 확장 I/O 예제
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//파일에 저장할 문자열을 선언하고 있다.
//아주 긴 문자열을 선언하고자 할 경우, 이와같은 형태로 선언이 가능하다.
//그러면 문자열을 이어서 선언하면 하나의 문자열로 인식한다.
TCHAR strData[] =
_T("Nobody was farther off base than the pundits who said\n")
_T("Royal Liverpool was outdated and not worthy of hosing ~\n")
_T("for the first time since 1967. The Hoylake track ~\n")
_T("Here's the solution to modern golf technology -- firm,\n")
_T("fast fairways, penal bunkers, firm greens and, with any ~\n");

VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	//파일을 생성하는데, 속성 FILE_FLAG_OVERLAPPED을 지정하고 있다.
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, 
		CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault!\n"));
		return -1;
	}
	//비동기 입출력의 기본이 되는 OVERLAPPED 구조체 변수를 선언 및 초기화하고 있다.
	//이벤트 오브젝트가 필요없는데 이벤트 오브젝트의 핸들을 대입할 위치에 이상한 값 대입.
	//비동기 입출력 연산이 완료되면, WriteFileEx 함수의 다섯째 전달인자를 통해 설정해준 완료루틴이 자동으로 호출.
	//따라서 중첩 I/O에서 필요로 하던 이벤트 오브젝트가 불필요해졌다.
	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = (HANDLE)1234;
	//함수가 호출되면서 비공기 출력 연산이 시작된다.
	//그리고 완료되면 자동으로 다섯 번째 인자로 전달된 함수 FileIOCompletionRoutine이 호출.
	WriteFileEx(hFile, strData, sizeof(strData), &overlappedInst, FileIOCompletionRoutine);

	//SleepEx(INFINITE, TRUE);
	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransfered, LPOVERLAPPED overlapped)
{
	_tprintf(_T("**********File wrtie result**********\n"));
	_tprintf(_T("Error code:%u\n"), errorCode);
	_tprintf(_T("Transfered bytes len:%u\n"), numOfBytesTransfered);
	_tprintf(_T("The other info:%u\n"), (DWORD)overlapped->hEvent);
}