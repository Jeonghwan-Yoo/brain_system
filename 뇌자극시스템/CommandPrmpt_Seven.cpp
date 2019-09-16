//CommandPrmpt_Seven.cpp
//프로그램 설명 : 명령 프롬프트 7차
//명령어 : XCOPY-- > 디렉터리 단위 복사.

#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <Windows.h>
#include <TlHelp32.h>

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

void ListProcessInfo(void)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("CreateToolhelp32Snapshot error!\n"));
		return;
	}

	PROCESSENTRY32 pe32; //프로세스 정보 얻기 위한 구조체 변수
	//PROCESSENTRY32변수는 사용하기 전에 크기 정보 초기화한다.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	//첫번째 프로세스 정보 얻음
	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf(_T("Process32First error!\n"));
		CloseHandle(hProcessSnap);
		return;
	}

	do
	{
		//프로세스 이름, ID 정보 출력
		_tprintf(_T("%25s %5d\n"), pe32.szExeFile, pe32.th32ProcessID);
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
}

void KillProcess(void)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("CreateToolhelp32Snapshot (of processes)"));
		return;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf(_T("Process32First"));
		CloseHandle(hProcessSnap);
		return;
	}

	HANDLE hProcess;
	BOOL isKill = FALSE;
	do
	{
		//입력된 프로세스 이름과 비교한다.
		if (_tcscmp(pe32.szExeFile, cmdTokenList[1]) == 0)
		{
			//프로세스 ID를 핸들로 변환하는 과정
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

			if (hProcess != NULL)
			{
				//프로세스를 강제 종료시킨다.
				TerminateProcess(hProcess, -1);
				isKill = TRUE;
			}
			CloseHandle(hProcess);
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	if (isKill == FALSE)
		_tprintf(_T("Kill process fail, Try again!\n"));
}

void TypeTextFile(void)
{
	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	BOOL isRun;

	if (!_tcscmp(cmdTokenList[2], _T("|")))
	{
		//Create unnamed pipe
		HANDLE hReadPipe, hWritePipe;

		SECURITY_ATTRIBUTES pipeSA = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

		CreatePipe(&hReadPipe, &hWritePipe, &pipeSA, 0);

		//Process type을 위한 선언
		STARTUPINFO siType = { 0, };
		PROCESS_INFORMATION piType;
		siType.cb = sizeof(siType);

		siType.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
		siType.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		siType.hStdOutput = hWritePipe; //출력 리다이렉션!
		siType.dwFlags |= STARTF_USESTDHANDLES;

		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[1]);

		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL,
			&siType, &piType);

		CloseHandle(piType.hThread);
		CloseHandle(hWritePipe);

		//Process sort를 위한 선언
		STARTUPINFO siSort = { 0, };
		PROCESS_INFORMATION piSort;
		siSort.cb = sizeof(siSort);

		siSort.hStdInput = hReadPipe; //입력 리다이렉션!
		siSort.hStdError = GetStdHandle(STD_ERROR_HANDLE);
		siSort.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		siSort.dwFlags |= STARTF_USESTDHANDLES;

		isRun = CreateProcess(NULL, cmdTokenList[3], NULL, NULL, TRUE, 0, NULL, NULL,
			&siSort, &piSort);

		CloseHandle(piSort.hThread);
		CloseHandle(hReadPipe);

		WaitForSingleObject(piType.hProcess, INFINITE);
		WaitForSingleObject(piSort.hProcess, INFINITE);

		CloseHandle(piType.hProcess);
		CloseHandle(piSort.hProcess);
	}
	else
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[1]);

		STARTUPINFO si = { 0, };
		PROCESS_INFORMATION pi;
		si.cb = sizeof(si);

		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, INFINITE);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

//XCOPY 관련 함수 및 변수
int nCopyFiles = 0;
BOOL XCOPY(TCHAR* source, TCHAR* dest);

BOOL CopyDirectoryFiles(WIN32_FIND_DATA fileData, TCHAR* source, TCHAR* dest)
{
	BOOL isSuccess = NULL;

	if (!_tcscmp(fileData.cFileName, _T(".")) || !_tcscmp(fileData.cFileName, _T("..")))
	{
		//특별한 처리 필요없음.
		//현재 디렉터리를 의미하는 '.'과 상위 디렉터리를 의미하는 '..' 처리를 위한 코드.
	}
	else if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		TCHAR subSourceDir[MAX_PATH];
		TCHAR subDestDir[MAX_PATH];

		_stprintf(subSourceDir, _T("%s\\%s"), source, fileData.cFileName);
		_stprintf(subDestDir, _T("%s\\%s"), dest, fileData.cFileName);

		CreateDirectory(subDestDir, NULL);
		XCOPY(subSourceDir, subDestDir);
	}
	else
	{
		TCHAR sourceFile[MAX_PATH];
		TCHAR destFile[MAX_PATH];

		_tcscpy(sourceFile, source);
		_tcscpy(destFile, dest);

		_stprintf(sourceFile, _T("%s\\%s"), sourceFile, fileData.cFileName);
		_stprintf(destFile, _T("%s\\%s"), destFile, fileData.cFileName);

		isSuccess = CopyFile(sourceFile, destFile, FALSE);
		if (isSuccess == 0)
			return FALSE;

		nCopyFiles++;
	}
	return TRUE;
}

//Only Directory Copy!
BOOL XCOPY(TCHAR* source, TCHAR* dest)
{
	//Copy Recursively..
	WIN32_FIND_DATA fileData;
	BOOL isSuccess = NULL;

	TCHAR firstFFStr[MAX_PATH];
	_stprintf(firstFFStr, _T("%s\\%s"), source, _T("*"));

	HANDLE searchHandle = FindFirstFile(firstFFStr, &fileData);
	if (searchHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	else
		CopyDirectoryFiles(fileData, source, dest);

	while (1)
	{
		if (!FindNextFile(searchHandle, &fileData))
			break;
		else
		{
			isSuccess = CopyDirectoryFiles(fileData, source, dest);
			if (isSuccess == FALSE)
				break;
		}
	}
	FindClose(searchHandle);
	return TRUE;
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
	else if (!_tcscmp(cmdTokenList[0], _T("lp")))
	{
		ListProcessInfo();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("kp")))
	{
		if (tokenNum < 2)
		{
			_tprintf(_T("usage : kp <process name>\n"));
			return 0;
		}
		KillProcess();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("sort")))
	{
		if (!_tcscmp(cmdTokenList[1], _T(">")))
		{
			SECURITY_ATTRIBUTES fileSec = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE }; //상속가능해야 지정.

			HANDLE hFile = CreateFile(cmdTokenList[2], GENERIC_WRITE, FILE_SHARE_READ, &fileSec,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			si.hStdOutput = hFile;
			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
			si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
			si.dwFlags |= STARTF_USESTDHANDLES;

			isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

			WaitForSingleObject(pi.hProcess, INFINITE);

			CloseHandle(hFile);
		}
		else
		{
			isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

			WaitForSingleObject(pi.hProcess, INFINITE);
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("type")))
	{
		TypeTextFile();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("xcopy")))
	{
		XCOPY(cmdTokenList[1], cmdTokenList[2]);
		_tprintf(_T("%d개의 파일이 복사되었습니다.\n"), nCopyFiles);
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