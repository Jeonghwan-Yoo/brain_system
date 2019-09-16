//_beginthreadex 함수 기반으로 변경
#include <stdio.h>
#include <tchar.h>
#include <process.h> //_beginthreadex함수가 선언되어 있는 헤더파일.
#include <Windows.h>

#define MAX_THREADS (1024*10)

//쓰레드 함수의 반환값을 DWORD에서 unsigned int(UINT)로 변경
//.c라면 그냥 DWORD로 둔다.
//타입 검사가 보다 엄밀이 진행되다 보니 컴파일 시 오류가 발생한다.
unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)
	{
		_tprintf(_T("thread num : %d\n"), threadNum);
		Sleep(1000);
	}
	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	//생성 가능한 최대 개수의 쓰레드 생성
	while (1)
	{
		//HANDLE과 unsigned*로 형변환하고 있다.
		hThread[cntOfThread] = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, (LPVOID)cntOfThread,
			0, (unsigned*)&dwThreadId[cntOfThread]);

		//쓰레드 생성 확인
		if (hThread[cntOfThread] == NULL)
		{
			_tprintf(_T("MAXIMUM THREAD SIZE : %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}
	for (DWORD i = 0;i < cntOfThread;i++)
	{
		CloseHandle(hThread[i]);
	}
	return 0;
}