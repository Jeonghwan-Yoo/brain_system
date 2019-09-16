//핸들을 이용해서 파일 정보 얻어오기
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

void ShowAttributes(DWORD attrib);
void ShowFileTime(FILETIME t);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	BY_HANDLE_FILE_INFORMATION fileInfo;

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}
	//파일의 다양한 정보를 얻기 위해 GetFileInformationByHandle 호출.
	GetFileInformationByHandle(hFile, &fileInfo);
	//구조체 멤버 dwFileAttributes을 참조해 파일 특성 정보를 출력하려 한다.
	//이 멤버는 GetFileAttributes 함수 호출을 통해 얻게 되는 정보와 동일.
	//차이가 있다면 이름이 아닌, 핸들을 통해서 얻게 된다는 점.
	ShowAttributes(fileInfo.dwFileAttributes);

	//Additional information
	//파일의 크기 정보를 얻기 위해 멤버 nFileSizeLow에 접근해야 한다.
	//대용량 파일 크기를 얻기 위해서는 멤버 nFileSizeHigh도 더불어 참조해야 한다.
	_tprintf(_T("File size:%u\n"), fileInfo.nFileSizeLow);
	_tprintf(_T("File created time:"));
	//각각 파일의 생성시간 그리고 마지막 접근 및 변경시간을 참조하는 방법을 보여준다.
	//우리가 이해할 수 있는 시간대로 변경하려면 ShowFileTime 함수를 호출해야 한다.
	ShowFileTime(fileInfo.ftCreationTime);

	_tprintf(_T("File accessed time:"));
	ShowFileTime(fileInfo.ftLastAccessTime);

	_tprintf(_T("File written time:"));
	ShowFileTime(fileInfo.ftLastWriteTime);

	return 0;
}

void ShowAttributes(DWORD attrib)
{
	//FILE_ATTRIBUTE_NORMAL은 다른 특성이 없음을 의미하므로 이어서 바로 함수를 빠져 나온다.
	if (attrib & FILE_ATTRIBUTE_NORMAL)
	{
		_tprintf(_T("Normal\n"));
	}
	else
	{
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(_T("Read Only\n"));

		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(_T("Hidden\n"));
	}
	_tprintf(_T("\n"));
}

void ShowFileTime(FILETIME t)
{
	TCHAR fileTimeInfo[STRING_LEN];
	FILETIME ft = t;
	SYSTEMTIME stUTC, stLocal;

	FileTimeToSystemTime(&ft, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	_stprintf(fileTimeInfo, _T("%02d/%02d/%d %02d:%02d"), stLocal.wMonth, stLocal.wDay,
		stLocal.wYear, stLocal.wHour, stLocal.wMinute);

	_tprintf(_T("[%s]\n"), fileTimeInfo);
}