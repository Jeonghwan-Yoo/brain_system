#define UNICODE
#define _UNICODE
//TCHAR은 "wchar_t"로, _T("1234567")은 L"1234567"로 인식된다.
//UNICODE, _UNICODE 정의는 헤더파일 선언 이전에 등장해야 한다.
//그 이유는 정의된 매크로에 따라서 헤더파일에 선언된 자료형의 형태가 결정되기 때문.

//#undef UNICODE
//#undef _UNICODE

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int wmain(void) {
	TCHAR str[] = _T("1234567");
	int size = sizeof(str);
	printf("string length : %d\n", size);
	return 0;
}