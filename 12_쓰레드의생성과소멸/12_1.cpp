//���� ������ �������� ���� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_THREADS (1024*10)

//�������� main�Լ��� �ش��ϴ� ������ �Լ��� �����ϰ� �ִ�.
//������ �Լ��� Ÿ���� �ݵ�� �̿� ��ġ�ؾ� �Ѵ�.
//���� Ÿ���� DWORD�̰�, �Ű����� Ÿ���� LPVOID�̾�� �Ѵ�.
//������ �Լ� �̸� �տ� �ִ� WINAPI�� �Լ� ȣ��Ծ࿡ ���õ� �����̴�.
//������ ���� �� ������ �Լ��� �����ϳ��� �����ϴµ� �� ���ڴ� �����尡 ������ ������ �ǹ��Ѵ�.
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		_tprintf(_T("thread num : %d\n"), threadNum);
		//���� ���� ���� ���μ����� ��� ���ߴ� ����� �Ѵ�.
		//������ Windows�� ������ �߽��� �ü���̹Ƿ� ���������� ȣ���ϴ� �����带 ��� ���߰� �ϴ� ��.
		//���⼭�� ������ �ӵ��� ���߱� ���� �뵵
		Sleep(5000); 
	}
	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	//���� ������ �ִ� ������ ������ ����
	//����ؼ� �����带 �����ϰ� �ִ�.
	//������ ������ ���и� �ϸ�, �� ������ ������ ����ϰ� break���� ���� �������´�.
	while (1)
	{
		hThread[cntOfThread] = CreateThread(
			NULL, //����Ʈ ���� �Ӽ� ����
			0, //����Ʈ ���� ������
			ThreadProc, //������ �Լ�
			(LPVOID)cntOfThread, //������ �Լ��� ��������
			0, //����Ʈ ���� flag����
			&dwThreadID[cntOfThread] //������ ID ��ȯ
		);
		//������ ���� Ȯ��
		if (hThread[cntOfThread] == NULL)
		{
			_tprintf(_T("MAXIMUM THREAD NUMBER : %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}
	for (DWORD i = 0;i < cntOfThread;i++)
	{
		//���ҽ� ������ �ֹ��ϰ� �ִ�.
		//�����嵵 Windows���������� Ŀ�� ������Ʈ ������ �����Ѵ�.
		//���� CloseHandle�� ���� ���ҽ� ������ �ֹ��ؾ� �Ѵ�.
		CloseHandle(hThread[i]);
	}
	return 0;
}