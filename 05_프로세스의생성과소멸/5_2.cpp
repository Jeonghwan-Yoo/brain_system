//���� ���μ����� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	//����ü ������ ����� ���ÿ� 0���� �ʱ�ȭ.
	//�� ������ CreateProcess�Լ��� 9���� �����̰� �����ϴ� ���μ����� �Ӽ��� �����ϴ� �뵵.
	//�� 0���� �ʱ�ȭ�ؾ� �Ѵ�.
	STARTUPINFO si = { 0, };
	//PROCESS_INFORMATION����ü ������ ���� �����Ǵ� ���μ��� ���� ������ ��� ���� ���ȴ�.
	PROCESS_INFORMATION pi;

	//�����ϰ��� �ϴ� ���μ����� �Ӽ��� ����.
	si.cb = sizeof(si); //����ü ���� si�� ����Ʈ ���� ũ��� cb�� �ʱ�ȭ. Ȯ�强�� ����� ���.
	//si����ü ���� �� �ݿ��ڰ� �ϴ� ����鿡 ���� ������ ����.
	//STARTF_USEPOSITION�� ����ü ��� �߿��� dwX�� dwY�� ���� �����ؼ�, �����ϴ� ���μ��� ������ ��ġ�� ����.
	//dwX�� dwY�� ���� �־ dwFlags�� �������� ������ �ǹ̰� ����.
	//STARTF_USESIZE�� dwXSize�� dwYSize�� ���� ������ �����ϴ� ���μ��� ������ ũ�� ����.
	si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
	//�����ϴ� ���μ��� �ܼ��� ��ġ�� ũ�⸦ ����.
	si.dwX = 100;
	si.dwY = 200;
	si.dwXSize = 300;
	si.dwYSize = 200;
	//���μ��� �������� Ÿ��Ʋ �� ������ ������ �� ���ȴ�.
	//���μ����� �ܼ��� �ƴ϶� ������ ���μ����� ��쿡�� �ǹ̰� ����.
	si.lpTitle = const_cast<LPWSTR>(_T("I am a boy!"));

	//���������� �̸��� �������� ������ ���ڿ��� �����ϰ� �� ��° ���ڷ� ����.
	TCHAR command[] = _T("5_1.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	//���� ���͸� ������ �����ؼ� ���.
	GetCurrentDirectory(DIR_LEN, cDir); //���� ���͸� Ȯ��

	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	//���� ���͸� ����
	SetCurrentDirectory(_T("D:\source\repos\���ڱؽý���\05_���μ����ǻ������Ҹ�"));

	//���� ���͸� ���� �ٽ� ���.
	GetCurrentDirectory(DIR_LEN, cDir); //���� ���͸� Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	//ù ��° ���ڷ� NULL�� �����ϰ�, �� ��° ���ڸ� ���� �����Ϸ��� ���μ��� �̸� �������� �Բ� ����.
	//���� ��° ���ڴ� ���μ��� Ư���� �������� �� ���ȴ�.
	//CREATE_NEW_CONSOLE�� �����ϸ� ���Ӱ� �����ϴ� ���μ����� ���� �ܼ� �����찡 ���������� ����.
	//�������� ������(0�� ����), �θ� ���μ����� �ܼ� �����츦 �ڽ� ���μ����� �����ϰ� �ȴ�.
	//���� �����ϰ��� �ϴ� ���μ����� �ܼ��� ������� ���� �ʴ� ���α׷��̸� CONSOLE�ɼ��� �ǹ̰� ����.
	state = CreateProcess( //���μ��� ����
		NULL, //���������� �̸�
		command, //main�Լ��� ���޵� ���ڿ�
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