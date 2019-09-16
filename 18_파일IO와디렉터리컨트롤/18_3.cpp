//파일 시간 정보 확인하는 예제
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("RealScaleViewer.exe"); //파일존재하는지 확인.

	TCHAR fileCreateTimeInfo[STRING_LEN];
	TCHAR fileAccessTimeInfo[STRING_LEN];
	TCHAR fileWriteTimeInfo[STRING_LEN];

	FILETIME ftCreate, ftAccess, ftWrite;

	SYSTEMTIME stCreateUTC, stCreateLocal;
	SYSTEMTIME stAccessUTC, stAccessLocal;
	SYSTEMTIME stWriteUTC, stWriteLocal;

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	//파일의 시간 정보 추출.
	//이 함수의 호출을 통해 변수 ftCreate, ftAccess, ftWrite에는 각각 파일의 생성, 접근, 갱신 시간이 UTC로 저장.
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
	{
		_tprintf(_T("GetFileTime function call fault!\n"));
		return FALSE;
	}

	//시간 정보 변환
	//첫번째 인자로 전달된 파일 시간의 정보를, SYSTEMTIME 구조체의 포맷으로 변경해서 적절히 채워주는 역할.
	//두번째 전달인자의 stCreateUTC은 SYSTEMTIME 구조체의 변수이다.
	FileTimeToSystemTime(&ftCreate, &stCreateUTC);
	//SystemTimeToTzSpecificLocalTime 함수는 UTC를 지역별, 국가별 시간대(Time Zone)로 변경하는 기능.
	//첫번째인자는 변경하고자 하는 시간대에 대한 정보이다. NULL이 전달되면 현재 시스템의 시간대 정보가 기준.
	//그러므로 한국 시간대 정보를 기준으로 변경이 이뤄짐.
	//두번째 전달인자는 변경할 대상이 되는 UTC 기반 시간 정보
	//세번째 전달인자는 변환된 시간 정보가 채워질 변수의 주소값이다.
	SystemTimeToTzSpecificLocalTime(NULL, &stCreateUTC, &stCreateLocal);

	FileTimeToSystemTime(&ftAccess, &stAccessUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stAccessUTC, &stAccessLocal);

	FileTimeToSystemTime(&ftWrite, &stWriteUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stWriteUTC, &stWriteLocal);

	_stprintf(fileCreateTimeInfo, _T("%02d/%02d/%d %02d:%02d"), stCreateLocal.wMonth,
		stCreateLocal.wDay, stCreateLocal.wYear, stCreateLocal.wHour, stCreateLocal.wMinute);

	_stprintf(fileAccessTimeInfo, _T("%02d/%02d/%d %02d:%02d"), stAccessLocal.wMonth,
		stAccessLocal.wDay, stCreateLocal.wYear, stCreateLocal.wHour, stCreateLocal.wMinute);

	_stprintf(fileWriteTimeInfo, _T("%02d/%02d/%d %02d:%02d"), stWriteLocal.wMonth,
		stWriteLocal.wDay, stWriteLocal.wYear, stWriteLocal.wHour, stWriteLocal.wMinute);

	_tprintf(_T("File created time : %s\n"), fileCreateTimeInfo);
	_tprintf(_T("File accessed time : %s\n"), fileAccessTimeInfo);
	_tprintf(_T("File written time : %s\n"), fileWriteTimeInfo);

	CloseHandle(hFile);
	return 0;
}