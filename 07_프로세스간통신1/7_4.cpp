//전달된 인자 사이의 수 덧셈
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//만약 전달인자의 개수가 3개가 아니라면 오류라고 인식을 하고 -1을 반환하도록 되어 있다.
	//두 정수 사이의 덧셈 결과가 -1이 되지 않는다는 가정을 하고 있다.
	if (argc != 3)
		return -1;

	//_tmain 호출 시 전달되는 두 개의 숫자 정보를 얻는다.
	//이는 자식 프로세스를 생성하면서 동시에 데이터를 전달하는 가장 쉬운 방법이다.
	//부모 프로세스는 자식 프로세스를 생성하는 과정에서 _tmain함수에 문자열을 전달할 수 있다.
	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start;i <= end;i++)
		total += i;

	return total;
}