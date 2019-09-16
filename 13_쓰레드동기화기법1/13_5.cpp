#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex;
DWORD dwWaitResult;

//�ϴ� ���� ���� "Thread Running!"�̶�� ���ڿ��� ���� �ð� �������� �� 5�� ���.
void ProcessBaseCriticalSection()
{
	//���ؽ��� �����Ϸ� �Ѵ�.
	//��� WaitForSingleObject�� ���� �Լ� ȣ�� �� ��ȯ���� ���� ����� Ȯ���ؾ߸��Ѵ�.
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	//�����尡 ���ؽ��� �����ߴ�.
	case WAIT_OBJECT_0:
		_tprintf(_T("thread got mutex !\n"));
		break;
	//time-out �߻��ߴ�.
	case WAIT_TIMEOUT:
		_tprintf(_T("timer expired !\n"));
		return;
	//���ؽ� ��ȯ�� ������ �̷����� �ʾҴ�.
	//���ؽ� �����ڰ� ��ȯ�� ������ ���� ���� ��Ȳ���� ��ȯ�Ǵ� ��.
	case WAIT_ABANDONED:
		return;
	}
	for (DWORD i = 0;i < 5;i++)
	{
		_tprintf(_T("Thread Running !\n"));
		Sleep(10000);
	}
	//�Լ��� ���������鼭 ������ ���ؽ��� ��ȯ�ϰ� �ִ�.
	ReleaseMutex(hMutex);
}

int _tmain(int argc, TCHAR* argv[])
{
//0�� 1�� �����ϰ� �������� �ϸ�, ���ؽ��� �����ϴ� ���μ����� ���������� �����ȴ�.
//0���� �����ϰ� �������� �ϸ�, �Լ��� ȣ���ϴ� ���������� �����ȴ�.
#if 1
	//�����ϴ� ���ؽ��� "NamedMutex"��� �̸��� ��´�.
	//�ٸ� ��� ���μ�����, �� �̸��� ���� ���ؽ� ������Ʈ�� �����ϱ� ���� �ڵ鰪�� ���� �� �ִ�.
	hMutex = CreateMutex(NULL, FALSE,
		_T("NamedMutex")); //named mutex
#else
	//�� �Լ��� �̹� �����Ǿ� �ִ� �̸��ִ� ���ؽ��� �ڵ��� ��� ���� ���Ǵ� �Լ��̴�.
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS, //���ٱ��� ��û
		FALSE, //�ڵ��� ������� �ʰڴ�.
		_T("NamedMutex") //���ؽ� ������Ʈ �̸�.
	);
#endif

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error:%d\n"), GetLastError());
		return -1;
	}
	ProcessBaseCriticalSection();

	CloseHandle(hMutex);
	return 0;
}