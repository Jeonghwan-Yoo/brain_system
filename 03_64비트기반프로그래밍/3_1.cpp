#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

UINT CalDistance(UINT a, UINT b) {
	return a - b;
}

int _tmain(void) {
	INT val1 = 10;
	INT val2 = 20;

	_tprintf(_T("Position %d, %d\n"), (UINT)&val1, (UINT)&val2);
	//두 변수의 주소값을 인자로 전달받아서 메모리상의 거리를 계산해서 반환해 주는 함수이다.
	//순수 메모리의 거리를 계산하기 위해서 포인터가 지니는 주소값을 정수형으로 변환해서 전달하고 있다.
	_tprintf(_T("distance : %d\n"), CalDistance((UINT)&val1, (UINT)&val2));

	return 0;
}