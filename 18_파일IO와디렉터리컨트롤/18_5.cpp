//������ Ư�� ���� ���� �� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");

	_tprintf(_T("Original file attributes\n"));
	DWORD attrib = GetFileAttributes(_T("data.txt"));
	ShowAttributes(attrib);

	attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	SetFileAttributes(_T("data.txt"), attrib);

	_tprintf(_T("Changed file attributes\n"));
	attrib = GetFileAttributes(_T("data.txt"));
	ShowAttributes(attrib);

	return 0;
}

//�� �Լ��� GetFileAttributes �Լ� ȣ�� �� ��ȯ�Ǵ� ���� ������ ���ڷ� ���޹ް�, ���޹��� ���� ������
//�м��Ͽ� �� ����� ����Ѵ�.
void ShowAttributes(DWORD attrib)
{
	//FILE_ATTRIBUTE_NORMAL�� �ٸ� Ư���� ������ �ǹ��ϹǷ� �̾ �ٷ� �������´�.
	//�� ������� ���Ͽ� ���ٸ� Ư�� ������ ������ ���� ������ ��Ÿ�� �� ���.
	//���� ���޵� ���ڿ� �� ������ ����ִٸ� �׳� �Լ��� ���� �������� ����.
	if (attrib & FILE_ATTRIBUTE_NORMAL)
	{
		_tprintf(_T("Normal\n"));
	}
	else
	{
		//���޵� ���� ������ ��� FILE_ATTRIBUTE_READONLY�� ��Ʈ ���� AND�����Ų��.
		//������ �б� �����̶�� ����� True�� �Ǿ� ����ȴ�.
		if (attrib & FILE_ATTRIBUTE_READONLY)
		{
			_tprintf(_T("Read Only\n"));
		}
		//���� ������ ���� Ư���� �����ϴ��� Ȯ���ϰ� �ִ�.
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
		{
			_tprintf(_T("Hidden\n"));
		}
		_tprintf(_T("\n"));
	}
}
