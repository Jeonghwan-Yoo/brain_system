//���� ���� ���� ���μ��� ���� ���
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <TlHelp32.h> //�߰��� �������

int _tmain(int argc, TCHAR* argv[])
{
	//Snapshot�� �� �״�� ������ ��� �Լ��̴�.
	//TH32CS_SNAPPROCESS�� ���� ���� ���� ���μ����� ������ ������� �ǹ��̴�.
	//(������ ��´ٴ� ���� ��� ���ϴ� ���μ��� ������ �Լ� ȣ�� ���� �������� ����)
	//�� �Լ��� ���μ����Ӹ� �ƴ϶� ���μ����� ����ϴ� ��, ���, �׸��� ������ ������ ���� �� �ִ�.
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("CreateToolhelp32Snapshot error!\n"));
		return -1;
	}

	//���μ��� ���� ��� ���� ����ü ����
	//���� ������ ���캸�鼭 ���μ��� ������ ������ �غ�.
	//�� ����ü�� �����ϴ� ����� Ȯ���� ���� ��� �������� ���� �� �ִ��� �� �� �ִ�.
	//���� �ʱ�ȭ�� �ݵ�� �ʿ��ϴ�.
	//ù ��° ���μ��� ������ ȣ���� ���� Process32First�Լ��� ȣ���Ѵ�.
	//�� ��° ���μ��� �������ʹ� Process32Next�Լ��� ȣ���Ѵ�.
	//������ �����ϴ� ���°� ���ڿ� ��ū ������ ��İ� �����ϴ�.
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf(_T("Process32First error!\n"));
		CloseHandle(hProcessSnap);
		return -1;
	}

	HANDLE hProcess;
	do
	{
		//���μ��� �̸�, ID���� ���
		_tprintf(_T("%25s %5d\n"), pe32.szExeFile, pe32.th32ProcessID);
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 0;
}