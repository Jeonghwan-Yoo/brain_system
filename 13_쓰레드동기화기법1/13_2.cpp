//���� ������ �������� ���� ����
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//ũ��Ƽ�� ���� ������Ʈ�� ����.
CRITICAL_SECTION hCriticalSection;

void IncreaseCount()
{
	//�Ӱ迵�� ���� ������ EnterCriticalSection, ���������鼭 LeaveCriticalSection.
	//�Ӱ� ������ �����忡 ���� ���ÿ� ����Ǵ� ���� �߻����� �ʵ��� ������ ����ȭ.
	EnterCriticalSection(&hCriticalSection);
	gTotalCount++; //�� �̻��� �����忡 ���� ����Ǵ� �ڵ忩�� �Ӱ� ������ �����ϴ� ����.
	LeaveCriticalSection(&hCriticalSection);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0;i < 1000;i++)
	{
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	//ũ��Ƽ�� ���� ������Ʈ�� �ʱ�ȭ.
	//ũ��Ƽ�� ���� ����ȭ�� �ʿ��� ��� �ʱ�ȭ�� �̷�����.
	InitializeCriticalSection(&hCriticalSection);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		hThread[i] = 
			(HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		ResumeThread(hThread[i]);
	}

	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count : %d\n"), gTotalCount);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		CloseHandle(hThread[i]);
	}

	DeleteCriticalSection(&hCriticalSection);
	return 0;
}