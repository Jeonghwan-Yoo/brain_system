#define UNICODE
#define _UNICODE
//TCHAR�� "wchar_t"��, _T("1234567")�� L"1234567"�� �νĵȴ�.
//UNICODE, _UNICODE ���Ǵ� ������� ���� ������ �����ؾ� �Ѵ�.
//�� ������ ���ǵ� ��ũ�ο� ���� ������Ͽ� ����� �ڷ����� ���°� �����Ǳ� ����.

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