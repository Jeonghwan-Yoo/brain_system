//핸들의 상속 확인용 예제. 자식 프로세스
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot;
	TCHAR message[50];
	DWORD bytesWritten; //number of bytes write

	//핸들을 얻는 코드
	//파일을 열어서 부모 프로세스가 실행 중에 저장해 놓은 핸들 정보를 참조하고 있다.
	//이제 이 핸들을 이용해 부모 프로세스와 동일한 형태로 메일슬롯에 메시지를 전달할 수 있게 된다.
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	_ftscanf(file, _T("%d"), &hMailSlot);
	fclose(file);
	_tprintf(_T("Inheritable Handle : %d\n"), hMailSlot);

	while (1)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		if (!WriteFile(hMailSlot, message, _tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL))
		{
			_fputts(_T("Unable to write!"), stdout);
			_gettchar();
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