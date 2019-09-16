//프로그램 : 핸들러의 중첩!
//Calculator 함수를 제외한 나머지 코드는 기존과 동일.
//프로그램 설명 : 예외의 추적!
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1, MUL, ADD, MIN, EXIT };

DWORD ShowMenu(void);
BOOL Calculator(void);

void Divide(int, int);
void Multiple(int, int);
void Add(int, int);
void Min(int, int);

int _tmain(int argc, TCHAR* argv[])
{
	BOOL state;

	do
	{
		state = Calculator();
	} while (state == TRUE);

	return 0;
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

	//핸들러 중첩이 가능하다.
	//__try__except 블록이 __try__finally 블록을 감싸고 있다.
	__try
	{
		__try
		{
			switch (sel)
			{
			case DIV:
				Divide(num1, num2);
				break;
			case MUL:
				Multiple(num1, num2);
				break;
			case ADD:
				Add(num1, num2);
				break;
			case MIN:
				Min(num1, num2);
				break;
			}
		}
		__finally
		{
			_tprintf(_T("End operation\n\n"));
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("Wrong number inserted. try again!\n\n"));
	}
	return TRUE;
}

void Divide(int a, int b)
{
	//b가 0이라면, 예외가 발생한다.
	//_tprintf함수가 호출되기 이전에, 전달되는 인자 a/b가 연산이 먼저 선행된다.
	//이 지점에서 예외가 발생하므로 더 이상의 실행을 중단하고 예외상황이 처리되어야 한다.
	//따라서 _tprintf 함수의 호출은 이루지지 않는다.
	_tprintf(_T("%d/%d=%d\n\n"), a, b, a / b);
}
void Multiple(int a, int b)
{
	_tprintf(_T("%d*%d=%d\n\n"), a, b, a * b);
}
void Add(int a, int b)
{
	_tprintf(_T("%d+%d=%d\n\n"), a, b, a + b);
}
void Min(int a, int b)
{
	_tprintf(_T("%d-%d=%d\n\n"), a, b, a - b);
}
