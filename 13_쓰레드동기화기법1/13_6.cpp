#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

LONG gTotalCount = 0;
HANDLE hMutex;

//�� �Լ��� �������� ���ؽ��� ȹ���� ���Ŀ� ��ȯ�ϴ� �ڵ� ���� �Լ��� �����Ѵٴ� ��.
//IncreaseCountTwo �Լ��� �������Լ��� �ϴ� ������� ���ؽ��� ���� ���ϴ� ��Ȳ�� ���̰� �ȴ�.
//�̷��� ��Ȳ�� ������ Windows�� ���ؽ��� ������ ����ϴ� �����尡 ���ؽ��� ȹ���� �� �ֵ��� ���ؽ��� ���¸� ����.
unsigned int WINAPI IncreaseCountOne(LPVOID lpParam)
{
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;
	return 0;
}

unsigned int WINAPI IncreaseCountTwo(LPVOID lpParam)
{
	DWORD dwWaitResult = 0;
	//���ؽ��� ȹ���� ����ϴ� ������� ��ȯ�� WAIT_ABANDONED�� ��Եȴ�.
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		ReleaseMutex(hMutex);
		break;
	case WAIT_ABANDONED:
		_tprintf(_T("WAIT_ABANDONED\n"));
		break;
	}
	gTotalCount++;
	ReleaseMutex(hMutex);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadIDOne;
	DWORD dwThreadIDTwo;

	HANDLE hThreadOne;
	HANDLE hThreadTwo;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL)
		_tprintf(_T("CreateMutex error:%d\n"), GetLastError());

	//������ ������
	hThreadOne = (HANDLE)_beginthreadex(
		NULL, 0, IncreaseCountOne, NULL, 0, (unsigned*)&dwThreadIDOne
	);
	//�������� ������ ���߱� ���� CREATE_SUSPENDED�� ����.
	hThreadTwo = (HANDLE)_beginthreadex(
		NULL, 0, IncreaseCountTwo, NULL, CREATE_SUSPENDED, (unsigned*)&dwThreadIDTwo
	);
	//�� 0.1�� �Ŀ� �Լ��� ȣ���Ű�鼭 ������ ����.
	//�� ��° �������� ����ð��� ���� ù ��° �����尡 ���� ���ؽ��� �򵵷� �ϱ� ����.
	Sleep(1000);
	ResumeThread(hThreadTwo);

	WaitForSingleObject(hThreadTwo, INFINITE);
	_tprintf(_T("total count:%d\n"), gTotalCount);

	CloseHandle(hThreadOne);
	CloseHandle(hThreadTwo);
	CloseHandle(hMutex);

	return 0;
}