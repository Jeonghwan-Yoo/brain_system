//CloseHandle �Լ� ����2
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD n = 0;
	//100ȸ�� ���� ���ڿ��� ����Ѵ�.
	while (n < 100)
	{
		//����ӵ��� ���� ����Ǵ� ��Ȳ�� �����ϰ� �ľ�.
		for (DWORD i = 0;i < 10000;i++)
			for (DWORD i = 0;i < 10000;i++); //Busy Waiting!!

		_fputts(_T("KernelObjProb2.exe\n"), stdout);
		n++;
	}
	return 0;
}