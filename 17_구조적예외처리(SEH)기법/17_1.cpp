//종료 핸들러의 동작

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//변수가 선언된 후 __try 블록에서 실행.
	int a, b;

	__try
	{
		_tprintf(_T("input divide string [a/b]:"));
		_tscanf(_T("%d/%d", &a, &b));
		//만약 b가 0이라면, 값을 반환하기 전에 __finally 블록이 실행된다.
		if (b == 0)
			return -1;
	}
	//__try블록안에 코드가 한 줄이라도 실행되면 반드시 실행됨.
	__finally
	{
		_tprintf(_T("__finally block!\n"));
	}
	_tprintf(_T("result:%d\n"), a / b);
	return 0;
}