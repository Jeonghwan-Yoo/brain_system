//�̸��ִ� ������ Ŭ���̾�Ʈ
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	//�������� �̸��� "\\servername\pipe\pipename"
	//Ŭ���̾�Ʈ�� ���� �̸��� ���ؼ� ���ݿ� �����ϴ� ��ǻ���� �������� ������ �Ѵ�.
	//�׷��� Ŭ���̾�Ʈ �ڵ��� ������ �̸� �������� ���� �̸��� �ʿ��ϴ�.
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	
	while (1)
	{
		//������ �����ϰų� �����ϴ� Windows �ý��� �Լ��̴�.
		//Ŭ���̾�Ʈ �������� ���� �� ���������� ���� ��û ��ɵ� ���Ѵ�.
		//ù��° �������ڸ� ���� ���� ����� ������ �̸��� �����Ѵ�.
		//�ι�° �������ڸ� ���� �б�, ���Ⱑ ���ÿ� �����ϵ��� ��带 ����.
		//���޵� ���� ���� ���� �� �б�, ���� ��带 ������ �� ���Ǵ� ������̴�.
		hPipe = CreateFile(
			pipeName, //������ ������ �̸�
			GENERIC_READ | GENERIC_WRITE, //�б�, ���� ��� ���� ����
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		//����Ǹ� while������ ���������� ���� �۾��� �����Ѵ�.
		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		//ERROR_PIPE_BUSY�� ���� ��û�� Pending(������ �������� ���� ��ٸ���)���¿� ���������� �ǹ��Ѵ�.
		//ERROR_PIPE_BUSY�� ��ȯ�Ǹ� ��� �� �ٽ� �õ��� ���� �Ѵ�.
		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}

		//���� ������ ���°� �Ǹ� TRUE�� ��ȯ�ϰڴ�.
		//���� ������ ���°� �� ������ ���ŷ ���¿� �ΰڴ�.
		if (!WaitNamedPipe(pipeName, 20000))
		{
			_tprintf(_T("Could not open pipe\n"));
			return 0;
		}
	}
	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT; //�޽��� ������� ��� ����
	//���������� ���� �Ӽ��� �����Ų��.
	//�������� ���� �� ���� ���� �Լ��� CreateFile�� ����ϴ� ���� ������ �ʿ��� ������ ������ �ݿ��� �� ����.
	//�׷��� �� �Լ��� ���� ���������� ���� �Ӽ��� ���ϴ� ��� �����Ű�� �߰����� �۾�.
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe, //���� �������� ����� �ڵ�
		&pipeMode, //������ ��� ����.
		NULL,
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("SetNamedPipeHandleState failed"));
		return 0;
	}

	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;

	//�������� ����� ���۵ȴ�.
	//�����ϰ��� �ϴ� ���ڿ� �����͸� ��� �ִ� ���� �̸��� �����Ѵ�.
	isSuccess = WriteFile(
		hPipe, //���� �������� ����� �ڵ�
		fileName, //������ �޽���
		(_tcslen(fileName) + 1) * sizeof(TCHAR), //�޽��� ����
		&bytesWritten, //���۵� ����Ʈ ��
		NULL);

	if (!isSuccess)
	{
		_tprintf(_T("WriteFile failed"));
		return 0;
	}

	DWORD bytesRead = 0;
	while (1)
	{
		//���޵� �����͸� �д´�.
		isSuccess = ReadFile(
			hPipe, //���� �������� ����� �ڵ�
			readDataBuf, //������ ������ ����
			BUF_SIZE * sizeof(TCHAR), //���� ������
			&bytesRead, //������ ����Ʈ ��
			NULL);
		//�������� �����͸� ������ �����ϰ� ������ ������ ���� ���, ���α׷��� �����ϰ� �ȴ�.
		//������ ������ ���ڿ��� ���̰� ReadFile�Լ����� ������ ������ ���̸� �ʰ��� ���, �� ����
		//��ü ���ڿ��� �о� ���� �� ���� ������ FALSE�� ��ȯ�ϸ鼭, GetLastError�Լ� ȣ���� �����
		//ERROR_MORE_DATA�� �ȴ�.
		//�̷� ��쿡�� ������ ���������� �ʰ� ������ �κ��� �б� ���� ����ϴ� �κ�.
		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;
		
		readDataBuf[bytesRead] = 0;
		_tprintf(_T("%s\n"), readDataBuf);
	}
	CloseHandle(hPipe);
	return 0;
}