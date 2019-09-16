//�ý��� ���� Ȯ���ϱ�
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SYSTEM_INFO si;
	DWORD allocGranularity;
	DWORD pageSize;

	//GetSystemInfo �Լ� ȣ���� ���� ����ü SYSTEM_INFO ����� �ý��� ������ ä���.
	GetSystemInfo(&si);
	pageSize = si.dwPageSize;
	allocGranularity = si.dwAllocationGranularity;

	//���� �������� ũ��� Allocation Granularity Boundary ���� ��� ����ϰ� �ִ�.
	//1024�� ���� KB������ ����Ͽ���.
	_tprintf(_T("Page size:%uKbytes\n"), pageSize / 1024);
	_tprintf(_T("Allocation granularity:%uKbytes\n"), allocGranularity / 1024);
	return 1;
}