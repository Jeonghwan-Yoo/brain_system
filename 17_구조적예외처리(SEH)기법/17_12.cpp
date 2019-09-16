//소프트웨어 예외의 생성
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SoftwareException(void);

int _tmain(int argc, TCHAR* argv[])
{
	SoftwareException();
	_tprintf(_T("End of the _tmain\n"));
	
	return 0;
}

//SoftwareException 내에서 RaiseException 함수를 호출하여 예외를 발생시키고 있다.
void SoftwareException(void)
{
	//첫 번째 전달인자로 사용할 변수를 선언하고 있다.
	DWORD DefinedException = 0x00;

	//Severity
	//각각 1을 채워주고 있다.
	//예외의 심각 수준을 Error(강도 높은 오류 상황)로 지정하고 있다.
	DefinedException |= 0x01 << 31;
	DefinedException |= 0x01 << 30;

	//MS or Customer
	//사용자정의 예외이므로 1.
	DefinedException |= 0x01 << 29;

	//Reserved, Must be 0
	//예약되어 있으므로 0.
	//DefinedException은 0으로 초기화되기 때문에 불필요한 코드지만 의미부여하기 위해 넣었다.
	DefinedException != 0x00 << 28;
	
	//Facility code
	//예외발생 환경 정보를 담고 있다.
	//16~27번째 데이터를 0으로 채우고 있다.
	//FACILITY_NULL로 지정으로 임의 지정이라 큰 의미없다.
	DefinedException != 0x00 << 16;

	//Exception code
	//예외 코드를 정의하고 있다.
	//임의로 0x80을 지정하였는데 이것이 예외의 종류를 구분하는 핵심이 된다.
	DefinedException |= 0x08;

	__try
	{
		_tprintf(_T("Send:exception code:0x%x\n"), DefinedException);
		RaiseException(DefinedException, 0, NULL, NULL);
	}

	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(_T("Recv:exception code:0x%x\n"), exptType);
	}
}