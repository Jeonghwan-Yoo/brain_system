//MMF�� ���� �˰���
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SortIntData(int* pSortArr, int num);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hFile = CreateFile(_T("data.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		_tprintf(_T("Could not open file."));

	//�����ϰ��� �ϴ� �޸��� �ִ� ũ�⸦ 10KB�� �����ϰ� �ִ�.
	//MMF�� ����Ǵ� �޸� ũ��� ���⼭ �����ϴ� ���̻����� �������� �ʴ´�.
	//���� 0�� �����Ѵٸ� ���� ������ ũ�Ⱑ 0�̹Ƿ�(�ƹ� �����Ͱ� ���� ����), MMF �ִ� ũ��� 0���� �����ȴ�.
	//�޸𸮿� ���� ������ �ִ� ũ�Ⱑ 0����Ʈ��� ���� �����Ű�� �ʰڴٴ� ���̾ ������ �߻�.
	//�׷��� ��������� ���� ������ �ִ� ũ�⸦ ������ ��߸� �Ѵ�.
	//������ ������ �������� �ʵ��� �˳��ϰ� ũ�⸦ �����ؾ� �Ѵ�.
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE,
		0, //���� ������ �ִ� �޸� ũ��, ���� 4����Ʈ
		1024 * 10, //���� ������ �ִ� �޸� ũ��, ���� 4����Ʈ
		NULL);
	if (hMapFile == NULL)
		_tprintf(_T("Could not create map of file.\n"));

	int* pWrite = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pWrite == NULL)
		_tprintf(_T("Could not map view of file.\n"));

	pWrite[0] = 1, pWrite[1] = 3, pWrite[2] = 0;
	pWrite[3] = 2, pWrite[4] = 4, pWrite[5] = 5;
	pWrite[6] = 8, pWrite[7] = 6, pWrite[8] = 7;

	//MMF�� �����͸� ���ڷ� �����ϸ鼭 ������ ������ �䱸�ϰ� �ִ�.
	//�� �˰����� ���Ͽ� ����� �����͸� ������� �����ϰ� �ȴ�.
	SortIntData(pWrite, 9);

	_tprintf(_T("%d %d %d\n"), pWrite[0], pWrite[1], pWrite[2]);
	_tprintf(_T("%d %d %d\n"), pWrite[3], pWrite[4], pWrite[5]);
	_tprintf(_T("%d %d %d\n"), pWrite[6], pWrite[7], pWrite[8]);

	UnmapViewOfFile(pWrite);
	CloseHandle(hMapFile);

	CloseHandle(hFile);
	_tprintf(_T("End of process!\n"));
	return 0;
}

void SortIntData(int* pSortArr, int num)
{
	//bubble sort
	int temp;

	for (int i = 0;i < num - 1;i++)
	{
		for (int j = 1;j < num - i;j++)
		{
			if (pSortArr[j - 1] > pSortArr[j])
			{
				temp = pSortArr[j - 1];
				pSortArr[j - 1] = pSortArr[j];
				pSortArr[j] = temp;
			}
		}
	}
}