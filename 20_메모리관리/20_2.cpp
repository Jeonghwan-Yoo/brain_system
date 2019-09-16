//SEH 기반의 가상 메모리 컨트롤
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_PAGE 10 //할당할 최대 페이지 개수

int* nextPageAddr;
DWORD pageCnt = 0;
DWORD pageSize;
int PageFaultExceptionFilter(DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID baseAddr;
	int* lpPtr;
	SYSTEM_INFO sSysInfo;

	GetSystemInfo(&sSysInfo);
	pageSize = sSysInfo.dwPageSize; //페이지 사이즈 획득

	//MAX_PAGE의 개수만큼 페이지 RESERVE!
	//가상 메모리를 예약하고 있다.
	//이 때 반환된 값(예약된 메모리의 시작 번지)을 lpPtr, nextPageAddr에 저장하고 있다.
	baseAddr = VirtualAlloc(
		NULL, //임의 주소 할당
		MAX_PAGE*pageSize, //예약 메모리 크기
		MEM_RESERVE, //RESERVE!
		PAGE_NOACCESS //NO ACCESS
	);
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve railed"));

	//lpPtr은 배열 이름 역할을 위해(배열 이름 기반의 배열 인덱스 연산을 위해),
	//nextPageAddr은 COMMIT 상태로 만든 페이지의 위치 정보를 저장하기 위해 사용된다.
	//COMMIT 상태에 있는 페이지가 아무것도 없으니 예약된 메모리의 시작 번지로 초기화했다.
	lpPtr = (int*)baseAddr; //배열의 시작 번지와 같은 의미 부여
	nextPageAddr = (int*)baseAddr;

	//page fault 발생 시 예외발생
	for (int i = 0;i < (MAX_PAGE*pageSize) / sizeof(int);i++)
	{
		__try
		{
			//첫 번째 실행에서 배열의 첫 요소에 0을 채워 넣으려 한다.
			//문제는 해당 위치의 페이지가 현재 COMMIT 상태에 있지 않다는 것.
			//그래서 예외가 발생해 실행은 __except 문으로 옮김.
			lpPtr[i] = i;
		}
		//예외발생의 이유를 알 수 있는 예외코드 값을 얻어(GetExceptionCode), 이 값을 가지고 예외처리 함수
		//PageFaultExceptionFilter를 호출하고 있다.
		__except (PageFaultExceptionFilter(GetExceptionCode()))
		{
			ExitProcess(GetLastError()); //예외처리 문제 발생 시 종료!
		}
	}
	
	/*for (int i = 0;i < (MAX_PAGE*pageSize) / sizeof(int);i++)
		_tprintf(_T("%d "), lpPtr[i]);*/
	
	BOOL isSuccess = VirtualFree(
		baseAddr, //해제할 메모리의 시작 번지
		0,
		MEM_RELEASE); //FREE 상태로 변경
	if (isSuccess)
		_tprintf(_T("Release succeeded!"));
	else
		_tprintf(_T("Release failed!"));
}

int PageFaultExceptionFilter(DWORD exptCode)
{
	//예외의 원인이 'page fault'가 아니라면
	if (exptCode != EXCEPTION_ACCESS_VIOLATION)
	{
		_tprintf(_T("Exception code = %d\n"), exptCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	_tprintf(_T("Exception is a page fault\n"));

	if (pageCnt >= MAX_PAGE)
	{
		_tprintf(_T("Exception:out of pages\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}

	//물리 메모리에 할당이 이뤄지지 않아서 발생한 예외이므로 문제가 된 페이지를 COMMIT 상태로 변경하고 있다.
	//두 번째 전달인자인 페이지 크기는 이미 계산해 놓은 상태.
	LPVOID lpvResult = VirtualAlloc((LPVOID)nextPageAddr, pageSize, MEM_COMMIT, PAGE_READWRITE);
	if (lpvResult == NULL)
	{
		_tprintf(_T("VirtualAlloc failed %d\n"));
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		_tprintf(_T("Allocating another page.\n"));
	}

	pageCnt++;
	//그리고 COMMIT 상태에 있는 페이지의 위치 정보를 갱신하고 있다.
	nextPageAddr += pageSize / sizeof(int); //실수 주의!

	//page fault가 발생한 지점부터 실행을 계속
	//EXCEPTION_CONTINUE_EXECUTION을 반환하고 있다.
	//따라서 예외가 발생한 위치로 돌아가서 실행을 이어갈 것이다.
	return EXCEPTION_CONTINUE_EXECUTION;
}