//���Ͻ��� Receiver
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot; //mailslot�ڵ�
	TCHAR messageBox[50];
	DWORD bytesRead; //number of bytes read

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//mailslot����
	hMailSlot = CreateMailslot(
		SLOT_NAME, //�� �ּҰ� ���Ͻ����� �ּҷ� ����.
		0,
		MAILSLOT_WAIT_FOREVER,
		&sa
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	//Message����
	_fputts(_T("********** Message **********\n"), stdout);
	while (1)
	{
		//ReadFile�� ���� ���Ͻ������� ���޵� �����͸� �о���̰� �ִ�.
		//���� ���Ϸκ��� �����͸� �о� ���� �� ���Ǵ� �Լ��̴�.
		if (!ReadFile(hMailSlot, messageBox, sizeof(TCHAR) * 50, &bytesRead, NULL))
		{
			_fputts(_T("Unable to read!"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}
		if (!_tcsncmp(messageBox, _T("exit"), 4))
		{
			_fputts(_T("Good Bye!"), stdout);
			break;
		}
		messageBox[bytesRead / sizeof(TCHAR)] = 0; //NULL ���� ����
		_fputts(messageBox, stdout);
	}
	CloseHandle(hMailSlot);
	return 0;
}
