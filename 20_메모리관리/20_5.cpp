//MMF와 정렬 알고리즘
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

	//연결하고자 하는 메모리의 최대 크기를 10KB로 지정하고 있다.
	//MMF로 연결되는 메모리 크기는 여기서 지정하는 값이상으로 증가하지 않는다.
	//따라서 0을 전달한다면 현재 파일의 크기가 0이므로(아무 데이터가 없는 상태), MMF 최대 크기는 0으로 설정된다.
	//메모리에 연결 가능한 최대 크기가 0바이트라는 것은 연결시키지 않겠다는 뜻이어서 오류가 발생.
	//그래서 명시적으로 연결 가능한 최대 크기를 지정해 줘야만 한다.
	//지정할 때에도 부족하지 않도록 넉넉하게 크기를 지정해야 한다.
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE,
		0, //파일 연결의 최대 메모리 크기, 상위 4바이트
		1024 * 10, //파일 연결의 최대 메모리 크기, 하위 4바이트
		NULL);
	if (hMapFile == NULL)
		_tprintf(_T("Could not create map of file.\n"));

	int* pWrite = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pWrite == NULL)
		_tprintf(_T("Could not map view of file.\n"));

	pWrite[0] = 1, pWrite[1] = 3, pWrite[2] = 0;
	pWrite[3] = 2, pWrite[4] = 4, pWrite[5] = 5;
	pWrite[6] = 8, pWrite[7] = 6, pWrite[8] = 7;

	//MMF의 포인터를 인자로 전달하면서 데이터 정렬을 요구하고 있다.
	//이 알고리즘은 파일에 저장된 데이터를 기반으로 동작하게 된다.
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