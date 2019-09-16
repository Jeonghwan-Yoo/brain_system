//�Ӱ� ������ ���� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

//���������� 1�� ������Ű�� ����.
//������ ���� ���� ������� ���尴�� ���� ���������� ����ϰ� �ȴ�.
void IncreaseCount()
{
	gTotalCount++; //�Ӱ� ����
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0;i < 1000;i++)
	{
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR** argv)
{
	DWORD dwThreadId[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		hThread[i] = 
			//CREATE_SUSPEND�� �����ϹǷ� ������ ������� �ٷν������ �ʴ´�.
			(HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		//�Լ��� ȣ��Ǵ� �������� �����尡 ����.
		//�������� ������ ��������� �ð��� �ɸ��� ������ �����带 ���� ������ ���� ���ÿ� ������ ����,
		//������ ���࿡ �־ �߻��ϴ� �ð����� �ּ�ȭ�Ϸ��� �Ͽ���.
		ResumeThread(hThread[i]);
	}
	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);

	_tprintf(_T("total count : %d\n"), gTotalCount);

	for (DWORD i = 0;i < NUM_OF_GATE;i++)
	{
		CloseHandle(hThread[i]);
	}
	return 0;
}