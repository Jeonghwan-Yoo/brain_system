//�ڵ��� ��� Ȯ�ο� ����. �θ� ���μ���
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot;
	TCHAR message[50]; 
	DWORD bytesWritten; //number of bytes write

	//�ڵ��� ��� ���θ� Y�� �α� ���� �ڵ�.
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//������ ���ҽ��� �ڵ� ������ �����ϰ� �ִ�.
	hMailSlot = CreateFile(
		SLOT_NAME, //���Ͻ����� �̸�(�ּ�)
		GENERIC_WRITE, //���Ǵ� �뵵
		FILE_SHARE_READ,
		&sa,
		OPEN_EXISTING, //���� ���
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	_tprintf(_T("Inheritable Handle : %d\n"), hMailSlot);
	//������ �����Ѵ�.
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%d"), hMailSlot);
	fclose(file);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSender2_2.exe");

	//�ڽ� ���μ����� �����Ѵ�.
	//5��° �������ڴ� TRUE�̰� �̴� �ڽ����μ������� �θ� ���μ����� �ڵ� ���̺������� ����ϰڴ�.
	//�ᱹ �ڽ� ���μ����� ������ ������ ���ҽ��� �ڵ������� ��ӹ޴´�.
	//���� �ּҰ� \\.\mailslot\mailbot�� ���ν��Կ� �����͸� ������ �� �ִ�.
	CreateProcess(NULL, command, NULL, NULL,
		TRUE, //�ڵ����̺� ��� ����!
		CREATE_NEW_CONSOLE, //�ڽ� ���μ������� ���ο� �ܼ��� �Ҵ��ϰڴٴ� �ǹ�.
		NULL, NULL, &si, &pi);

	while (1)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		//WriteFile�Լ��� �̿��� ���Ͻ������� �����͸� �����ϰ� �ִ�.
		if (!WriteFile(hMailSlot, message, _tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL))
		{
			_fputts(_T("Unable to write!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}
		if (!_tcscmp(message, _T("exit")))
		{
			_fputts(_T("Good Bye!"), stdout);
			break;
		}
	}
	CloseHandle(hMailSlot);
	return 0;
}