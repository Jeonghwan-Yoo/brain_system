#include <stdio.h>
#include <Windows.h>

int wmain(int argc, wchar_t* argv[]) {
	LPSTR str1 = "SBCS Style String 1"; //char*로 MBCS
	LPWSTR str2 = L"WBCS Style String 1"; //wchar_t*로 유니코드 기반

	CHAR arr1[] = "SBCS Style String 2";
	WCHAR arr2[] = L"WBCS Style String 2";

	LPCSTR cSt1 = arr1; //const char*
	LPCWSTR cStr2 = arr2; //const wchar_t*

	printf("%s\n", str1);
	printf("%s\n", arr1);

	wprintf(L"%s\n", str2);
	wprintf(L"%s\n", arr2);

	return 0;
}