#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex;
DWORD dwWaitResult;

//하는 일은 그저 "Thread Running!"이라는 문자열을 일정 시간 간격으로 총 5번 출력.
void ProcessBaseCriticalSection()
{
	//뮤텍스를 소유하려 한다.
	//사실 WaitForSingleObject와 같은 함수 호출 후 반환값을 통해 결과를 확인해야만한다.
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	//쓰레드가 뮤텍스를 소유했다.
	case WAIT_OBJECT_0:
		_tprintf(_T("thread got mutex !\n"));
		break;
	//time-out 발생했다.
	case WAIT_TIMEOUT:
		_tprintf(_T("timer expired !\n"));
		return;
	//뮤텍스 반환이 적절이 이뤄지지 않았다.
	//뮤텍스 소유자가 반환을 적절히 하지 않은 상황에서 반환되는 값.
	case WAIT_ABANDONED:
		return;
	}
	for (DWORD i = 0;i < 5;i++)
	{
		_tprintf(_T("Thread Running !\n"));
		Sleep(10000);
	}
	//함수를 빠져나가면서 소유한 뮤텍스를 반환하고 있다.
	ReleaseMutex(hMutex);
}

int _tmain(int argc, TCHAR* argv[])
{
//0을 1로 변경하고 컴파일을 하면, 뮤텍스를 생성하는 프로세스용 실행파일이 생성된다.
//0으로 변경하고 컴파일을 하면, 함수를 호출하는 실행파일이 생성된다.
#if 1
	//생성하는 뮤텍스는 "NamedMutex"라는 이름을 얻는다.
	//다른 어느 프로세스라도, 이 이름을 통해 뮤텍스 오브젝트에 접근하기 위한 핸들값을 얻을 수 있다.
	hMutex = CreateMutex(NULL, FALSE,
		_T("NamedMutex")); //named mutex
#else
	//이 함수는 이미 생성되어 있는 이름있는 뮤텍스의 핸들을 얻기 위해 사용되는 함수이다.
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS, //접근권한 요청
		FALSE, //핸들을 상속하지 않겠다.
		_T("NamedMutex") //뮤텍스 오브젝트 이름.
	);
#endif

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error:%d\n"), GetLastError());
		return -1;
	}
	ProcessBaseCriticalSection();

	CloseHandle(hMutex);
	return 0;
}