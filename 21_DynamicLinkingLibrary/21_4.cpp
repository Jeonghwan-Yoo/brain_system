//Explicit DLL 활용
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include "SwapDll.h"

typedef void(*SWAP_FUNC)(int*, int*);

int _tmain(int argc, TCHAR* argv[])
{
	HMODULE hinstLib;
	SWAP_FUNC SwapFunction;

	//DLL을 프로세스 가상 메모리에 Loading 한다.
	hinstLib = LoadLibrary(_T("SwapDll"));
	if (hinstLib == NULL)
	{
		_tprintf(_T("LoadLibrary fail!\n"));
		return -1;
	}
	//이름으로 함수 포인터를 얻고 있다.
	SwapFunction = (SWAP_FUNC)GetProcAddress(hinstLib, _T("swap"));
	if (SwapFunction == NULL)
	{
		_tprintf(_T("GetProcAddress fail!\n"));
		return -1;
	}

	int a = 10;
	int b = 20;
	_tprintf(_T("Before:%d, %d\n"), a, b);

	SwapFunction(&a, &b);
	_tprintf(_T("After:%d, %d\n"), a, b);

	//로딩한 DLL을 반환하고 있다.
	BOOL isSuccess = FreeLibrary(hinstLib);
	if (isSuccess == NULL)
	{
		_tprintf(_T("FreeLibrary fail!\n"));
		return -1;
	}

	return 0;
}