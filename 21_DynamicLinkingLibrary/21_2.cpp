//swap 라이브러리의 활용
#include <stdio.h>
#include <tchar.h>
//swap.h파일을 include문에 의해 포함될 수 있는 경로에 복사해야 된다.(프로젝트 파일의 위치).
//비록 SwapStaticLib.lib에 바이너리로 존재하는 swap 함수를 호출할 예정이지만, 연계성은 링크과정을 통해 구성.
//컴파일러는 swap함수 호출 문장을 이해하지 못하므로 include 해줘야 한다.
#include "swap.h"

//#pragma comment(lib, "SwapStaticLib.lib")

int _tmain(int argc, TCHAR* argv[])
{
	int a = 10;
	int b = 20;
	_tprintf(_T("Before:%d, %d\n"), a, b);

	swap(&a, &b);
	_tprintf(_T("After:%d, %d\n"), a, b);
	
	return 0;
}