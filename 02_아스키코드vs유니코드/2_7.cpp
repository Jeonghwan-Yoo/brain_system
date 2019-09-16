#include <stdio.h>

int wmain(int argc, wchar_t* argv[]) { //전달되는 문자열은 유니코드 기반으로 구성된다.
	for (int i = 1;i < argc;i++) {
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}

	return 0;
}