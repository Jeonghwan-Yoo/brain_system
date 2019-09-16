//종료 핸들러의 동작
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR str[2];

	__try
	{
		//메모리 복사가 일어나는데, 문자열을 저장할 공간이 턱없이 부족하다.
		//따라서 할당되지 않은 메모리 공간으로 복사를 시도하는 과정에서 메모리 참조 오류가 발생한다.
		//프로그램은 종료된다.
		//그러나 __try 블록 안에서 발생한 오류이기 때문에 __finally 블록은 실행된다.
		//__finally 블록은 __try블록 내에서 오류가 발생해도 실행된다.
		_tcscpy(str, _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ~"));
		_tprintf(_T("%s\n"), str);
	}
	__finally
	{
		_tprintf(_T("__finally block!\n"));
	}
	return 0;
}