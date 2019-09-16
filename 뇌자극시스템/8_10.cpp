//현재 실행 중인 프로세스 정보 출력
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <TlHelp32.h> //추가된 헤더파일

int _tmain(int argc, TCHAR* argv[])
{
	//Snapshot은 말 그대로 사진을 찍는 함수이다.
	//TH32CS_SNAPPROCESS는 현재 실행 중인 프로세스의 사진을 찍으라는 의미이다.
	//(사진을 찍는다는 것은 계속 변하는 프로세스 정보를 함수 호출 시점 기준으로 추출)
	//이 함수는 프로세스뿐만 아니라 프로세스가 사용하는 힙, 모듈, 그리고 쓰레드 사진도 찍을 수 있다.
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("CreateToolhelp32Snapshot error!\n"));
		return -1;
	}

	//프로세스 정보 얻기 위한 구조체 변수
	//찍은 사진을 살펴보면서 프로세스 정보를 추출할 준비.
	//이 구조체를 구성하는 멤버를 확인해 보면 어떤한 정보들을 얻을 수 있는지 알 수 있다.
	//변수 초기화는 반드시 필요하다.
	//첫 번째 프로세스 정보를 호출할 때는 Process32First함수를 호출한다.
	//두 번째 프로세스 정보부터는 Process32Next함수를 호출한다.
	//정보를 추출하는 형태가 문자열 토큰 나누는 방식과 유사하다.
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf(_T("Process32First error!\n"));
		CloseHandle(hProcessSnap);
		return -1;
	}

	HANDLE hProcess;
	do
	{
		//프로세스 이름, ID정보 출력
		_tprintf(_T("%25s %5d\n"), pe32.szExeFile, pe32.th32ProcessID);
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 0;
}