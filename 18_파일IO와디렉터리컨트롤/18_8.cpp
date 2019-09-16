//���� �������� �̵� 32��Ʈ ����
//abcd.dat��� �̸��� ������ ������ ���� ���ĺ��� �Է��Ѵ�.
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100
TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	HANDLE hFile;
	DWORD numOfByteWritten = 0;
	DWORD dwPtr = 0;

	//file write
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	CloseHandle(hFile);

	//file read
	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	//���� �����͸� �� ������ �̵�
	//SetFilePointer �Լ��� ȣ���� ���� ���� ������ ��ġ�� �� ������ �̵��� ������, ���� 4���� ��ġ��ŭ
	//�ڷ� �ǳ� �ٰ� �ִ�.
	//sizeof(TCHAR)�� 4���� ��ġ�� �����Ͽ����Ƿ� �����ڵ� ����̶�� 8����Ʈ�� �ǳʶٰ� �ȴ�.
	//����° �������ڴ� NULL�� 4GB �̻��� �Ǵ� ���Ͽ� ���ؼ��� �Ű澲�� �ʰ� �������� �ʴ´�.
	dwPtr = SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);
	//SetFilePointer �Լ��� ��ȯ���� INVALID_SET_FILE_POINTER��� ������ �߻��Ͽ����� �ǹ�.
	//#define INVALID_SET_FILE_PIONTER ((DWORD)-1)
	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		_tprintf(_T("SetFilePointer Error\n"));
		return -1;
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	//���� �����͸� �� �ڷ� �̵�
	//���� ������ ��ġ�� �� �ڷ� �̵��� ��������, ���� 4���� ��ġ��ŭ�� ������ �̵���Ű�� �ִ�.
	//-�� �پ������Ƿ� ������ �̵��ϰ� �ȴ�.
	dwPtr = SetFilePointer(hFile, -(sizeof(TCHAR) * 4), NULL, FILE_END);
	if (dwPtr == INVALID_SET_FILE_POINTER) //Test for failure
	{
		_tprintf(_T("SetFilePointer Error\n"));
		return -1;
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	CloseHandle(hFile);
	return 0;
}