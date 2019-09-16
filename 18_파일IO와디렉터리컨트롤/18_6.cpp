//�ڵ��� �̿��ؼ� ���� ���� ������
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
	//������ �پ��� ������ ��� ���� GetFileInformationByHandle ȣ��.
	GetFileInformationByHandle(hFile, &fileInfo);
	//����ü ��� dwFileAttributes�� ������ ���� Ư�� ������ ����Ϸ� �Ѵ�.
	//�� ����� GetFileAttributes �Լ� ȣ���� ���� ��� �Ǵ� ������ ����.
	//���̰� �ִٸ� �̸��� �ƴ�, �ڵ��� ���ؼ� ��� �ȴٴ� ��.
	ShowAttributes(fileInfo.dwFileAttributes);

	//Additional information
	//������ ũ�� ������ ��� ���� ��� nFileSizeLow�� �����ؾ� �Ѵ�.
	//��뷮 ���� ũ�⸦ ��� ���ؼ��� ��� nFileSizeHigh�� ���Ҿ� �����ؾ� �Ѵ�.
	_tprintf(_T("File size:%u\n"), fileInfo.nFileSizeLow);
	_tprintf(_T("File created time:"));
	//���� ������ �����ð� �׸��� ������ ���� �� ����ð��� �����ϴ� ����� �����ش�.
	//�츮�� ������ �� �ִ� �ð���� �����Ϸ��� ShowFileTime �Լ��� ȣ���ؾ� �Ѵ�.
	ShowFileTime(fileInfo.ftCreationTime);

	_tprintf(_T("File accessed time:"));
	ShowFileTime(fileInfo.ftLastAccessTime);

	_tprintf(_T("File written time:"));
	ShowFileTime(fileInfo.ftLastWriteTime);

	return 0;
}

void ShowAttributes(DWORD attrib)
{
	//FILE_ATTRIBUTE_NORMAL�� �ٸ� Ư���� ������ �ǹ��ϹǷ� �̾ �ٷ� �Լ��� ���� ���´�.
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