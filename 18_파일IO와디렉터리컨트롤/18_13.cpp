#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePath[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	_tprintf(_T("Insert name of the file to find:"));
	//ã���� �ϴ� ������ �̸��� �Է¹޾�
	_tscanf(_T("%s"), fileName);
	//��θ� ã�� ���� SearchPath �Լ��� ȣ���Ѵ�.
	//ù ��° ���ڰ� NULL�̾ Ư�� ���͸� ��ġ�� �������� ���� ��.
	//���� ���α׷��� �ε�� ���͸��� �������� ȯ�溯�� PATH�� ��ϵ� ���͸������ ���������� �˻�.
	result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePart);
	if (result == 0)
	{
		_tprintf(_T("File not found!\n"));
	}
	else
	{
		_tprintf(_T("File path:%s\n"), bufFilePath);
		_tprintf(_T("File name only:%s\n"), lpFilePart);
	}
	return 0;
}