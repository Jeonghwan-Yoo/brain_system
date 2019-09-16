#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void TYPE(TCHAR* fileName) //FOR REDIRECTION.
{
	TCHAR StringBuff[1024]; //문자열 길이 임의로 제한

	FILE* filePtr = _tfopen(fileName, _T("rt"));
	while (_fgetts(StringBuff, 1024, filePtr))
		_fputts(StringBuff, stdout);
}

int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2)
		return -1;

	TYPE(argv[1]);

	return 0;
}