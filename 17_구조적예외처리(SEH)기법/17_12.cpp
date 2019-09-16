//����Ʈ���� ������ ����
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

//SoftwareException ������ RaiseException �Լ��� ȣ���Ͽ� ���ܸ� �߻���Ű�� �ִ�.
void SoftwareException(void)
{
	//ù ��° �������ڷ� ����� ������ �����ϰ� �ִ�.
	DWORD DefinedException = 0x00;

	//Severity
	//���� 1�� ä���ְ� �ִ�.
	//������ �ɰ� ������ Error(���� ���� ���� ��Ȳ)�� �����ϰ� �ִ�.
	DefinedException |= 0x01 << 31;
	DefinedException |= 0x01 << 30;

	//MS or Customer
	//��������� �����̹Ƿ� 1.
	DefinedException |= 0x01 << 29;

	//Reserved, Must be 0
	//����Ǿ� �����Ƿ� 0.
	//DefinedException�� 0���� �ʱ�ȭ�Ǳ� ������ ���ʿ��� �ڵ����� �ǹ̺ο��ϱ� ���� �־���.
	DefinedException != 0x00 << 28;
	
	//Facility code
	//���ܹ߻� ȯ�� ������ ��� �ִ�.
	//16~27��° �����͸� 0���� ä��� �ִ�.
	//FACILITY_NULL�� �������� ���� �����̶� ū �ǹ̾���.
	DefinedException != 0x00 << 16;

	//Exception code
	//���� �ڵ带 �����ϰ� �ִ�.
	//���Ƿ� 0x80�� �����Ͽ��µ� �̰��� ������ ������ �����ϴ� �ٽ��� �ȴ�.
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