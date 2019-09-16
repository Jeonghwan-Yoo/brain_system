//파일의 특성 정보 참조 및 변경
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

//이 함수는 GetFileAttributes 함수 호출 시 반환되는 파일 정보를 인자로 전달받고, 전달받은 인자 정보를
//분석하여 그 결과를 출력한다.
void ShowAttributes(DWORD attrib)
{
	//FILE_ATTRIBUTE_NORMAL은 다른 특성이 없음을 의미하므로 이어서 바로 빠져나온다.
	//이 상수값은 파일에 별다른 특성 정보가 설정된 것이 없음을 나타낼 때 사용.
	//따라서 전달된 인자에 이 정보가 들어있다면 그냥 함수를 빠져 나가도록 구현.
	if (attrib & FILE_ATTRIBUTE_NORMAL)
	{
		_tprintf(_T("Normal\n"));
	}
	else
	{
		//전달된 파일 정보와 상수 FILE_ATTRIBUTE_READONLY를 비트 단위 AND연산시킨다.
		//파일이 읽기 전용이라면 결과는 True가 되어 실행된다.
		if (attrib & FILE_ATTRIBUTE_READONLY)
		{
			_tprintf(_T("Read Only\n"));
		}
		//파일 정보에 숨김 특성이 존재하는지 확인하고 있다.
		if (attrib & FILE_ATTRIBUTE_HIDDEN)
		{
			_tprintf(_T("Hidden\n"));
		}
		_tprintf(_T("\n"));
	}
}
