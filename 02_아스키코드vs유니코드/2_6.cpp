#include <stdio.h>

//wchar_t* argv[]로 바꾸면 문제가 발생하지 않는 것처럼 보이지만 엉뚱한 출력결과가 보인다.
//왜냐하면 main이라는 이름의 함수는 프로그램 실행 시, 전달되는 문자열을 MBCS기반으로 구성하기 때문.
int main(int argc, char* argv[]) { //char형의 문자열 포인터는 SBCS기반
	int i;
	for (i = 0;i < argc;i++) {
		//문제는 출력의 대상이 되는 문자열이 유니코드 기반이 아니다.
		//fputws(argv[i], stdout);
	}

	return 0;
}