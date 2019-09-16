//EXCEPTION_CONTINUE_EXECUTION 활용 사례
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu(void);
BOOL Calculator(void);
DWORD FilterFunction(DWORD exptType);

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

int num1, num2, result;

BOOL Calculator(void)
{
	DWORD sel;

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
			//GetException함수는 EXCEPTION_INT_DIVIDE_BY_ZERO를 반환한다.
			result = num1 / num2;
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
	//예외필터 표현식이 아닌 FilterFunction이라는 이름의 함수를 호출하고 있다.
	//GetExcetionCode 함수의 호출을 통해 얻어진 예외 정보를 인자로 전달하면서 FilterFunction 함수를 호출.
	__except (FilterFunction(GetExceptionCode()))
	{
		_tprintf(_T("__except block...\n\n"));
	}
	return TRUE;
}

//이 함수는 예외의 종류에 따라 반환하는 필터 표현식이 다르다.
//즉 예외의 종류에 따라 예외가 처리되는 방식을 달리한다.
DWORD FilterFunction(DWORD exptType)
{
	switch (exptType)
	{
	//이 부분은 예외가 발생할만한 부분은 없다.
	case EXCEPTION_ACCESS_VIOLATION:
		_tprintf(_T("Access violation\n\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	//예외가 발생한 원인에 해당하는 num2의 값을 재입력받고 있다.
	//그리고 EXCEPTION_CONTINUE_EXECUTION을 반환한다.
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		_tprintf(_T("Wrong number inserted.\n"));
		_tprintf(_T("Input second number again:"));
		_tscanf(_T("%d"), &num2);
		return EXCEPTION_CONTINUE_EXECUTION;

	default:
		return EXCEPTION_EXECUTE_HANDLER;
	}
}