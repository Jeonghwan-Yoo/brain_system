//main 함수의 전달인자를 덧셈하는 프로그램
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD val1, val2;
	//_ttoi함수는 문자열 데이터를 정수형 데이터로 변경시키는 atoi함수와 유니코드 기반의 _wtoi를 동시에
	//지원하기 위한 매크로이다.
	val1 = _ttoi(argv[1]);
	val2 = _ttoi(argv[2]);

	_tprintf(_T("%d + %d = %d\n"), val1, val2, val1 + val2);

	//_gettchar함수는 getchar함수와 유니코드 기반의 gettchar함수를 동시 지원하기 위한 매크로 함수.
	_gettchar(); //프로그램의 실행을 잠시 멈추기 위해
	return 0;
}