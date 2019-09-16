//생성 가능한 쓰레드의 개수 측정
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_THREADS (1024*10)

//쓰레드의 main함수에 해당하는 쓰레드 함수를 정의하고 있다.
//쓰레드 함수의 타입은 반드시 이와 일치해야 한다.
//리턴 타입은 DWORD이고, 매개변수 타입은 LPVOID이어야 한다.
//쓰레드 함수 이름 앞에 있는 WINAPI는 함수 호출규약에 관련된 내용이다.
//쓰레드 생성 시 쓰레드 함수로 숫자하나를 전달하는데 이 숫자는 쓰레드가 생성된 순서를 의미한다.
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		_tprintf(_T("thread num : %d\n"), threadNum);
		//현재 실행 중인 프로세스를 잠시 멈추는 기능을 한다.
		//하지만 Windows는 쓰레드 중심의 운영체제이므로 실질적으론 호출하는 쓰레드를 잠시 멈추게 하는 것.
		//여기서는 실행의 속도를 늦추기 위한 용도
		Sleep(5000); 
	}
	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	//생성 가능한 최대 개수의 쓰레드 생성
	//계속해서 쓰레드를 생성하고 있다.
	//쓰레드 생성에 실패를 하면, 총 생성된 개수를 출력하고 break문에 의해 빠져나온다.
	while (1)
	{
		hThread[cntOfThread] = CreateThread(
			NULL, //디폴트 보안 속성 지정
			0, //디폴트 스택 사이즈
			ThreadProc, //쓰레드 함수
			(LPVOID)cntOfThread, //쓰레드 함수의 전달인자
			0, //디폴트 생성 flag지정
			&dwThreadID[cntOfThread] //쓰레드 ID 반환
		);
		//쓰레드 생성 확인
		if (hThread[cntOfThread] == NULL)
		{
			_tprintf(_T("MAXIMUM THREAD NUMBER : %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}
	for (DWORD i = 0;i < cntOfThread;i++)
	{
		//리소스 해제를 주문하고 있다.
		//쓰레드도 Windows내부적으로 커널 오브젝트 생성을 동반한다.
		//따라서 CloseHandle을 통해 리소스 해제를 주문해야 한다.
		CloseHandle(hThread[i]);
	}
	return 0;
}