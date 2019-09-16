//���͸� ���� �����ϴ� ���� ����Ʈ ���
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR DirSpec[MAX_PATH];

	_tprintf(_T("Insert tartget directory:"));
	//�˻��ϰ��� �ϴ� ���͸� ������ �Է¹���.
	//"C:\Best"��� �ϸ� �� �ȿ� �����ϴ� ���ϰ� ���͸� �̸��� ��� ����ϰ��� �ϴ� ��.
	_tscanf(_T("%s"), DirSpec);
	//������� �ϴ� ���� ���͸��� ������ ��� �����ִ� ���α׷�.
	//*�� All�� �ǹ̸� �����ϴ� Wildcard ����.
	//"C:\Best\*"�� �ȴ�.
	//���� Ȯ���ڰ� exe�� ������ ���ϸ� �˻��ϱ� ���Ѵٸ� "C:\Best\*.exe"
	_tcsncat(DirSpec, _T("\\*"), 3);

	//���ǿ� �´� ù ��° ������ ã�� ������,
	hFind = FindFirstFile(DirSpec, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Invalid file handle\n"));
		return -1;
	}
	else
	{
		_tprintf(_T("First file name is %s\n"), FindFileData.cFileName);
		//�� ��° ���� ������ ã�� �ִ�.
		//FindNextFile �Լ��� ����� ã�� ���ϸ� 0�� ��ȯ�Ѵ�.
		//0�� ��ȯ�� ������ �� �Լ��� ȣ���ϹǷ�, ���ǿ� �´� ��� ������ ã�� �ȴ�.
		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			_tprintf(_T("Next file name is %s\n"), FindFileData.cFileName);
		}
		//�ڵ��� �ݾ� �ְ� �ִ�.
		FindClose(hFind);
	}
	return 0;
}