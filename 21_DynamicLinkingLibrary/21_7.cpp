//DLL 참조하는 프로그램
#include <stdio.h>
#include <tchar.h>
//헤더파일은 DLL을 만들 때에도 사용되었던 헤더파일.
#include "Calculator.h"

#pragma comment(lib, "Calculator.lib")

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("result Add:%d\n"), Add(5, 3));
	_tprintf(_T("result Min:%d\n"), Min(5, 3));
	_tprintf(_T("result Mul:%e\n"), Mul(5.0, 3.0));
	_tprintf(_T("result Div:%e\n"), Div(5.0, 3.0));

	return 0;
}