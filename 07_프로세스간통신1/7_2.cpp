//메일슬롯 Receiver
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot; //mailslot핸들
	TCHAR messageBox[50];
	DWORD bytesRead; //number of bytes read

	//mailslot생성
	hMailSlot = CreateMailslot(
		SLOT_NAME, //이 주소가 메일슬롯의 주소로 결정.
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL
	);
	
	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	//Message수신
	_fputts(_T("********** Message **********\n"), stdout);
	while (1)
	{
		//ReadFile을 통해 메일슬롯으로 전달된 데이터를 읽어들이고 있다.
		//원래 파일로부터 데이터를 읽어 들일 때 사용되는 함수이다.
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
		messageBox[bytesRead / sizeof(TCHAR)] = 0; //NULL 문자 삽입
		_fputts(messageBox, stdout);
	}
	CloseHandle(hMailSlot);
	return 0;
}
