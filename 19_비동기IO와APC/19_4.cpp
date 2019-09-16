//�񵿱� ���� I/O ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

TCHAR strData1[] = _T("Nobody was farther off base than ~\n");
TCHAR strData2[] = _T("Royal Liverpool was outdated and not worthy of ~\n");
TCHAR strData3[] = _T("for the first time since 1967. The Hoylake track ~\n");

VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

OVERLAPPED overlappedFilePtr; //Default 0 �ʱ�ȭ!

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
	//�Լ� ȣ�⿡�� ������ ������ ũ�⸦ ����ϰ� �ִ�.
	//�� ���� �������� ����� OVERLAPPED ����ü ������ ����ȴ�.
	WriteFileEx(hFile, strData1, sizeof(strData1), &overlappedInstOne, FileIOCompletionRoutine);
	//�̷��� ����� ���� WriteFileEx �Լ��� ȣ���ϱ� ���� OVERLAPPED ����ü ���� �ʱ�ȭ �������� ���ȴ�.
	overlappedFilePtr.Offset += _tcslen(strData1) * sizeof(TCHAR);

	OVERLAPPED overlappedInstTwo;
	memset(&overlappedInstTwo, 0, sizeof(OVERLAPPED));
	//�ռ� ������ ���Ҵ� ������ ��ġ ������ �ʱ�ȭ�ϰ� �ִ�.
	//ù ��° WriteFileEx �Լ� ȣ��� ���� �����Ͱ� ������ ��ġ�� �ڸ� �̾� �����͸� ���ڴٴ� �ǹ�.
	overlappedInstTwo.Offset = overlappedFilePtr.Offset;
	overlappedInstTwo.hEvent = (HANDLE)_T("Second I/O");
	WriteFileEx(hFile, strData2, sizeof(strData2), &overlappedInstTwo, FileIOCompletionRoutine);
	//������ ������ ũ�⸦ ����ؼ� �����ϰ� �ִ�.
	//���� �� WriteFileEx �Լ� ȣ���� ���� ��.
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