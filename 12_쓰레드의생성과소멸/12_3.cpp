//�����带 �̿��� �۾��� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//���μ��� ���� ���� ������ ����
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD* nPtr = (DWORD*)lpParam;

	//������ �Լ� ȣ�� �� �� ���� ���ڰ� ����.
	//���������� �����͸� ������ ��ȯ�ؼ� ���� ���Ѵ�.
	//�迭�� ���·� ����� �������ڰ� �ʿ��ϴ�.
	DWORD numOne = *nPtr;
	DWORD numTwo = *(nPtr + 1);

	DWORD total = 0;
	for (DWORD i = numOne; i <= numTwo;i++)
	{
		total += i;
	}
	//����� ��ȯ
	//�۾��� ���� �����尡 ����ʰ� ���ÿ� ������� ��ȯ�ϴ� ��Ȳ.
	//�� ������� main�����尡 ���� �� �־�� �Ѵ�.
	//�ڽ� ���μ����� ��ȯ�� �����(�����ڵ�)�� �θ� ���μ����� GetExitCodeProcess�Լ� ȣ���� ���� ��´�.
	//"�����尡 �Լ��� ��ȯ�� ������� ���μ����� �����ڵ�ó�� Ŀ�� ������Ʈ�� �� ����� ����ȴ�."
	return total;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];

	//������ ���� �� ����ϰ� �� �������ڸ� �迭�� ����
	DWORD paramThread[] = { 1,3,4,7,8,10 };
	DWORD total = 0;
	DWORD result = 0;

	//�� 3���� �����尡 �����ǹǷ� ���� ���ÿ� ������ �Լ� ThreadProc�� ȣ��ȴ�.
	//���� �ڵ� ������ �����ϴ� ���� ������ �����帶�� ������ ������ �ְ�, �������� total��
	//������ ���ÿ� �Ҵ�ǹǷ� ���ÿ� �����ϰ� �ȴٰ��� ������ �߻������� �ʴ´�.
	hThread[0] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[0]), 0, &dwThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[2]), 0, &dwThreadID[1]);
	hThread[2] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[4]), 0, &dwThreadID[2]);

	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault!\n"));
		return -1;
	}

	//������ �� ���� �����尡 ������ ����Ǳ⸦ ��ٸ��� �ִ�.
	//����ÿ� �ش� Ŀ�� ������Ʈ�� Signaled���°� �ȴ�.
	//main�������� ����� ���μ����� ����� �̾�����.
	//���࿡ ���μ����� ����Ǹ� ���� ������ ����ϴ� ��������� �ڽ��� ���� ��ġ�⵵ ���� �Ҹ�ǰ� ����.
	//�׷��� �Ǹ� ��°���� ������ �ȴ�.
	WaitForMultipleObjects(
		3, //�� 3���� Ŀ�� ������Ʈ�� ����
		hThread, //Ŀ�� ������Ʈ �ڵ��� �迭 ����
		TRUE, //��� Ŀ�� ������Ʈ�� signaled ���°� �Ǳ⸦ 
		INFINITE //������ ��ٸ���.
	);

	//�������� �����ڵ带 ��� ���� ���Ǵ� �Լ�.
	//�����ڵ尡 ��ϵǸ鼭���� ��� �Ǳ������ ������ ���μ����� �����ڵ带 ��� ������ ����.
	GetExitCodeThread(hThread[0], &result);
	total += result;

	GetExitCodeThread(hThread[1], &result);
	total += result;

	GetExitCodeThread(hThread[2], &result);
	total += result;

	_tprintf(_T("total (1~10) : %d\n"), total);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	return 0;
}