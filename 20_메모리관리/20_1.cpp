//시스템 정보 확인하기
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SYSTEM_INFO si;
	DWORD allocGranularity;
	DWORD pageSize;

	//GetSystemInfo 함수 호출을 통해 구조체 SYSTEM_INFO 멤버에 시스템 정보를 채운다.
	GetSystemInfo(&si);
	pageSize = si.dwPageSize;
	allocGranularity = si.dwAllocationGranularity;

	//각각 페이지의 크기와 Allocation Granularity Boundary 값을 얻어 출력하고 있다.
	//1024로 나눠 KB단위로 출력하였다.
	_tprintf(_T("Page size:%uKbytes\n"), pageSize / 1024);
	_tprintf(_T("Allocation granularity:%uKbytes\n"), allocGranularity / 1024);
	return 1;
}