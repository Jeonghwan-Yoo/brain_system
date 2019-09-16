//�������� ���� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	while (1)
	{
		_tprintf(_T("Running State!\n"));
		Sleep(10000);
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId;
	HANDLE hThread;
	DWORD susCnt; //suspend count�� Ȯ���ϱ� ���� ����

	//�����尡 �ϴ� ���� ���ڿ��� ����ϴ� ���̴�.
	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, 
		//������ ������ ���õ� ���ڿ� CREATE_SUSPENDED�� ���޵Ǹ� �����尡 �������ڸ��� �����ҵ� ī��Ʈ�� 1.
		//�� �����尡 �������ڳ��� Blocked���·� �Ǵ� ��.
		CREATE_SUSPENDED,
		(unsigned*)&dwThreadId);

	//������ ���� Ȯ��
	if (hThread == NULL)
		_tprintf(_T("Thraed creation fault!\n"));

	//Blocked���¿� ������ ������ ���ؼ� ResumeThread�Լ��� ȣ������� �Ѵ�.
	//ȣ��� ����, ������� ������ ������ ���̴�.
	//�׸��� �Լ� ȣ�� �� ��ȯ ���� 1�̴�.
	//�ֳ��ϸ� �����ϱ� ������ �����ҵ� ī��Ʈ�� ��ȯ�ϱ� ����.
	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);
	Sleep(10000);

	//�� �� ȣ��Ǵ� �����ҵ� ī��Ʈ�� 2���ǰ� ResumeThread�Լ��� �� �� ȣ��Ǿ�� ������ ������ �簳�ȴ�.
	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count : %d\n"), susCnt);

	//���μ����� ���Ḧ ���� �������� ������ Ȯ���ϱ� ����.
	WaitForSingleObject(hThread, INFINITE);
	return 0;
}