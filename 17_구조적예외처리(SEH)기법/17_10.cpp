//EXCEPTION_CONTINUE_EXECUTION Ȱ�� ���
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
			//�� ��° �Է°� 0���� num2�� ä������ ���, ������ �߻�.
			//������ ������ ��� ������ �� ���� �ǰ�, ���Է��� �䱸�ϴ� �޽����� ����ϰ� �Է��� �ٽ� �޴´�.
		case DIV:
			//GetException�Լ��� EXCEPTION_INT_DIVIDE_BY_ZERO�� ��ȯ�Ѵ�.
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
	//�������� ǥ������ �ƴ� FilterFunction�̶�� �̸��� �Լ��� ȣ���ϰ� �ִ�.
	//GetExcetionCode �Լ��� ȣ���� ���� ����� ���� ������ ���ڷ� �����ϸ鼭 FilterFunction �Լ��� ȣ��.
	__except (FilterFunction(GetExceptionCode()))
	{
		_tprintf(_T("__except block...\n\n"));
	}
	return TRUE;
}

//�� �Լ��� ������ ������ ���� ��ȯ�ϴ� ���� ǥ������ �ٸ���.
//�� ������ ������ ���� ���ܰ� ó���Ǵ� ����� �޸��Ѵ�.
DWORD FilterFunction(DWORD exptType)
{
	switch (exptType)
	{
	//�� �κ��� ���ܰ� �߻��Ҹ��� �κ��� ����.
	case EXCEPTION_ACCESS_VIOLATION:
		_tprintf(_T("Access violation\n\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	//���ܰ� �߻��� ���ο� �ش��ϴ� num2�� ���� ���Է¹ް� �ִ�.
	//�׸��� EXCEPTION_CONTINUE_EXECUTION�� ��ȯ�Ѵ�.
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		_tprintf(_T("Wrong number inserted.\n"));
		_tprintf(_T("Input second number again:"));
		_tscanf(_T("%d"), &num2);
		return EXCEPTION_CONTINUE_EXECUTION;

	default:
		return EXCEPTION_EXECUTE_HANDLER;
	}
}