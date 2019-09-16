//EXCEPTION_EXECUTE_HANDLER 활용 사례
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu(void);
BOOL Calculator(void);

int _tmain(int argc, TCHAR* argv[])
{
	BOOL state;

	do
	{
		state = Calculator();
	} while (state == TRUE);
}

DWORD ShowMenu(void)
{
	DWORD sel;

	_fputts(_T("-----Menu-----\n"), stdout);
	_fputts(_T("num 1:Divide\n"), stdout);
	_fputts(_T("num 2:Multiple\n"), stdout);
	_fputts(_T("num 3:Add\n"), stdout);
	_fputts(_T("num 4:Minus\n"), stdout);
	_fputts(_T("num 5:Exit\n"), stdout);
	_fputts(_T("SELECTION >>"), stdout);
	_tscanf(_T("%d"), &sel);

	return sel;
}

BOOL Calculator(void)
{
	DWORD sel;
	int num1, num2, result;

	sel = ShowMenu();
	if (sel == EXIT)
		return FALSE;

	_fputts(_T("Input num1 num2:"), stdout);
	_tscanf(_T("%d %d"), &num1, &num2);

	__try
	{
		switch (sel)
		{
		//두 번째 입력값 0으로 num2가 채워지는 경우, 문제가 발생.
		//나눗셈 연산은 계속 진행할 수 없게 되고, 재입력을 요구하는 메시지를 출력하고 입력을 다시 받는다.
		case DIV:
			result = num1 / num2;
			//0으로 나누면 연산결과가 의미가 없어졌기 때문에 실행도 의미를 잃는다.
			//건너 뛰어야 잘못된 결과를 출력하지 않는다.
			//프로그램 코드는 앞 줄의 실행결과가 다음 줄에 의미를 부여하는 경우가 대부분이다.
			//그래서 특정 위치에서 예외상황이 발생하면, 관련된 나머지 부분도 건너 뛸 필요가 있다.
			_tprintf(_T("%d/%d=%d\n\n"), num1, num2, result);
			break;
		case MUL:
			result = num1 * num2;
			_tprintf(_T("%d*%d=%d\n\n"), num1, num2, result);
			break;
		case ADD:
			result = num1 + num2;
			_tprintf(_T("%d+%d=%d\n\n"), num1, num2, result);
			break;
		case MIN:
			result = num1 - num2;
			_tprintf(_T("%d-%d=%d\n\n"), num1, num2, result);
			break;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("Wrong number inserted. Try again!\n\n"));
	}
	return TRUE;
}