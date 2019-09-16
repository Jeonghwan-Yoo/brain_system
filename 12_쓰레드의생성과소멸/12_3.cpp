//쓰레드를 이용한 작업의 분할
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

//프로세스 유사 형태 쓰레드 생성
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD* nPtr = (DWORD*)lpParam;

	//쓰레드 함수 호출 시 두 개의 인자가 전달.
	//전달인자의 포인터를 적절히 변환해서 값을 취한다.
	//배열의 형태로 선언된 전달인자가 필요하다.
	DWORD numOne = *nPtr;
	DWORD numTwo = *(nPtr + 1);

	DWORD total = 0;
	for (DWORD i = numOne; i <= numTwo;i++)
	{
		total += i;
	}
	//결과값 반환
	//작업이 끝난 쓰레드가 종료됨과 동시에 결과값을 반환하는 상황.
	//이 결과값을 main쓰레드가 취할 수 있어야 한다.
	//자식 프로세스가 반환한 결과값(종료코드)을 부모 프로세스가 GetExitCodeProcess함수 호출을 통해 얻는다.
	//"쓰레드가 함수가 반환한 결과값은 프로세스의 종료코드처럼 커널 오브젝트에 그 결과가 저장된다."
	return total;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[3];
	HANDLE hThread[3];

	//쓰레드 생성 시 사용하게 될 전달인자를 배열로 구성
	DWORD paramThread[] = { 1,3,4,7,8,10 };
	DWORD total = 0;
	DWORD result = 0;

	//총 3개의 쓰레드가 생성되므로 거의 동시에 쓰레드 함수 ThreadProc가 호출된다.
	//같은 코드 영역을 실행하는 것은 맞지만 쓰레드마다 별도의 스택이 있고, 지역변수 total은
	//각각의 스택에 할당되므로 동시에 실행하게 된다고해 문제가 발생하지는 않는다.
	hThread[0] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[0]), 0, &dwThreadID[0]);
	hThread[1] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[2]), 0, &dwThreadID[1]);
	hThread[2] = CreateThread(NULL, 0, ThreadProc, (LPVOID)(&paramThread[4]), 0, &dwThreadID[2]);

	if (hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault!\n"));
		return -1;
	}

	//생성된 세 개의 쓰레드가 완전히 종료되기를 기다리고 있다.
	//종료시에 해당 커널 오브젝트가 Signaled상태가 된다.
	//main쓰레드의 종료는 프로세스의 종료로 이어진다.
	//만약에 프로세스가 종료되면 각자 역할을 담당하는 쓰레드들은 자신의 일을 마치기도 전에 소멸되고 만다.
	//그렇게 되면 출력결과는 엉망이 된다.
	WaitForMultipleObjects(
		3, //총 3개의 커널 오브젝트를 관찰
		hThread, //커널 오브젝트 핸들의 배열 정보
		TRUE, //모든 커널 오브젝트가 signaled 상태가 되기를 
		INFINITE //영원히 기다린다.
	);

	//쓰레드의 종료코드를 얻기 위해 사용되는 함수.
	//종료코드가 등록되면서부터 얻게 되기까지의 과정은 프로세스의 종료코드를 얻는 과정과 동일.
	GetExitCodeThread(hThread[0], &result);
	total += result;

	GetExitCodeThread(hThread[1], &result);
	total += result;

	GetExitCodeThread(hThread[2], &result);
	total += result;

	_tprintf(_T("total (1~10) : %d\n"), total);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	CloseHandle(hThread[2]);
	return 0;
}