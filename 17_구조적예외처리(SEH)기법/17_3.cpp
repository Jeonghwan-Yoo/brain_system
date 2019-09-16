//종료 핸들러의 활용 예
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int ReadStringAndWrite(void);

int _tmain(int argc, TCHAR* argv[])
{
	int state = 0;
	while (1)
	{
		state = ReadStringAndWrite();
		if (state == -1)
		{
			_tprintf(_T("Some problem occurred!\n"));
			break;
		}
		if (state == 0)
		{
			_tprintf(_T("Graceful exit!\n"));
			break;
		}
	}
	return 0;
}

int ReadStringAndWrite(void)
{
	FILE* fPtr = NULL;
	TCHAR* strBufPtr = NULL;

	__try
	{
		//두 가지를 봐야한다.
		//하나는 파일의 개방(생성)이고, 개방하였으니 반드시 닫아줘야 한다.
		//또 다른 하나는 메모리의 해제이다.
		//문자열을 입력받기 위해 메모리를 동적 할당하고 있다.
		//따라서 반드시 해제해 줘야만 한다.
		//만약에 메모리 해제가 적절히 이뤄지지 않는다면 ReadStringAndWrite 함수가 반복적으로 호출되는
		//과정에서 해제되지 않은 메모리가 누적될 것이다.
		fPtr = _tfopen(_T("string.dat"), _T("a+t"));
		if (fPtr == NULL)
			return - 1;

		DWORD strLen = 0;
		_tprintf(_T("Input string length(0 to exit):"));
		_tscanf(_T("%d"), &strLen);

		if (strLen == 0) //정상적 종료
			return 0;

		strBufPtr = (TCHAR*)malloc((strLen + 1) * sizeof(TCHAR));
		if (strBufPtr == NULL)
			return -1;

		_tprintf(_T("Input string:"));
		_tscanf(_T("%s"), strBufPtr);

		_ftprintf(fPtr, _T("%s\n"), strBufPtr); //파일에 저장
	}
	__finally
	{
		//try블록으로 프로그램의 흐름이 진입되면 무조건 실행되는 영역이다.
		//파일 포인터와 할당된 메모리 포인터를 검사해서 종료하거나, 해제 작업이 필요한 경우에 해제하도록 구성.
		//만약에 종료 핸들러를 삽입하지 않았다면 위에 함수 마지막 부분에서 중복코드가 삽입되야 한다.
		if (fPtr != NULL)
			fclose(fPtr);

		if (strBufPtr != NULL)
			free(strBufPtr);
	}
	return 1;
}