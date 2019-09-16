//힙의 컨트롤에 대한 이해
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	SYSTEM_INFO sysInfo;

	GetSystemInfo(&sysInfo);
	UINT pageSize = sysInfo.dwPageSize;

	//1. 힙의 생성
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);

	//2. 메모리 할당
	int* p = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 10);

	//3. 메모리 활용
	for (int i = 0;i < 10;i++)
		p[i] = i;

	//4. 메모리 해제
	HeapFree(hHeap, 0, p);

	//5. 힙 소멸
	HeapDestroy(hHeap);

	//GetProcessHeap 함수가 호출되고 있는데, 디폴트 힙을 얻을 때 사용하는 함수이다.
	HANDLE hDefaultHeap = GetProcessHeap();
	//디폴트 힙의 핸들을 참조해서 메모리를 할당하고 있다.
	//이는 malloc과 free 함수 호출을 통해 디폴트 힙에 메모리를 할당하고 반환하는 것과 동일한 작업.
	//malloc과 free 함수 대신 디폴트 힙을 얻어 작업을 할 경우 얻게 되는 장점은 추가적인 컨트롤이다.
	//성능향상을 고려해 HEAP_NO_SERIALIZE를 지정하고 있다.
	//메모리를 할당하는 과정에서 동기화를 할 수도 있고, 안 할 수도 있다.
	TCHAR* pDefault = (TCHAR*)HeapAlloc(hDefaultHeap, HEAP_NO_SERIALIZE, sizeof(TCHAR) * 10);
	_tcscpy(pDefault, _T("Default Heap!"));
	_tprintf(_T("%s\n"), pDefault);
	//할당한 메모리를 반환하고 있다.
	HeapFree(hDefaultHeap, HEAP_NO_SERIALIZE, pDefault);

	return 1;
}