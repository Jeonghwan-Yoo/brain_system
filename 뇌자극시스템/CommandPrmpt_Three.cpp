//명령 프롬프트 3차 start명령어(echo cmd 추가)
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <Windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다.\n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize(void);
int CmdProcessing(int);
TCHAR* StrLower(TCHAR*);

int _tmain(int argc, TCHAR* argv[])
{
	//한글 입력을 가능케 하기 위해
	_tsetlocale(LC_ALL, _T("Korean"));

	//매개변수 전달인자가 있는 경우. start명령어를 위한 처리.
	if (argc > 2)
	{
		for (int i = 1;i < argc;i++)
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		CmdProcessing(argc - 1);
	}

	DWORD isExit = NULL;
	while (1)
	{
		int tokenNum = CmdReadTokenize();
		if (tokenNum == 0) //Enter입력 처리를 위한 부분
			continue;

		isExit = CmdProcessing(tokenNum);
		if (isExit == TRUE)
		{
			_fputts(_T("명령어 처리를 종료합니다.\n"), stdout);
			break;
		}
	}
	return 0;
}

//사용자의 선택을 입력받는 기능을 CmdReadTokenize함수로 분리시켰다.
//명령어가 main함수를 통해 전달되는 경우에는 사용자 입력이 불필요하기 때문.
int CmdReadTokenize(void)
{
	TCHAR* token;

	_fputts(_T("Best command promt>>"), stdout);
	_getts_s(cmdString);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}

int CmdProcessing(int tokenNum)
{
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	si.cb = sizeof(si);
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start")))
	{
		//start echo test good이라는 문자열이 입력되었다고 가정해보자.
		//실행파일 이름이 CmdProject.exe라고 가정해보자.
		if (tokenNum > 1)
		{
			//start를 제외한 나머지 문자열을 재구성한다.
			for (int i = 1;i < tokenNum;i++)
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CmdProject.exe"), optString);
		}
		else //start만 입력하는 경우 
		{
			_stprintf(cmdStringWithOptions, _T("%s"), _T("CmdProject.exe"));
		}
		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, CREATE_NEW_CONSOLE,
			NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo")))
	{
		//입력된 문자열을 그대로 출력하는 echo명령어
		for (int i = 1;i < tokenNum;i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_tprintf(_T("echo mesasge : %s\n"), optString);
	}
	else
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);

		//Check Point 1 : 문자열 처리를 위한 for문
		for (int i = 1;i < tokenNum;i++)
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (isRun == FALSE)
			_tprintf(ERROR_CMD, cmdTokenList[0]);
	}
	return 0;
}

//문자열의 내에 존재하는 모든 대문자를 소문자로 변경한다. 변경된 문자열의 포인터를 반환한다.
TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	while (*pStr)
	{
		if (_istupper(*pStr))
		{
			*pStr = _totlower(*pStr);
		}
		pStr++;
	}
	return ret;
}//명령 프롬프트 3차 start명령어(echo cmd 추가)
#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <Windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다.\n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize(void);
int CmdProcessing(int);
TCHAR* StrLower(TCHAR*);

int main(int argc, TCHAR* argv[])
{
	//한글 입력을 가능케 하기 위해
	_tsetlocale(LC_ALL, _T("Korean"));

	//매개변수 전달인자가 있는 경우. start명령어를 위한 처리.
	if (argc > 2)
	{
		for (int i = 1;i < argc;i++)
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		CmdProcessing(argc - 1);
	}

	DWORD isExit = NULL;
	while (1)
	{
		int tokenNum = CmdReadTokenize();
		if (tokenNum == 0) //Enter입력 처리를 위한 부분
			continue;

		isExit = CmdProcessing(tokenNum);
		if (isExit == TRUE)
		{
			_fputts(_T("명령어 처리를 종료합니다.\n"), stdout);
			break;
		}
	}
	return 0;
}

//사용자의 선택을 입력받는 기능을 CmdReadTokenize함수로 분리시켰다.
//명령어가 main함수를 통해 전달되는 경우에는 사용자 입력이 불필요하기 때문.
int CmdReadTokenize(void)
{
	TCHAR* token;

	_fputts(_T("Best command promt>>"), stdout);
	_getts_s(cmdString);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}

int CmdProcessing(int tokenNum)
{
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	si.cb = sizeof(si);
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start")))
	{
		//start echo test good이라는 문자열이 입력되었다고 가정해보자.
		//실행파일 이름이 CmdProject.exe라고 가정해보자.
		if (tokenNum > 1)
		{
			//start를 제외한 나머지 문자열을 재구성한다.
			for (int i = 1;i < tokenNum;i++)
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CmdProject.exe"), optString);
		}
		else //start만 입력하는 경우 
		{
			_stprintf(cmdStringWithOptions, _T("%s"), _T("CmdProject.exe"));
		}
		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, CREATE_NEW_CONSOLE,
			NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo")))
	{
		//입력된 문자열을 그대로 출력하는 echo명령어
		for (int i = 1;i < tokenNum;i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_tprintf(_T("echo mesasge : %s\n"), optString);
	}
	else
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);

		//Check Point 1 : 문자열 처리를 위한 for문
		for (int i = 1;i < tokenNum;i++)
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (isRun == FALSE)
			_tprintf(ERROR_CMD, cmdTokenList[0]);
	}
	return 0;
}

//문자열의 내에 존재하는 모든 대문자를 소문자로 변경한다. 변경된 문자열의 포인터를 반환한다.
TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	while (*pStr)
	{
		if (_istupper(*pStr))
		{
			*pStr = _totlower(*pStr);
		}
		pStr++;
	}
	return ret;
}