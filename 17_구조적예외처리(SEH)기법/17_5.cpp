//SEH의 실행 흐름 파악하기
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("start point!\n"));

	int* p = NULL;

	__try
	{
		//할당되지 않은 주소 NULL에 값을 쓰려하고 있다. 그래서 예외상황 발생
		*p = 100; //예외발생 지점
		//위에서 예외가 발생하면, __except 블록의 예외필터를 검사한다.
		//검사 결과를 가지고 실행의 흐름을 결정하게 되는데, EXCEPTION_EXECUTE_HANDLER는 우선 __except을 실행.
		//실행됨으로 인해 예외상황이 적절히 처리되었다고 Windows는 간주한다.
		//예외상황이 처리된 다음(__except 블록 이후), __except 블록의 이후 부분을 실행하게 된다.
		_tprintf(_T("value:%d\n"), *p);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("exception occurred!\n"));
	}

	_tprintf(_T("end point!\n"));
	return 0;
}