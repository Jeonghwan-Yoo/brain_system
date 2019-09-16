//EXCEPTION_EXECUTE_HANDLER Ȱ�� ���
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
		//�� ��° �Է°� 0���� num2�� ä������ ���, ������ �߻�.
		//������ ������ ��� ������ �� ���� �ǰ�, ���Է��� �䱸�ϴ� �޽����� ����ϰ� �Է��� �ٽ� �޴´�.
		case DIV:
			result = num1 / num2;
			//0���� ������ �������� �ǹ̰� �������� ������ ���൵ �ǹ̸� �Ҵ´�.
			//�ǳ� �پ�� �߸��� ����� ������� �ʴ´�.
			//���α׷� �ڵ�� �� ���� �������� ���� �ٿ� �ǹ̸� �ο��ϴ� ��찡 ��κ��̴�.
			//�׷��� Ư�� ��ġ���� ���ܻ�Ȳ�� �߻��ϸ�, ���õ� ������ �κе� �ǳ� �� �ʿ䰡 �ִ�.
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