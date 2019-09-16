//��뷮 ������ ���� ������ �̵�
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

	LONG lDistanceLow = sizeof(TCHAR) * 4;
	LONG lDistanceHigh = 0;

	//file write
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);
	CloseHandle(hFile);

	//file read
	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	//���� �����͸� �� ������ �̵�
	//4GB �̻��� ��뷮 ���� ��ġ ������ ǥ���Ϸ��� 8����Ʈ�� �ʿ��ѵ�, SetFilePointer �Լ��� ��ȯ���̰�,
	//�Ű����� �ڷ����̰� ��� �͵� 8B�� ǥ���� �� �ִ� ���� ����.
	//��� 4����Ʈ �ڷ������� ����Ǿ� �ְ� ���� 4����Ʈ�� ���� 4����Ʈ�� ������ ǥ���ϵ��� �Լ��� ����.
	//�̰��� �� �Լ��� ������ ���ŷӰ��ϴ� ������, ���� ������ �̵��̶�� �۾��� ���ŷӰ� �Ѵ�.
	//�� ��°, �� ��° ���޵Ǵ� ���ڰ� ���� ���� 4B�� ���� 4B ������ ǥ���Ѵ�. (������ 0���� �ʱ�ȭ�ߴ�).
	//�׷��� ���޵Ǵ� ���� Ÿ���� �ٸ���, �� ��°�� ���� 4B������ �ܼ��� �����ϴ� �뵵(Call By Value).
	//�׷��� �� ��° �������ڴ� ������ ȹ���� ���ؼ��� ���Ǳ� ������ �����͸� ���ڷ� ����(Call By Pointer).
	//64��Ʈ ��� �ڵ� ���������� ȣ�� ���� �� 64��Ʈ ��ġ ������ ��ȯ����� �ϴµ� ��ȯ Ÿ���� 
	//4B �ڷ����̶� �Ұ����ϴ�.
	//�׷��� SetFilePointer �Լ� ȣ�� ���� �� ���� �������� ���� 4����Ʈ ������ ��ȯ���� ���ؼ�,
	//���� 4����Ʈ ������ SetFilePointer �Լ��� �� ��° �������ڰ� ����Ű�� ������ ���� ��ȯ�ϱ�� ����.
	dwPtr = SetFilePointer(hFile, lDistanceLow, &lDistanceHigh, FILE_BEGIN);
	//�Լ��� ��ȯ���� ���� �����˻縦 �ϰ� �ִ�.
	if ((dwPtr == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR))
	{
		_tprintf(_T("SetFilePointer Error\n"));
		return -1;
	}
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	CloseHandle(hFile);
	return 0;
}