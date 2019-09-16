//프로그램 설명 : 예외의 구분!
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	int* p = NULL;
	int sel = 0;

	while (1)
	{
		_tprintf(_T("1 for memory access exception\n"));
		_tprintf(_T("2 for divide by 0 exception\n"));
		_tprintf(_T("Select exception type[3 for exit]:"));
		//입력받은 값에 따라 "메모리 참조 오류"나 "0으로 정수를 나누는 예외"가 발생.
		_tscanf(_T("%d"), &sel);

		if (sel == 3)
			break;

		__try
		{
			if (sel == 1)
			{
				*p = 100; //예외발생 지점
				_tprintf(_T("value:%d\n"), *p);			
			}
			else //sel == 2
			{
				int n = 0;
				n = 7 / n; //예외발생 지점
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			//이 함수는 현재 발생한 예외 정보를 반환해 준다.
			//정수형 데이터가 반환되는데, 이는 예외의 종류를 구분하기 위해 이미 정의된 값.
			DWORD exptType = GetExceptionCode();

			switch (exptType)
			{
			//EXCEPTION_ACCESS_VIOLATION는 메모리 참조 오류를 구분하기 위해 정의해 놓은 정수값이다.
			//EXCEPTION_INT_DIVIDE_BY_ZERO는 정수를 0으로 나누는 예외를 나타내기 위해 정의해 놓은 정수값.
			case EXCEPTION_ACCESS_VIOLATION:
				_tprintf(_T("Access violation\n\n"));
				break;
			case EXCEPTION_INT_DIVIDE_BY_ZERO:
				_tprintf(_T("Divide by zero\n\n"));
				break;
			}
		}
	}
	return 0;
}