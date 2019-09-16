/*
MS에서 C++문법을 확장하는 경우는 있어도 문법을 변경하는 일은 없다.
특이한 것들은 프로그래머의 편의를 위해서 제공되는 것들이다.
GUI프로그래밍을 하던, 시스템 프로그래밍을 하건 유니코드에 대한 이해는 필수이다.

01 Windows에서의 유니코드(UNICODE)
문자셋(Character Sets)의 종류와 특성
아스키코드는 미국에서 정의하고 있는 표준이다.
알파벳 개수 26개에다가 확장 문자를 포함해 256개를 넘지 않아 1바이트로도 충분히 표현할 수 있다.
유니코드는 문자를 표현하는 데 있어서 균일하게 2바이트를 사용한다.
왜냐하면 전세계의 모든 문자와 다양한 종류의 기호를 표현하기 위해.
문자셋이란 문자들의 집합으로 "약속된 문자의 표현방법"을 의미.
문자셋은 종류에 따라서 세 가지 형태로 나뉜다.

SBCS(Single Byte Character Set)
문자를 표현하는 데 있어서 1바이트만을 사용하는 방식으로 아스키코드가 대표적.
MBCS(Multi Byte Character Set)
다양한 바이트 수를 사용해서 문자를 표현하는 방식.
유니코드는 MBCS에 속하지 않는다.
왜냐하면 MBCS는 SBCS를 포함하고 있기 때문이다.
그래서 대부분의 문자들을 2바이트로 처리하되, 경우에 따라서는 1바이트로 처리한다.
아스키코드에서 정의하면 1바이트로 처리하고, 아니면 2바이트로 처리하는 방식.
상당히 효율적으로 문자를 표현하지만 프로그램을 구현하는 데 세심한 주의를 기울여야 한다.
WBCS(Wide Byte Character Set)
유니코드가 해당한다.
모든 문자를 2바이트로 처리하는 문자셋이다.

MBCS 기반의 문자열
2_1.cpp MBCS1.cpp
배열의 크기는 ABC(3) + 한글(4) + NULL(1) = 8Bytes
영문은 1바이트로 한글은 2바이트로 처리되고 있다.
이것은 현재 MBCS를 기반으로 실행되고 있음을 보여준다.
strlen은 문자열의 길이를 계산함에 있어서 NULL문자를 포함하지 않는다.
길이는 ABC(3) + 한글(4) = 7Bytes
2_2.cpp MBCS2.cpp
문자열 길이는 5이지만, 문자열에 할당된 크기가 10바이트인 관계로 fputc함수를 10번 호출해야만 한다.
이런 문제점들도 프로그래밍을 잘하면 어느 정도 해결이 가능하다.
이런 문제점의 해결책이 될 수 있는 것이 WBCS방식이다.
WBCS방식은 모든 문자들을 2바이트로 처리한다.
모든 문자들을 동일한 바이트의 크기로 처리한다는 것이 문제점을 해결하는 실마리.

WBCS 기반의 프로그래밍
[char을 대신하는 wchar_t]
문자를 표현하는데 사용되는 자료형 char를 대신해서 자료형 wchar_t를 사용해야 한다.
wchar_t형 변수는 2바이트 메모리 공간이 할당된다.
따라서 유니코드를 기반으로 문자를 표현하는 것이 가능하다.
typedef unsigned short wchar_t;
["ABC"를 대신하는 L"ABC"]
wchar_t str[] = "ABC";형태로 선언하면 문제가 발생한다.
배열 str은 유니코드 문자열을 저장할 준비가 되어 있지만, 오른쪽 문자열은 여전히 MBCS기반 문자열이기 때문.
whcar_t str[] = L"ABC";형태로 변경해야 한다.
L은 "이어서 등장하는 문자열은 유니코드 기반으로 표현하라"는 의미.
이 경우에는 널문자까지도 2바이트로 처리되어 총 8바이트.
wchar_t는 ANSI표준에서 유니코드 지원을 위해 정의한 표준 자료형이다.
[strlen을 대신하는 wcslen]
2_3.cpp MBCS1.cpp 유니코드 버전
문자열 조작 함수들은 SBCS기반 문자열을 처리하기 위한 함수였다.
 strlen -> size_t wcslen(const wchar_t* string);
 strcpy -> wchar_t* wcscpy(wchar_t* dest, const wchar_t* src);
strncpy -> wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, size_t cnt);
 strcat -> wchar_t* wcscat(wchar_t* dest, const wchar_t* src);
strncat -> wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, size_t cnt);
 strcmp -> int wcscmp(const wchar_t* s1, const wchar_t2* s2);
strncmp -> int wcsncmp(const wchar_t* s1, const wchar_t2* s2, size_t cnt);

SBCS함수나 WBCS함수나 전달인자의 개수 및 의미는 완전히 동일하다.
다만 WBCS기반 함수의 전달인자는 유니코드 기반 문자열이다.
SBCS는 대부분 MBCS기반 문자열 처리를 위해서도 사용 가능하다.
다만 strlen함수는 MBCS문자열을 처리하는데 2_1.cpp처럼 문제가 된다.
또한, size_t는 typedef unsigned int size_t;
2_4.cpp WBCS1.cpp

완전한 유니코드 기반으로 : 첫 번째
Windows2000이상의 운영체제는 기본적으로 유니코드를 지원한다.
유니코드를 지원할 뿐만아니라, 내부적으로 모든 문자열을 유니코드 기반으로 처리한다.
printf함수도 문자열 처리 함수이므로, SBCS와 WBCS 중 하나로 구분 되는데 SBCS기반 문자열을 처리하는 함수다.
만약에 Windows2000이상의 운영체제에서 위와 같은 함수의 호출이 이뤄지면 운영체제는 전달되는 문자열을 내부적으로
2바이트 유니코드 형식으로 변환한다.
Windows2000이상의 운영체제는 모든 문자열을 유니코드 기반으로 처리하기 때문.
이는 프로그램 성능에 다소 영향을 미치는 요소가 될 수 있다.
유니코드 기반으로 프로그램을 작성하면, 성능에는 전혀 영향을 미치지 않는다.
printf -> int wprintf(const wchar_t* format [, argument]...);
 scanf -> int wscanf(const wchar_t* format [, argument]...);
 fgets -> wchar_t* fgetws(wchar_t* string, int n, FILE* stream);
 fputs -> int fputws(const wchar_t* string, FILE* stream);
2_5.cpp WBCS2.cpp

wprintf, fputws와 같은 함수들을 통해 유니코드 기반으로 한글을 출력하고 싶다면, 호출하기 전에
#include "locale.h"
_wsetlocale(LC_ALL, L"korean");
_wsetlocale함수는 프로그램이 실행되는 나라 및 지역에 대한 정보를 설정하는 데 사용되는 함수이다.

완전한 유니코드 기반으로 : 두 번째
2_5.cpp는 완전한 유니코드 기반이 아니다.
2_6.cpp WBCS3.cpp
c:\>test.exe AAA BBB                       c:\>test.exe AAA BBB
          ↓ main                                     ↓ wmain
"test.exe" "AAA" "BBB"                     L"test.exe" L"AAA" L"BBB"
          ↓ 인자 전달                                 ↓ 인자 전달
int main(int argc, char* argv[])           int wmain(int argc, wchar_t* argv[])
함수 이름이 main이면 전달되는 문자열은 MBCS기반으로 구성되어 인자로 전달된다.
함수 이름이 wmain이면 프로그램 실행 시 전달되는 문자열을 유니코드 기반으로 구성한다.
2_7.cpp WBCS4.cpp

02 MBCS와 WBCS의 동시 지원
WBCS기반으로 구현하는 것이 좋아보이지만, 시스템 모두가 완벽히 유니코드 기반을 지원하는 것이 아니어서
문제가 발생할 소지가 높다.
프로그램은 한번만 구현하고, 변경없이 MBCS기반으로 돌아가는 형태로도, WBCS기반으로 돌아가는 형태로도
컴파일 가능하다면 아주 만족스러울 것이다.
안그러면 변경할 때 문자열을 모두 변경해야하고 함수들도 변경해야되는데 불편하고 버그로 이어질 수도 있다.

#include <windows.h>
windows.h는 Windows기반 프로그래밍을 하는 데 있어서 기본적으로 항상 포함해야 하는 헤더파일이다.
windows.h는 Windows프로그래밍에 필요한 다양한 종류의 헤더파일을 더불어 포함하기 때문에 이 헤더파일 하나로
충분한 경우가 대부분이다.
새로운 자료형들은 헤더파일 windows.h에 정의되어 있다.
정확하게는 winnt.h에 정의되어 있고, 헤더파일 windef.h가 winnt.h를 포함하고, windows.h는 windef.h를 포함.
windows.h를 통해 Windows시스템 프로그래밍에 필요한 대부분의 것을 직접/간접적으로 포함하게 된다.

Windows에서 정의하고 있는 자료형
typedef char CHAR;
typedef wchar_t WCHAR;
문자열의 주소값을 저장할 수 있는 자료형
매크로 CONST는 windef.h에 나머지는 winnt.h에 정의되어 있다.
#define CONST const
typedef CHAR* LPSTR;
typedef CONST CHAR* LPCSTR;
typedef WCHAR* LPWSTR;
typedef CONST WCHAR* LPCWSTR;
const를 CONST로 사용하는 것은 Windows 스타일의 자료형 이름이 대문자로 구성되는 흐름을 따라가기 위해.
2_8.cpp WinString.cpp
2_8.c

Windows스타일 자료형에 대한 이야기
Windows에서는 int, char와 같은 기본 자료형도 Windows스타일의 이름으로 정의하고 있다.
이런 자료형을 정의하는 이유는 첫 번쨰로 선언의 편리성이다.
typedef는 복잡한 선언을 단순하게 해준다.
typedef unsigned int size_t;
긴 문장을 대신해서 간결하고, 의미도 보다 강하게 부여된 이름을 변수 선언 시 사용할 수 있다.
두 번째는 확장의 용이성이다.
만약 unsigned char에서 unsigned int로 바꿔야 한다면 일일이 바꿔주어야 하지만
STR_LEN이라는 이름을 대신 사용해서 변수를 선언한 상황이라면 일은 수월해진다.
정의를 변경해주고 컴파일만 다시 하면 모든 작업이 완료되기 때문.
즉, 확장성이 좋아지는 것.
typedef unsigned char STR_LEN;
typedef unsigned int STR_LEN;
즉, 선언의 용이성과 확장성을 고려해서 typedef기반으로 적절한 이름의 자료형을 정의하는 것은 아주 좋은
프로그래밍 습관이다.
프로젝트를 진행할 때마다 고유한 이름의 자료형을 정의하고, 또 이를 활용하여 프로그래밍을 개발하는 것이 권장.

MBCS와 WBCS를 동시에 지원하기 위한 매크로
Windows에서는 MBCS와 WBCS를 동시에 수용하는 형태의 프로그램 구현을 위해서 매크로를 정의하고 있다.
#ifdef UNICODE
	typedef WCHAR TCHAR;
	typedef LPWSTR LPTSTR;
	typedef LPCWSTR LPCTSTR;
#else
	typedef CHAR TCHAR;
	typedef LPSTR LPTSTR;
	typedef LPCSTR LPCTSTR;
#endif
tchar.h헤더파일의 일부를 편집해놓은 것인데, tchar.h는 windows.h에 포함되지 않는다.
따라서 헤더파일 tchar.h는 추가로 포함시켜야 한다.
#ifdef _UNICODE
	#define __T(x) L ## x //##는 맨 앞뒤에 올 수 없고 중간에서 연결시켜주는 것. 여기선 x앞에 L을 붙인다.
#else
	#define __T(x) x
#endif
#define _T(x) __T(x)
#define _TEXT(x) __T(x)
예를 들어
TCHAR arr[10];
매크로 UNICODE가 정의되면 WBCS
TCHAR arr[10]; -> WCHAR arr[10]; -> wchar_t arr[10];
매크로 UNICODE가 정의되지 않으면 MBCS
TCHAR arr[10]; -> CHAR arr[10]; -> char arr[10];
예를 들어
_T("HANBIT");
이 매크로는 아무 조건 없이 전처리기에 의해
__T("HANBIT");
매크로 _UNICODE가 정의되면 WBCS
__T("HANBIT"); -> L"HANBIT"
매크로 _UNICODE가 정의되지 않으면 MBCS
__T("HANBIT"); -> "HANBIT"
2_9.cpp MBCS_WBCS1.cpp
매크로를 주석처리하고 컴파일해도 변함이 없다면 Visual Studio설정을 확인해야 한다.
프로젝트속성으로 들어가면(Alt+p두번) C/C++의 Preprocessor에서 <edit>을 누르면
"Inherited valuse"에 _UNICODE와 UNICODE가 정의되어 있다.
프로젝트 생성 시 기본적으로 정의된 매크로들이다.
숫자를 변경시키려면 Inhrit from parent or project defaults의 체크를 해제해야 하는데 경고 메시지를 받는다.
매크로가 중복 정의되었다는 경고 메시지인데 이 경우에도 설정을 해제하면 된다.
컴파일 이전에, 전처리기에 의해 전처리 과정을 거치게 되는데, 기본적으로 정의하고자 하는 매크로를 프로젝트 속성
페이지에서 설정할 수 있다.
MBCS기반으로 컴파일하려면 설정창에서 _UNICODE와 UNICODE를 지워도 되지만
#undef지시자를 통해서 이미 정의된 _UNICODE를 무효화시키면 된다.
#undef _UNICODE
#undef UNICODE

MBCS와 WBCS를 동시에 지원하기 위한 함수들
2_9.cpp는 매크로 _UNICODE, UNICODE의 정의 유무에 따라 WBCS나 MBCS기반으로 컴파일이 된다.
하지만 printf는 매크로 정의에 상관없이 MBCS기반으로 컴파일된다.
유니코드 기반으로 돌아가게 하려면 wprint로 바꿔야한다.
매크로에 자신이 있다면 언급한 문자열에 적용할 수 있는 매크로 _T("string")을 기억한다면
#ifdef _UNICODE
	#define _tprintf wprintf
#else
	#define _tprintf printf
#endif
그러면 _UNICODE의 정의 유무에 따라서 WBCS나 MBCS방식으로 컴파일 될 것이다.
_tprint(_T("string size : %d\n"), size);
하지만 그럴필요 없이 이미 tchar.h에 선언되어 있으니 활용할 수 있다.
#ifdef _UNICODE
	#define _tmain wmain
	#define _tcslen wcslen
	#define _tcscat wcscat
	#define _tcscpy wcscpy
	#define _tcsncpy wcsncpy
	#define _tcscmp wcscmp
	#define _tcsncmp wcsncmp
	#define _tprintf wprintf
	#define _tscanf wscanf
	#define _fgetts fgetws
	#define _fputts fputws
#else
	#define _tmain main
	#define _tcslen strlen
	#define _tcscat strcat
	#define _tcscpy strcpy
	#define _tcsncpy strncpy
	#define _tcscmp strcmp
	#define _tcsncmp strncmp
	#define _tprintf printf
	#define _tscanf scanf
	#define _fgetts fgets
	#define _fputts fputs
#endif
2_10.cpp MBCS_WBCS2.cpp

프로젝트를 생성하면, 기본적으로 Pre-compiled헤더파일을 사용하도록 설정된 형태의 프로젝트가 생성될 것이다.
Pre-compiled헤더는 자주 사용되는 헤더파일 정보를 미리 모아 두어서 컴파일 속도를 향상시키기 위한 것.
Pre-compiled헤더를 사용하는 형태로 프로젝트를 생성하면 stdafx.h와 stdafx.cpp파일이 만들어 지는데,
stdafx.h파일 안에서는 헤더파일 stdio.h와 tchar.h를 포함하고 있다.
따라서 두 헤더파일을 직접 포함시키지 않아도 된다.
1)설정하는 방법은 빈프로젝트를 생성하고 솔루션 탐색기에서 Source Files/Header Files필터 구성 확인 후
stdafx.h파일과 stdafx.cpp파일을 추가한다.
2)프로젝트 속성에서 C/C++ -> 미리 컴파일된 헤더 메뉴에서 '미리 컴파일된 헤더 만들기/사용' 항목에서 만들기 선택
3)stdafx.h 맨 윗줄에 #pragma once 추가(단 한번만 빌드)
4)stdafx.cpp를 포함한 프로젝트 모든 소스 파일에 #include "stdafx.h"추가
5)프로젝트 전체 빌드
6)이후부터는 '미리 컴파일된 헤더 만들기/사용' 항목을 사용으로 선택

이것만은 알고 갑시다
1. SBCS, MBCS, WBCS의 이해
SBCS는 문자를 표현하는 데 1바이트, MBCS는 문자를 표현하는 데 1바이트 혹은 2바이트, WBCS는 문자를 표현하는 2바이트
사용하는 문자셋을 의미. 유니코드는 WBCS에 해당.
2. 유니코드 기반 문자열 처리 함수
ANSI 표준 문자열 처리 함수는 별도로 유니코드 기반을 정의하고 있다.
3. UNICODE와 _UNICODE
정의 유무에 따라서 함수의 선언 형태가 달라진다.
두 매크로를 기반으로 유니코드 방식과 MBCS방식의 컴파일이 가능하도록 프로그램을 작성.
4. 유니코드 방식과 MBCS 방식을 모두 지원하기 위한 main함수의 구성
MBCS방식을 지원하려면 main, 유니코드 방식을 지원하려면 wmain, 두 가지 방식을 모두 지원하려면 _tmain이 존재.

*/