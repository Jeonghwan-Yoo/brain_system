//문자열을 토큰으로 나누는 예제
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//토큰을 나눌 문자열을 선언하고 있다.
	//이는 하나의 문자열로 인식이 된다.
	TCHAR string[] = _T("Hey, get a life!") _T("You don't even have two pennies to rub together.");
	//토큰을 나누는 기준을 모아서 문자열을 구성하고 있다.
	TCHAR seps[] = _T(" ,.!");

	//토큰 분리 조건, 문자열 설정 및 첫 번째 토큰 반환
	//토큰을 나눌 대상이 되는 문자열(첫 번째 전달인자)와 토큰의 기준(두 번째 전달인자)을 지정해 주고 있다.
	//_tcstok함수는 매크로 _UNICODE가 정의되어 있는 경우 strtok의 유니코드 버전인 wcstok함수로 해석된다.
	//그리고 _tcstok 함수는 문자열과 토큰을 지정하기 위해 처음 호출될 때에도 첫 번째 토큰이 반환된다.
	//반환된 포인터는 첫 번째 토큰을 가리키게 된다.
	TCHAR* token = _tcstok(string, seps);

	//계속해서 토큰을 반환 및 출력
	while (token != NULL)
	{
		_tprintf(_T("%s\n"), token);
		//한번 문자열과 토큰이 지정되면, 다음 토큰을 얻기 위해서도 _tctok함수를 호출한다.
		//NULL은 이전에 설정한 문자열의 다음 토큰을 얻기위해 함수를 호출하고 있음.
		token = _tcstok(NULL, seps);
	}
	return 0;
}