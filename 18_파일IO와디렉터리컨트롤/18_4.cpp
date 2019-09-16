//파일 크기를 얻는 예제
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD high4ByteFileSize = 0;
	DWORD low4ByteFileSize = GetFileSize(hFile, &high4ByteFileSize);

	_tprintf(_T("High 4byte file size:%ubyte\n"), high4ByteFileSize);
	_tprintf(_T("Low 4byte file size:%ubyte\n"), low4ByteFileSize);

	LARGE_INTEGER fileSize;
	GetFileSizeEx(hFile, &fileSize);
	_tprintf(_T("Total file size:%ubyte\n"), fileSize.QuadPart);

	CloseHandle(hFile);
	return 0;
}