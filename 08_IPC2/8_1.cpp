//핸들의 상속 확인용 예제. 부모 프로세스
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot;
	TCHAR message[50]; 
	DWORD bytesWritten; //number of bytes write

	//핸들의 상속 여부를 Y로 두기 위한 코드.
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	//생성한 리소스의 핸들 정보를 저장하고 있다.
	hMailSlot = CreateFile(
		SLOT_NAME, //메일슬롯의 이름(주소)
		GENERIC_WRITE, //사용되는 용도
		FILE_SHARE_READ,
		&sa,
		OPEN_EXISTING, //생성 방식
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	if (hMailSlot == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot!\n"), stdout);
		return 1;
	}

	_tprintf(_T("Inheritable Handle : %d\n"), hMailSlot);
	//파일을 생성한다.
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%d"), hMailSlot);
	fclose(file);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSender2_2.exe");

	//자식 프로세스를 생성한다.
	//5번째 전달인자는 TRUE이고 이는 자식프로세스에게 부모 프로세스의 핸들 테이블정보를 상속하겠다.
	//결국 자식 프로세스는 위에서 생성한 리소스의 핸들정보를 상속받는다.
	//따라서 주소가 \\.\mailslot\mailbot인 메인슬롯에 데이터를 전송할 수 있다.
	CreateProcess(NULL, command, NULL, NULL,
		TRUE, //핸들테이블 상속 설정!
		CREATE_NEW_CONSOLE, //자식 프로세스에게 새로운 콘솔을 할당하겠다는 의미.
		NULL, NULL, &si, &pi);

	while (1)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		//WriteFile함수를 이용해 메일슬롯으로 데이터를 전송하고 있다.
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