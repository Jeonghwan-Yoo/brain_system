#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(void)
{
	//������ �����ϴ� �Լ��̴�.
	//�������� �ʴ� ������ ������ ������ �������� �Լ��� ȣ���� ���з� ���ư� ���̴�.
	//CreateFile�Լ��� ȣ�� ������ ��� INVALID_HANDLE_VALUE�� ��ȯ�Ѵ�.
	HANDLE hFile = CreateFile(_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL); //Windows system �Լ�
	if (hFile == INVALID_HANDLE_VALUE)
	{
		//The system cannot find the file specified.
		_tprintf(_T("error code : %d\n"), GetLastError());
		return 0;
	}
	return 0;
}