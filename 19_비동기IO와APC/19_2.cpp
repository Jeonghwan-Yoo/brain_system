//���� ����� Ȯ�� I/O ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//���Ͽ� ������ ���ڿ��� �����ϰ� �ִ�.
//���� �� ���ڿ��� �����ϰ��� �� ���, �̿Ͱ��� ���·� ������ �����ϴ�.
//�׷��� ���ڿ��� �̾ �����ϸ� �ϳ��� ���ڿ��� �ν��Ѵ�.
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
	//������ �����ϴµ�, �Ӽ� FILE_FLAG_OVERLAPPED�� �����ϰ� �ִ�.
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, 
		CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault!\n"));
		return -1;
	}
	//�񵿱� ������� �⺻�� �Ǵ� OVERLAPPED ����ü ������ ���� �� �ʱ�ȭ�ϰ� �ִ�.
	//�̺�Ʈ ������Ʈ�� �ʿ���µ� �̺�Ʈ ������Ʈ�� �ڵ��� ������ ��ġ�� �̻��� �� ����.
	//�񵿱� ����� ������ �Ϸ�Ǹ�, WriteFileEx �Լ��� �ټ�° �������ڸ� ���� �������� �Ϸ��ƾ�� �ڵ����� ȣ��.
	//���� ��ø I/O���� �ʿ�� �ϴ� �̺�Ʈ ������Ʈ�� ���ʿ�������.
	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = (HANDLE)1234;
	//�Լ��� ȣ��Ǹ鼭 ����� ��� ������ ���۵ȴ�.
	//�׸��� �Ϸ�Ǹ� �ڵ����� �ټ� ��° ���ڷ� ���޵� �Լ� FileIOCompletionRoutine�� ȣ��.
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