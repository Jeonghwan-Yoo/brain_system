//DuplicateHandle �Լ��� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hParent = (HANDLE)_ttoi(argv[1]);
	//WaitForSingleObject�Լ��� ȣ���ϸ鼭 �θ� ���μ����� �ڵ��� ���ڷ� �ް� �ִ�.
	//�θ� ���μ����� ����� ������ ��ٸ��� ��.
	DWORD isSuccess = WaitForSingleObject(hParent, INFINITE);

	_tprintf(_T("[Child Process]\n"));

	if (isSuccess == WAIT_FAILED)
	{
		_tprintf(_T("WAIT_FAILED returned!"));
		Sleep(10000);
		return -1;
	}
	else 
	{
		_tprintf(_T("General Lee said, \"Don't inform") _T("the enemy my death\""));
		Sleep(10000);
		return 0;
	}
}