//ũ��Ƽ�� ���ǰ� ���ؽ� ��
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//���ؽ��� Ŀ�� ������Ʈ�̹Ƿ� HANDLEŸ���� ������ �ڵ鰪�� �����Ѵ�.
//CRITICAL_SECTION gCriticalSection;
HANDLE hMutex;

void IncreaseCount()
{
	//���ؽ��� �������
	//EnterCriticalSection(&gCriticalSection);
	WaitForSingleObject(hMutex, INFINITE);

	gTotalCount++;

	//ȹ���� ���ؽ��� ��ȯ�ϰ� ���ؽ��� Signaled���°� �ȴ�.
	//LeaveCriticalSection(&gCriticalSection);
	ReleaseMutex(hMutex);
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

	//���ؽ��� �����ϰ� �ִ�. FALSE�� �������Ե� �������� ���� ���·� �����ȴ�. Signaled���·� ���ؽ� ����.
	//InitializeCriticalSection(&gCriticalSection);
	hMutex = CreateMutex(
		NULL, //����Ʈ ���� ������
		FALSE, //������ ������ �� �ִ� ���·� ����
		NULL //unnamed mutex
	);
	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error : %d\n"), GetLastError());
	}

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
	
	//�Ҵ���� ���ҽ��� ����.
	//�Լ��� ȣ���ϴ� �������� �ü���� ���� �Ҵ�� Ŀ�� ������Ʈ�� �Ҹ�ȴ�.(Usage Count = 0)
	//DeleteCriticalSection(&gCriticalSection);
	CloseHandle(hMutex);
	return 0;
}