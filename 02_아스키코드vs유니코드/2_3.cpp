#include <stdio.h>
#include <string.h>

int main(void) {
	wchar_t str[] = L"ABC";
	int size = sizeof(str); //sizeof()는 연산자이기 때문에 상관없이 배열의 크기를 계산해 반환한다
	//컴파일 에러가 발생한다. strlen함수는 SBCS기반 문자열을 처리하기 위한 함수이기 때문.
	//int len = strlen(str);

	printf("배열의 크기 : %d\n", size);
	//printf("문자열 길이 : %d\n", len);

	return 0;
}