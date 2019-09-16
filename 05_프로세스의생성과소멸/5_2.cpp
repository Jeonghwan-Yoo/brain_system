//덧셈 프로세스를 생성
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	//구조체 변수를 선언과 동시에 0으로 초기화.
	//이 변수는 CreateProcess함수의 9번쨰 인자이고 생성하는 프로세스의 속성을 지정하는 용도.
	//꼭 0으로 초기화해야 한다.
	STARTUPINFO si = { 0, };
	//PROCESS_INFORMATION구조체 변수는 새로 생성되는 프로세스 관련 정보를 얻기 위해 사용된다.
	PROCESS_INFORMATION pi;

	//생성하고자 하는 프로세스의 속성을 지정.
	si.cb = sizeof(si); //구조체 변수 si의 바이트 단위 크기로 cb를 초기화. 확장성을 고려한 멤버.
	//si구조체 변수 중 반영코가 하는 멤버들에 대한 정보를 설정.
	//STARTF_USEPOSITION은 구조체 멤버 중에서 dwX와 dwY의 값을 참조해서, 생성하는 프로세스 윈도우 위치를 결정.
	//dwX와 dwY가 값이 있어도 dwFlags에 설정되지 않으면 의미가 없다.
	//STARTF_USESIZE은 dwXSize와 dwYSize의 값을 참조해 생성하는 프로세스 윈도우 크기 결정.
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	//생성하는 프로세스 콘솔의 위치와 크기를 설정.
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	//프로세스 윈도우의 타이틀 바 제목을 지정할 때 사용된다.
	//프로세스가 콘솔이 아니라 윈도우 프로세스일 경우에는 의미가 없다.
	si.lpTitle = const_cast<LPWSTR>(_T("I am a boy!"));

	//실행파일의 이름과 전달인자 정보를 문자열로 구성하고 두 번째 인자로 전달.
	TCHAR command[] = _T("5_1.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	//현재 디렉터리 정보를 추출해서 출력.
	GetCurrentDirectory(DIR_LEN, cDir); //현재 디렉터리 확인

	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	//현재 디렉터리 변경
	SetCurrentDirectory(_T("D:\source\repos\뇌자극시스템\05_프로세스의생성과소멸"));

	//현재 디렉터리 정보 다시 출력.
	GetCurrentDirectory(DIR_LEN, cDir); //현재 디렉터리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	//첫 번째 인자로 NULL을 전달하고, 두 번째 인자를 통해 생성하려는 프로세스 이름 정보까지 함께 전달.
	//여섯 번째 인자는 프로세스 특성을 결정지을 때 사용된다.
	//CREATE_NEW_CONSOLE를 전달하면 새롭게 생성하는 프로세스를 위한 콘솔 윈도우가 독립적으로 생성.
	//전달하지 않으면(0을 전달), 부모 프로세스의 콘솔 윈도우를 자식 프로세스가 공유하게 된다.
	//만약 생성하고자 하는 프로세스가 콘솔을 기반으로 하지 않는 프로그램이면 CONSOLE옵션은 의미가 없다.
	state = CreateProcess( //프로세스 생성
		NULL, //실행파일의 이름
		command, //main함수에 전달될 문자열
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi
	); //CreateProcess

	if (state != 0)
		_fputts(_T("Creation OK!\n"), stdout);
	else
		_fputts(_T("Creation Error!\n"), stdout);

	return 0;
}