#include <stdio.h>

int wmain(int argc, wchar_t* argv[]) { //���޵Ǵ� ���ڿ��� �����ڵ� ������� �����ȴ�.
	for (int i = 1;i < argc;i++) {
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}

	return 0;
}