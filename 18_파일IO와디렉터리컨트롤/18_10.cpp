//���͸��� ������ �Ҹ�
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//���Ǻ� �����Ϲ��� ���� �����Ѵ� 0���� �� ��� ����.
#define CREATE_DIRECTORY 0

int _tmain(int argc, TCHAR* argv[])
{
	//���� ������� ���͸� ������ �������� ���͸� ������ �����ֱ� ���� ������ ��θ� ���Ƿ� ����.
	//������ ������ ������ ���� �� ������ ���͸��� �������ش�.

	TCHAR dirReletivePath[] = _T("GoodDirectoryOne");
	TCHAR dirFullPath[] = _T("D:\\GoodDirectoryTwo");

#if CREATE_DIRECTORY
	CreateDirectory(dirReletivePath, NULL);
	CreateDirectory(dirFullPath, NULL);
#else
	RemoveDirectory(dirReletivePath);
	RemoveDirectory(dirFullPath);
#endif
	return 0;
}