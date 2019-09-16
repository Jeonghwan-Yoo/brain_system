//SEH ����� ���� �޸� ��Ʈ��
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_PAGE 10 //�Ҵ��� �ִ� ������ ����

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
	pageSize = sSysInfo.dwPageSize; //������ ������ ȹ��

	//MAX_PAGE�� ������ŭ ������ RESERVE!
	//���� �޸𸮸� �����ϰ� �ִ�.
	//�� �� ��ȯ�� ��(����� �޸��� ���� ����)�� lpPtr, nextPageAddr�� �����ϰ� �ִ�.
	baseAddr = VirtualAlloc(
		NULL, //���� �ּ� �Ҵ�
		MAX_PAGE*pageSize, //���� �޸� ũ��
		MEM_RESERVE, //RESERVE!
		PAGE_NOACCESS //NO ACCESS
	);
	if (baseAddr == NULL)
		_tprintf(_T("VirtualAlloc reserve railed"));

	//lpPtr�� �迭 �̸� ������ ����(�迭 �̸� ����� �迭 �ε��� ������ ����),
	//nextPageAddr�� COMMIT ���·� ���� �������� ��ġ ������ �����ϱ� ���� ���ȴ�.
	//COMMIT ���¿� �ִ� �������� �ƹ��͵� ������ ����� �޸��� ���� ������ �ʱ�ȭ�ߴ�.
	lpPtr = (int*)baseAddr; //�迭�� ���� ������ ���� �ǹ� �ο�
	nextPageAddr = (int*)baseAddr;

	//page fault �߻� �� ���ܹ߻�
	for (int i = 0;i < (MAX_PAGE*pageSize) / sizeof(int);i++)
	{
		__try
		{
			//ù ��° ���࿡�� �迭�� ù ��ҿ� 0�� ä�� ������ �Ѵ�.
			//������ �ش� ��ġ�� �������� ���� COMMIT ���¿� ���� �ʴٴ� ��.
			//�׷��� ���ܰ� �߻��� ������ __except ������ �ű�.
			lpPtr[i] = i;
		}
		//���ܹ߻��� ������ �� �� �ִ� �����ڵ� ���� ���(GetExceptionCode), �� ���� ������ ����ó�� �Լ�
		//PageFaultExceptionFilter�� ȣ���ϰ� �ִ�.
		__except (PageFaultExceptionFilter(GetExceptionCode()))
		{
			ExitProcess(GetLastError()); //����ó�� ���� �߻� �� ����!
		}
	}
	
	/*for (int i = 0;i < (MAX_PAGE*pageSize) / sizeof(int);i++)
		_tprintf(_T("%d "), lpPtr[i]);*/
	
	BOOL isSuccess = VirtualFree(
		baseAddr, //������ �޸��� ���� ����
		0,
		MEM_RELEASE); //FREE ���·� ����
	if (isSuccess)
		_tprintf(_T("Release succeeded!"));
	else
		_tprintf(_T("Release failed!"));
}

int PageFaultExceptionFilter(DWORD exptCode)
{
	//������ ������ 'page fault'�� �ƴ϶��
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

	//���� �޸𸮿� �Ҵ��� �̷����� �ʾƼ� �߻��� �����̹Ƿ� ������ �� �������� COMMIT ���·� �����ϰ� �ִ�.
	//�� ��° ���������� ������ ũ��� �̹� ����� ���� ����.
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
	//�׸��� COMMIT ���¿� �ִ� �������� ��ġ ������ �����ϰ� �ִ�.
	nextPageAddr += pageSize / sizeof(int); //�Ǽ� ����!

	//page fault�� �߻��� �������� ������ ���
	//EXCEPTION_CONTINUE_EXECUTION�� ��ȯ�ϰ� �ִ�.
	//���� ���ܰ� �߻��� ��ġ�� ���ư��� ������ �̾ ���̴�.
	return EXCEPTION_CONTINUE_EXECUTION;
}