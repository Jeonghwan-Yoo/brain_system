//�̸��ִ� ������ ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024
int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	//���� Ŭ���̾�Ʈ�� ��� ���������� �� ������ �� Ŭ���̾�Ʈ�͸� ����!
	//�̸��ִ� �������� �����ϰ�, Ŭ���̾�Ʈ ���� ��û�� �����ϴ� ������ �ݺ�.
	while (1)
	{
		//��������� �а� ���� ���� �����ϵ� �޽��� ������� �����Ѵ�.
		//�Է� ���ۿ� ��� ������ ������� BUF_SIZE�̰�, Ƽ��Ʈ Ŭ���̾�Ʈ Ÿ�Ӿƿ��� 20�ʷ� ����.
		hPipe = CreateNamedPipe(
			pipeName, //������ �̸�
			PIPE_ACCESS_DUPLEX, //�б�, ���� ��� ����.
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //�޽��� ���
			PIPE_UNLIMITED_INSTANCES, //�ִ� ������ ����. ���� ������ �������� ����.
			BUF_SIZE, //��� ���� ������
			BUF_SIZE, //�Է� ���� ������
			20000, //Ŭ���̾�Ʈ Ÿ�Ӿƿ�
			NULL //����Ʈ ���� �Ӽ�
		);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreatePipe failed"));
			return -1;
		}

		BOOL isSuccess = 0;
		//Ŭ���̾�Ʈ�� ���� ��û�� �����ϴ� ������ �Ѵ�.
		//�̹� ��û�� ���� �ִ� ���¸� �ٷ� ��ȯ�Ǿ� �� ���� �۾��� ���������� 
		//��û�� ���� ���¶�� ���� ��û�� ���� ������ ���ŷ�ȴ�.
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

		if (isSuccess)
			CommToClient(hPipe);
		else
			CloseHandle(hPipe);
	}
	return 1;
}

//Ŭ���̾�Ʈ�� ������ �����Ǹ�, �̶� ���� ������ �ڵ��� �����ϸ鼭 �� �Լ��� ȣ��ȴ�.
//�����͸� �����ϴ� �Լ�(ReadFile), �����͸� �����ϴ� �Լ�(WriteFile)
//�������� ������ �����ϴ� �Լ�(FlushFileBuffers, DisconnedtNamedPipe)
int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile(
		hPipe, //������ �ڵ�
		fileName, //read ���� ����
		MAX_PATH * sizeof(TCHAR), //read ���� ������
		&fileNameSize, //������ ������ ũ��
		NULL
	);

	if (!isSuccess || fileNameSize == 0)
	{
		_tprintf(_T("Pipe read message error!\n"));
		return -1;
	}

	FILE* filePtr = _tfopen(fileName, _T("r"));
	if (filePtr == NULL)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile(
			hPipe, //������ �ڵ�
			dataBuf, //������ ������ ����
			bytesRead, //������ ������ ũ��
			&bytesWritten, //���۵� ������ ũ��
			NULL);
		
		if (bytesRead != bytesWritten)
		{
			_tprintf(_T("Pipe write message error!\n"));
			break;
		}
	}

	//������ ������ �����ϱ� ���ؼ� ���Ǵ� �Լ���.
	//��� ���۸� ���� ���ҷ� ���������� ������ �ǹ�.
	//�⺻������ Windows�� ���� �ý����� ������ ��κ��� ����� ��Ȳ���� ���۸��� �Ѵ�.
	//���� �̹� ���۵Ǿ��ٰ� �����Ǵ� �����͵��� �������� ��Ȳ�� ���� �������� �ý��� �޸𸮿� ���� ���� �� �ִ�.
	FlushFileBuffers(hPipe); 
	//Ŭ���̾�Ʈ�� ���� �޽����� ���� �� �ֵ��� �����ش�.
	//������ ������ ����� ����, Ŭ���̾�Ʈ�� ������ ���� �� ������ �߻��Ѵ�.
	//���� Ŭ���̾�Ʈ ���� �̿� ���� ������ ó���� ����������.
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}