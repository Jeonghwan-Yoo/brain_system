#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h> //_beginthreadex, _endthreadex

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID;

	//main�����尡 �ϴ���. ����ȭ�� �̺�Ʈ ������Ʈ�� �����Ѵ�. ���� ���� ���� �����ϰ� �ִ�.
	hEvent = CreateEvent( //event object ����
		NULL, //��ӺҰ�
		TRUE, //manual-reset mode�� ����
		FALSE, //non-signaled ���·� ����
		NULL //�̸����� event
	);
	if (hEvent == NULL)
	{
		_fputts(_T("Event object creation error\n"), stdout);
		return -1;
	}

	//OutputThreadFunction�� main���� �ϴ� �����带 �����ϰ� �ִ�.
	//�������ڸ��� �ռ� ������ �̺�Ʈ ������Ʈ�� Signaled ���°� �� ���� ��ٸ���.
	hThread = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread == 0)
	{
		_fputts(_T("Thread creation error\n"), stdout);
		return -1;
	}
	_fputts(_T("Insert string:"), stdout);
	//main������� �ַܼκ��� ���ڿ��� �Է¹��� �Ŀ� �̺�Ʈ ������Ʈ�� Signaled ���·� �����Ų��.
	//���ڿ��� �Է¹ް� �� ����,
	_fgetts(string, 30, stdin);

	SetEvent(hEvent); //event�� state�� signaled���·� ����

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent); //event ������Ʈ �Ҹ�
	CloseHandle(hThread);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	//event�� signaled ���°� �Ǳ⸦ ��ٸ���.
	//�̺�Ʈ ������Ʈ�� Signaled ���°� �Ǿ����Ƿ�, ���ŷ�� ������� �Լ��� ���� ���ͼ� ������ �κ�(�ܼ����)��
	//�����Ѵ�. �������¸��� �̺�Ʈ�� �����Ͽ����Ƿ� WaitForSingleObject�� �������� �������� Signaled ����.
	//���� �̺�Ʈ ������Ʈ�� Non-Signaled ���·� ������ �ʿ䰡 ���� �����ϴ� �ڵ�� ����.
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string:"), stdout);
	_fputts(string, stdout);

	return 0;
}