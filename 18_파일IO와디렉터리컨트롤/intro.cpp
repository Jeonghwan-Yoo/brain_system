/*
01 기본적인 파일 처리 함수들
Windows에서 제공하는 파일 관련 시스템 함수들은 ANSI에서 정의하는 것보다 많은 기능을 제공한다.
이러한 기능을 활용하기 위해서는 Windows 기반 파일 입출력 함수들도 알아야 한다.
그러나 단순히 파일에 데이터를 쓰고 읽는 것이 전부라면, ANSI 표준 함수의 선택이 호환성 측면에서 더 좋다.

파일 열기 & 닫기
파일을 열 때에는 다음 함수를 활용한다.
HANDLE CreateFile (
	LPCTSTR lpFileName, 1)
	DWORD dwDesiredAccess, 2)
	DWORD dwShareMode, 3)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, 4)
	DWORD dwCreationDisposition, 5)
	DWORD dwFlagsAndAttributes, 6)
	HANDLE hTemplateFile 7)
);
If the function fails, the return value is INVALID_HANDLE_VALUE. 8)
1)lpFileName:개방할 파일 이름을 지정한다.
2)dwDesiredAccess:읽기/쓰기 모드를 지정한다. or(|)연산으로 결합 가능.
GENERIC_READ:읽기 모드 지정
GENERIC_WRITE:쓰기 모드 지정
3)dwShareMode:파일 공유방식을 지정한다.
0:다른 프로세스에 절대 공유 불가. 이미 개방된 파일은 중복 개방 불가.
FILE_SHARE_READ:다른 프로세스에서 이 파일에 동시 읽기 접근 가능.
FILE_SHARE_WRITE:다른 프로세스에서 이 파일에 동시 쓰기 접근 가능. 단 동시에 같은 영역에 데이터를 쓰는 문제를
피해야 함.
4)lpSecurityAttributes:보안 속성을 지정한다. 핸들을 자식 프로세스에게 상속할 것인지 말 것인지를 결정하기 위한
용도로 사용할 수 있다. 디폴트 보안 속성을 지정하고자 하는 경우 NULL을 전달한다.
5)dwCreationDisposition:파일이 생성되는 방법을 지정한다.
CREATE_ALWAYS:항상 새 파일을 생성한다.
CREATE_NEW:새 파일 생성, 같은 이름의 파일이 존재하면 생성 실패.
OPEN_ALWAYS:기존 파일 개방, 없으면 새로 생성.
OPEN_EXISTING:기존 파일 개방, 없으면 함수 호출 실패.
TRUNCATE_EXISTING:기존 파일의 내용 지우고 개방, 파일이 존재하지 않으면 호출 실패.
6)dwFlagsAndAttributes:파일의 특성 정보를 설정한다. 둘 이상의 특성 정보다 OR(|)연산자를 통해 지정될 수 있으며,
기본적으로는 FILE_ATTRIBUTE_NORMAL이라는 값을 사용한다. 이는 특별한 특성을 지정하지 않은 보통 파일임을 의미한다.
이외에도 지정할 수 있는 값들이 많다.
7)hTemplateFile:기존에 존재하는 파일과 동일한 특성을 가지는 새 파일을 만들 때 사용되는 전달인자이다.
Windows ME/98/95에서는 이 전달인자를 지원하지 않기 때문에 일반적으로 NULL을 전달한다.
8)끝으로 함수 호출이 성공하면, 파일의 핸들이 반환된다.

파일을 종료할 때에는 마찬가지로 Closehandle 함수를 호출하면 된다.
파일을 개방할 때에도 커널 오브젝트가 생성되고, 핸들이 반환된다.
CreateFile 함수는 핸들을 반환한다.
함수 호출을 통해 생성되는 커널 오브젝트에는 파일에 대한 정보로 가득 차있다.

파일 읽기 & 쓰기와 포인터
파일에 데이터를 읽을 때에는 다음 함수를 사용한다.
BOOL ReadFile (
	HANDLE hFile, 1)
	LPVOID lpBuffer, 2)
	DWORD nNumberOfBytesToRead, 3)
	LPDWORD lpNumberOfBytesRead, 4)
	LPOVERLAPPED lpOverlapped 5)
);
If the function fails, the return value is 0.
1)hFile:데이터를 읽을 파일의 핸들을 지정한다.
2)lpBuffer:읽어 들인 데이터를 저장할 버퍼(배열, 메모리)의 주소(포인터)를 지정한다.
3)nNumberOfBytesToRead:파일로부터 읽고자 하는 데이터의 크기를 바이트 단위로 지정한다.
4)lpNubmerOfBytesRead:실제 읽어 들인 데이터 크기를 얻기 위한 변수의 주소를 지정한다.
5)lpOverLapped.

파일에 데이터를 저장할 때에는 다음 함수를 사용한다.
BOOL WriteFile (
	HANDLE hFile, 1)
	LPCVOID lpBuffer, 2)
	DWORD nNumberOfBytesToWrite, 3)
	LPDWORD lpNumberOfBytesWritten, 4)
	LPOVERLAPPED lpOverlapped 5)
);
If the function fails, the return value is zero.
1)hFile:데이터를 저장할 파일의 핸들을 지정한다.
2)lpBuffer:데이터를 저장하고 있는 버퍼(배열, 메모리)의 주소(포인터)를 지정한다.
3)nNumberOfBytesToWrite:파일에 저장하고자 하는 데이터 크기를 바이트 단위로 지정한다.
4)lpNumberOfBytesWritten:파일에 실제 저장된 데이터 크기를 얻기 위해 변수의 주소를 지정한다.
5)lpOverLapped.

파일을 열어서 읽고 쓰고 닫는 예제
18_1.cpp UNICODE_BASE_FILE_IO.cpp
18_2.cpp UNICODE_BASE_FILE_READ.cpp

파일의 시간 정보 얻어오기
Windows에서 파일 정보의 확인이 가능하다.
만든 날짜, 수정한 날짜(마지막으로), 액세스한 날짜(마지막으로) 등등.
위와 같은 정보를 얻기 위해, 변경하기 위해선 다음 함수를 사용한다.
BOOL GetFileTime (
	HANDLE hFile, 1)
	LPFILETIME lpCreationTime, 2)
	LPFILETIME lpLastAccessTime, 3)
	LPFILETIME lpLastWriteTime 4)
);
If the function fails, the return value is zero.
1)hFile:시간 관련 정보를 얻을 대상 파일의 핸들을 지정한다.
2)lpCreationTime:파일이 생성된 시간을 얻기 위해 FILETIME 구조체 변수의 주소값을 전달한다. NULL 전달도 가능.
3)lpLastAccessTime:파일의 마지막 접근 시간을 얻기 위해 FILETIME 구조체 변수의 주소값을 전달한다. NULL 전달도 가능.
4)lpLastWriteTime:파일의 마지막 데이터 갱신(덮어 쓰기 포함) 시간을 얻기 위해 FILETIME 구조체 변수의 주소값을
전달한다. NULL 전달도 가능.

두 번째, 세 번째 그리고 네 번째 전달인자는 FILETIME 구조체 변수의 포인터인데, 다음과 같이 선언되어 있다.
typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME;
FILETIME 구조체는 시간 정보를 나타내는 8바이트 자료형(DWORD*2)이다. 그리고 이 구조체는 UTC 기반으로 시간표현.
GetFileTime 함수는 UTC 기반으로 시간 정보를 돌려 준다.

UTC란 Coordinated Universal Time으로 세계 시간의 기준을 만들기 위해 정의된 시간.
이것은 1601년 1월 1일을 기준으로 100나노초 단위 기준으로 지나간 시간을 계산.
시, 분, 초는 생략하고 UTC는 [2007, 01, 01]-[1601, 01, 01]을 100나노초 단위로 환산한 값이 UTC다.
지금도 유지되고 있고, 정밀도를 최대한 높이기 위해 Atomic Clocks를 사용.
정밀도가 중시되는 분야에선 대부분 UTC 기반.
그리고 우리가 원하는 타입으로 시간 정보를 변경하는 함수를 제공한다.
GetFileTime 함수의 호출을 통해 파일의 시간 정보를 추출하고 시간 정보 스케일로 변환하는 과정.
18_3.cpp FileTimeInformation.cpp
FileTimeToSystemTIme 함수의 호출로 변경되는 것은 단지 포맷이다(시간 정보는 여전히 UTC기준).
변경되는 포맷을 이해하기 위해 SYSTEMTIME 구조체의 선언 형태는
typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME;
파일의 시간 정보를 얻고자 할 때 참조하면 그만큼 시간 소모를 줄일 수 있다.
SetFileTime 함수를 이용하면 파일의 시간 정보를 변경할 수도 있다.

파일 사이즈 얻어오기
ANSI표준 함수에서는
FILE* fp = fopen("test.dat", "rb");
fseek(fp, 0, SEEK_END);
DWORD sizeOfFile = ftell(fp);
fseek 함수로 파일 포인터를 끝으로 이동시킨 다음, ftell 함수를 호출해 현재 위치 정보를 얻어온다.
파일 포인터를 끝으로 이동시켰기 때문에 현재 위치 정보는 파일의 크기가 된다.
다소 번거롭다.
Windows 시스템 함수는 파일 크기를 직접 계산해서 반환하는 함수를 제공한다.
DWORD GetFileSize (
	HANDLE hFile, 1)
	LPDWORD lpFileSizeHigh 2)
);
If the function fails and lpFileSizeHigh is non-NULL, the return value is INVALID_FILE_SIZE.
1)hFile:파일 핸들을 지정한다. 이 핸들이 가리키는 파일의 크기 정보를 얻게 된다.
2)lpFileSizeHigh:반환 타입을 보면 4바이트 DWORD로 선언되어 있다. 따라서 4GB 이상의 파일 크기를 반환값으로
얻는 것은 불가능하다. 4GB이상 되는 파일의 크기를 얻을 때 사용되는 것이 두 번째 전달인자이다.
이 전달인자를 통해 크기가 4GB를 넘는 파일의 상위 4B 정보를 얻을 수 있다.

GetFileSize 함수는 4GB 이상의 파일에 대해 상위 4B와 하위 4B를 각각 다른 경로를 통해 얻어야 한다.
불편하다면 다음 함수의 사용을 고려해 볼 수 있다.
BOOL GetFileSizeEx (
	HANDLE HFile, 1)
	PLARGE_INTEGER lpFileSize 2)
);
If the function fails, the return value is zero.
1)hFile:크기를 얻고자 하는 파일의 핸들을 지정한다.
2)lpFileSize:파일 크기를 저장하기 위한 변수의 포인터(주소값)을 인자로 전달한다. PLARGE_INTEGER는 
LARGE_INTEGER의 포인터 타입이고, LARGE_INTEGER는 다음과 같이 선언되어 있다.
중요한 사실은 4바이트가 아닌 8바이트 자료형이라는 것.
typedef union _LARGE_INTEGER
{
	struct {
		DWORD LowPart;
		LONG HighPart;
	};
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
18_4.cpp GetFileSize.cpp
공용체에 대해 공부해보고, LARGE_INTEGER를 참조하면 이해할 수 있다.
단 GetFileSizeEx 함수는 Windows 2000이나 WindowsXP 이상에서만 지원되는 함수.
GetFileSize 함수를 활용해 하위 버전에 대한 호환성을 유지할 수도 있다.
DWORD high4ByteFileSize = 0;
LONGLONG fileSize = GetFileSize(hFile, &high4ByteFileSize);
fileSize = fileSize | ((LONGLONG)high4ByteFileSize << 32);
LONGLONG타입 대신 LARGE_INTEGER를 대신 사용할 수도 있다.

파일 특성(Attribute) 정보 얻어오기
파일 특성 정보는 파일을 지정한 다음에 마우스 오른쪽 버튼을 누른 후 속성을 선택하면 볼 수 있다.
이러한 특성 정보는 프로그램 코드상에서 변경 및 확인이 가능하다.
DWORD GetFilettributes (
	LPCTSTR lpFileName 1)
);
If the function fails, the return value is INVALID_FILE_ATTRIBUTES.
1)lpFileName:특성 정보를 얻고자 하는 파일의 핸들을 지정한다. 파일의 특성 정보는 반환값을 통해서 얻게 된다.

위 함수의 호출을 통해 DWORD형 반환값을 얻을 수 있다.
이 안에 파일 특성에 대한 정보들이 모두 들어있다.
하나의 값에 여러 정보가 담겨있다보니, 비트 단위로 의미가 부여되어 있다.
|  ...|8| | | |4| | | |0|
FILE_ATTRIBUTE_HIDDEN┘ └FILE_ATTRIBUTE_READONLY
자료형의 첫 번째 비트(오른쪽에서)가 1인 경우에 해당하는 값 0x00000001을 읽기 전용 특성 정보를 표현하는데 사용.
즉 반환값이 인덱스 기준 0번째 비트가 1로 설정되어 있으면, 그 파일은 읽기 전용인 것.
두 번째 인덱스 비트가 1인 경우에 해당하는 값 0x00000002는 숨김 특성 정보를 표현하는데 사용.
프로그램 구현의 용이성을 위해 읽기 전용 특성과 숨김 특성을 매크로 상수로 정의해 놓고 있다.
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
파일이 가질 수 있는 특성 정보의 종류는 이것 외에도 12가지 정도가 더 있다.

BOOL SetFileAttributes (
	LPCTSTR lpFileName, 1)
	DWORD dwFileAttributes 2)
);
If the funciton fails, the return value is zero.
1)lpFileName:특성 정보를 변경하고픈 파일의 핸들을 지정한다.
2)dwFileAttributes:변경할 특성 정보를 전달한다.

18_5.cpp Set_Get_FileAttributes.cpp
현재 파일 정보를 얻은 다음, 기존 파일 정보에다가 읽기 전용과 숨김 특성 정보를 더해 파일 특성을 변경한다.
물론 파일 특성 자체가 변하는 것.
그리고 변경된 상태를 확인한다.
GetFileAttributes함수와 SetFileAttributes함수는 일반적인 파일 처리 함수와 차이를 보인다.
그것은 파일 핸들을 필요로 하지 않는다는 점.
대신 위치경로(절대경로나 상대경로)를 포함하는 파일의 이름을 필요로 한다.
이는 유용할 때도 있지만 제한을 가져다 준다.
사실 파일의 이름보다는 파일의 핸들을 활용해야 하는 상황이 훨씬 더 많다.

파일의 특성(Attribute) 정보 핸들로부터 얻어오기 + a
원하는 것은 핸들을 이용해서 파일 정보를 얻어 오는 것.
실제로 핸들을 이용해 파일 정보를 얻기 위해 사용되는 함수가 있다.
BOOL GetFileInformationByHandle (
	HANDLE hFile, 1)
	LPBY_HANDLE_FILE_INFORMATION lpFileInformation 2)
);
If the function fails, the return value is zero.
1)hFile:정보를 얻고자 하는 파일의 핸들을 지정한다.
2)LPBY_HANDLE_FILE_INFORMATION:구조체 BY_HANDLE_FILE_INFORMATION의 포인터 타입이다.
여기로 전달되는 주소의 변수에 파일 정보가 채워진다.

이 함수를 통해 얻는 정보는 파일의 특성 정보뿐 아니라 시간 정보와 파일의 크기 정보를 비롯해 추가적인 파일 시스템
정보들도 얻을 수 있다.
그래서 이 함수의 호출은 GetFileTime와 GetFileSize함수의 호출을 대신할 수 있다.
typedef struct _BY_HANDLE_FILE_INFORMATION
{
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD dwVolumeSerialNumber;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD nNumberOfLinks;
	DWORD nFileIndexHigh;
	DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *BY_HANDLE_FILE_INFORMATION;
18_6.cpp GetFileInformationByHandle.cpp

파일의 경로(Path) 정보 얻어오기
파일 정보 얻기 시리즈 마지막 단계로 파일 이름을 통해 파일경로 정보를 얻어야 할 때 사용하는 함수를 소개.
DWORD GetFullPathName (
	LPCTSTR lpFileName, 1)
	DWORD nBufferLength, 2)
	LPTSTR lpBuffer, 3)
	LPTSTR* lpFilePart 4)
);
If the function fails, the return value is 0.
1)lpFileName:완전경로(Full Path)를 확인하고자 하는 파일 이름을 전달한다.
2)nBufferLength:완전경로를 저장할 버퍼에 저장 가능한 문자열 길이를 지정한다. 버퍼의 바이트 단위 크기가 아닌
저장 가능한 문자열의 길이이다.
3)lpBuffer:완전경로를 저장할 버퍼의 주소값을 지정한다.
4)lpFilePath:완전경로가 문자열로 버퍼에 저장된 이후, 버퍼의 특정 위치를 가리키는 포인터 값이 저장.
마지막 역 슬래쉬(\) 다음 번지 주소값이 저장된다.
18_7.cpp GetFullPathName.cpp

파일 포인터의 이동 - 32비트 기반
ANSI 표준 함수 fseek에 해당하는 Windows 시스템 함수인 SetFilePointer.
64비트 환경까지 고려한 상황에서(4GB 이상의 대용량 파일을 고려한 상황), 이 함수를 사용하려면 별도의 번거로운
일을 고려해야만 한다.
DWORD SetFilePointer (
	HANDLE hFile, 1)
	LONG lDistanceToMove, 2)
	PLONG lpDistanceToMoveHigh, 3)
	DWORD dwMoveMethod 4)
);
If the function fails and lpDistanceToMoveHigh is NULL, the return value is INVALID_SET_FILE_POINTER.
1)hFile:파일 포인터 위치를 이동시킬 대상 파일의 핸들을 지정한다.
2)lDistanceToMove:이동시킬 거리를 지정한다. 만약에 64비트 기반으로 구현하면 하위 4바이트 정보를 표현하게 된다.
3)lDistanceToMoveHigh:64비트 기반의 대용량 파일에서만 의미를 지닌다. 상위 4바이트 정보를 표현하게 된다.
32비트 기반에서는 NULL을 전달한다.
4)dwMoveMethod:파일 포인터 이동 시 기준이 되는 위치를 지정한다. 파일의 가장 앞부분을 기준으로 설정하고 할 때에는
FILE_BEGIN을 인자로 전달한다. fseek 함수의 SEEK_SET에 해당한다. 파일 포인터의 현재 위치를 기준으로 설정하고자
할 때에는 FILE_CURRENT를 인자로 전달한다. fseek 함수의 SEEK_CUR에 해당한다. 파일의 가장 마지막 부분을
기준으로 할 때에는 FILE_END를 인자로 전달한다. fseek 함수의 SEEK_END에 해당한다.

32비트 시스템에서 4GB를 넘지 않는 파일을 다룰 때.
18_8.cpp SetFilePointer_32BIT_VERSION.cpp
실제론 최대 (2^32-2)B크기의 파일까지 지원가능 하다.
SetFilePointer는 함수 호출 성공 시 변경된 위치의 파일 포인터값을 반환한다.
물론 파일 포인터 위치 중에서 아래 4바이트에 해당하는 값을 반환한다.
오류 발생시 반환되는 값 INVALID_SET_FILE_POINTER는 -1이고 32비트로 표현하면 0xFFFFFFFF, 2^32-1이다.
파일 포인터 위치가 0이라면 0x00000000을 반환할 것이고, 4GB이고, 파일 포인터가 SetFilePointer 함수 호출을
통해서 이 파일의 끝을 가리키게 되었다면 2^32-1이 반환된다.
그런데 2^32-1은 10진수로 -1에 해당하기 때문에, INVALID_SET_FILE_POINTER와 구분할 방법이 없다.
그래서 결국 크기가 딱 4GB인 경우에는 대용량 파일로 간주하고 다른 방식을 지원.
그래서 32비트 기반에서 지원 가능한 최대 파일 크기가 2^32-2인 것.

파일 포인터의 이동 - 64비트 기반
18_9.cpp SetFilePointer_64BIT_VERSION.cpp
32비트기반(4GB를 안넘는) 오류검사 코드
if (dwPtr == INVALID_SET_FILE_POINTER) {}
64비트기반(4GB 이상) 오류검사 코드
if ((dwPtrLow == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR)) {}
64비트 기반에서는 GetLastError를 통해 정말 오류가 발생하는지 확인.
4GB 이상의 대용량 파일을 다루기 때문에 파일의 위치가 2^32-1의 위치에 놓일 수 있다.
그러면 파일 포인터 위치는 0xFFFFFFFF가 되는데 INVALID_SET_FILE_POINTER와 동일하다.
그래서 SetFilePointer 함수의 반환값만을 가지고 오류 발생 유무를 확인할 수 없다.
반드시 GetLastError 함수 호출을 통해서 반환값의 의미를 정확히 파악해야 한다.

02 디렉터리 관련 함수 및 그밖의 함수들
디렉터리의 생성과 소멸
BOOL CreateDirectory (
	LPCTSTR lpPathName, 1)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes 2)
);
If the function fails, the return value is zero.
1)lpPathName:생성하고자 하는 디렉터리 이름을 지정한다.
2)lpSecurityAttributes:보안 속성을 지정할 때 사용된다. ACL에 배우지 않았으므로 기본적으로 NULL을 전달해
디폴트 속성을 지정.
BOOL RemoveDirectory (
	LPCTSTR lpPathName 1)
);
If the function fails, the return value is zero.
1)lpPathName:소멸하고자 하는 디렉터리 이름을 지정한다.
18_10.cpp CreateDeleteDirectory.cpp
매크로를 1로 둔 다음에 컴파일 및 실행을 한다.
0으로 변경해서 다시 한번 컴파일 및 실행을 한다.

현재 디렉터리, 시스템 디렉터리 그리고 Windows 디렉터리
현재 디렉터리(Current Directory)
"초기에는 프로그램이 Load된 디렉터리로 설정되며, 이후 변경 가능하다."
기준이 되는 것이 현재 디렉터리이다(표준 검색 경로 중 하나로서).

Visual Studio에서 실행하면 현재 디렉터리는 프로젝트 파일이 존재하는 위치로 설정.

현재 디렉터리를 참조하거나 변경하는 데 사용되는 함수들.
DWORD GetCurrentDirectory (
	DWORD nBufferLength, 1)
	LPTSTR lpBuffer 2)
);
If the function fails, the return value is zero.
1)nBufferLength:두 번째 인자로 전달된 버퍼의 길이를 지정한다.
2)pBuffer:현재 디렉터리 정보를 저장할 버퍼의 주소값을 지정한다.
BOOL SetCurrentDirectory (
	LPCTSTR lpPathName 1)
);
If the function fails, the return value is zero.
1)lpPathName:변경하고자 하는 현재 디렉터리 정보를 지정한다.
18_11.cpp CurrentDirectory.cpp

시스템 디렉터리(System Directory) & Windows 디렉터리
시스템 디렉터리는 각종 라이브러리(DLL) 및 드라이버 파일처럼 Windows 시스템에 중요한 파일들이 존재하는 위치이고,
Windows 디렉터리는 초기화 및 실행파일들이 존재하는 위치이다.
어디가 시스템 디렉터리고 어디가 Windows 디렉터리인지 그 위치를 아는 것이 중요하다.
그리고 이러한 디렉터리들은 현재 디렉터리와 달리 변경이 불가능하다.
문제가 생길 수 있기 때문에 Windows 운영체제는 Windows 디렉터리와 시스템 디렉터리 변경을 제한.
시스템 디렉터리와 Windows 디렉터리의 위치 정보를 확인하기 위해 사용되는 함수들.
UINT GetSystemDirectory (
	LPTSTR lpBuffer, 1)
	UINT uSize 2)
);
If the function fails, the return value is zero.
1)lpBuffer:시스템 디렉터리 정보를 저장할 버퍼의 주소값을 지정한다.
2)uSize:첫 번째 인자로 전달된 버퍼의 길이를 지정한다.
UINT GetWindowsDirectory (
	LPTSTR lpBuffer, 1)
	UINT uSize 2)
);
If the function fails, the return value is zero.
1)lpBuffer:Windows 디렉터리 정보를 저장할 버퍼의 주소값을 지정한다.
2)uSize:첫 번째 인자로 전달된 버퍼의 길이를 지정한다.
18_12.cpp System_Windows_Dir.cpp

디렉터리에서 파일 찾기
파일의 위치 정보를 얻고자 할 때, 특정 디렉터리 내에 존재하는 파일 정보를 얻고자 할 때 사용하는 함수들.
문자열로 지정한 경로에 특정 파일이 존재하는지 확인하는 용도로 사용할 수 있는 함수.
파일 이름을 인자로 해서 해당 파일이 저장되어 있는 완전경로 정보를 얻고자 할 때에 사용할 수도 있다.(제한된 형태)
DWORD SearchPath (
	LPCTSTR lpPath, 1)
	LPCTSTR lpFileName, 2)
	LPCTSTR lpExtension, 3)
	DWORD nBufferLength, 4)
	LPTSTR lpBuffer, 5)
	LPTSTR* lpFilePart 6)
);
If the function fails, the return value is zero.
1)lpPath:대상 경로를 지정한다. 이 인자를 통해 지정된 경로에서 파일을 찾게 된다. 인자로 NULL이 전달되면,
표준 검색 경로 순서로 파일을 찾게 된다.
1_실행 중인 프로그램이 Load된 디렉터(실행파일이 존재하는 디렉터리)
2_현재 디렉터리
3_시스템 디렉터리
4_Windows 디렉터리
5_마지막으로 환경변수 PATH에 등록된 디렉터리들
2)lpFileName:찾고자 하는 파일 이름.
3)lpExtension:확장자를 지정하는 인자로서 첫 번째 문자는 반드시 '.'으로 시작해야 한다.
lpFileName이 확장자를 포함하고 있거나 확장자를 지정해 줄 필요가 없을 때에는 NULL을 지정.
4)nBufferLength:완전경로명을 저장할 버퍼의 길이를 지정한다.
5)lpBuffer:완전경로명을 저장할 버퍼의 주소를 지정한다.
6)lpFilePart:함수 호출 결과로 얻게 되는 완전경로명(lpBuffer로 지정된 버퍼에 저장되는 완전경로명)의 마지막에는
파일 이름도 추가된다. 이 전달인자를 통해 파일 이름이 저장된 위치 정보(포인터값)를 얻게 된다.

환경변수 PATH에 등록된 정보는 [제어판]->[시스템]->[고급]->[환경변수]로 들어가 확인할 수 있다.
Administrator에 대한 사용자 변수는 Administrator로 로그인 했을 때에 추가로 반영되는 변수들이다.

18_13.cpp SearchPath.cpp
명령프롬프트의 실행파일로서 시스템 디렉터리에 저장되어 있는 CMD.EXE를 입력해 확인해본다.

SearchPath보다 유용한 함수들 3개가 있는데, 이 함수들은 하나의 기능을 완성하기 위해 함께 사용되어야 한다.
첫 번째로 필요한 함수는 FindFirstFile이다.
이 함수는 첫 번째 전달인자를 통해 전달되는 디렉터리나 파일 이름을 통해 부합되는 파일을 찾고, 정보를 추출해
두 번째 전달인자가 가리키는 변수에 저장한다.
HANDLE FindFirstFile (
	LPCTSTR lpFileName, 1)
	LPWIN32_FIND_DATA lpFindFileData 2)
);
If the function fails, the return value is INVALID_HANDLE_VALUE.
1)lpFileName:파일이나 디렉터리 이름을 지정한다. 지정된 정보를 근거로 파일(혹은 디렉터리) 정보를 얻게 된다.
2)lpFindFileData:발견된 파일이나 디렉터리 정보를 담을 WIN32_FIND_DATA 구조체 변수의 주소값을 전달한다.

FindFirstFile 함수의 반환 타입이 HANDLE이다.
이는 검색을 위한 핸들이므로 파일을 개방했을 때 얻게 되는 핸들로 인식하면 안된다.
이 함수를 통해서는 조건에 맞는 파일 중 가장 첫 번째 검색된 파일 정보만 얻을 수 있다.
따라서 조건에 맞는 또 다른 파일 정보를 얻기 위해 추가적인 작업인 FindFirstFile 함수가 반환한 핸들과 FindNextFile.
BOOL FindNextFile (
	HANDLE hFindFile, 1)
	LPWIN32_FIND_DATA lpFindFileData 2)
);
If the function fails, the return value is zero.
1)hFindFile:FindFirstFile함수 호출을 통해 얻은 핸들을 전달한다. 이 핸들을 가리키는 커널 오브젝트에는
찾고자 하는 파일(디렉터리 포함) 정보와 검색이 이뤄진 위치 정보가 담겨 있다.
따라서 이 전달인자를 통해 다음 파일을 찾을 수 있다.
2)lpFindFileData:발견된 파일이나 디렉터리의 정보를 담을 WIN32_FIND_DATA 구조체 변수의 주소값을 전달한다.

FindFirstFile("3RDPARTY에서 N자로 시작하는 디렉터리")---->Handle---->Kernel Object
----->3RDPARTY에서 N자로 시작하는 디렉터리 NETSCAPE를 찾음.
FindFirstFile 함수 호출을 통해 생성된 커널 오브젝트가 담고 있는 정보는 디렉터리 NETSCAPE에 관한 것.
물론 이어서 FindNextFile 함수를 호출하면, 다음에 존재하는 디렉터리에 관한 정보가 채워지게 된다.
그 이후에도 여전히 N으로 시작하는 디렉터리가 있다면 FindNextFile 함수 호출을 통해 커널 오브젝트에 또 다른
디렉터리 정보를 담을 수 있다.

FindFirstFile 함수는 결과적으로 커널 오브젝트를 생성하였다.
따라서 검색이 끝나면 다음 함수를 이용해 리소스를 반환해야 한다.
BOOL FindClose (
	HANDLE hFindFile 1)
);
If the function fails, the return value is zero.
1)hFindFile:FindFirstFile 함수를 통해 얻은 핸들을 반환한다.

typedef struct _WIN32_FIND_DATA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETime ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	TCHAR cFileName[MAX_PATH];
	TCHAR cAlternateFileName[14];
} WIN32_FIND_DATA, *PWIN32_FIND_DATA;
dwReserved1은 예약만 되어있을 뿐 사용되지 않는 멤버이고, dwReserved0는 dwFileAttributes의 값에 따라서
의미 있는 값이 채워지기도 한다.
18_14.cpp ListDirectoryFileList.cpp

이것만은 알고 갑시다
1. 가장 기본이 되는 연산은 데이터의 입력과 출력
2. 4GB 이상 대용량 파일 처리
64비트시스템에서
3. 표준 검색 경로.
Windows 시스템은 파일을 찾을 때 이 경로를 기준으로 검색을 한다.
4. 지원하는 기능을 알고 있자
어떠한 기능이 제공되는지 기억

*/