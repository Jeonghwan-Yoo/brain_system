/*
01 WIN32 vs WIN64
64비트와 32비트
한 번에 전송 및 수신할 수 있는 데이터의 크기에 따라서 32비트 시스템과 64비트 시스템이 나뉘게 된다.
즉, CPU가 버스를 통해서 한 번에 전송 및 수신할 수 있는 데이터의 크기가 32비트면 32비트 컴퓨터,
64비트면 64비트 컴퓨터.
또 하나의 준은 데이터 처리능력이다.
CPU는 외부로부터 들어오는 데이터를 처리해야 하는데, 32비트 컴퓨터는 한 번에 32비트 데이터를,
64비트 컴퓨터는 한 번에 64비트 데이터를 처리할 수 있다.
정리해보면
"한 번에 송수신할 수 있는 데이터 크기와 한 번에 처리할 수 있는 데이터 크기를 기준으로 32비트와 64비트"

프로그래머 입장에서의 64비트 컴퓨터
프로그래머 입장에서 보면 표현할 수 있는 주소값의 범위가 넓으면 넓을수록 좋다.
메모리 공간만 충분하다면 주소값의 범위가 넓은 만큼 더 넓은 메모리 공간을 활용할 수 있기 때문이다.
예를 들어 메모리가 1GB인데, 주소값을 표현하기 위해 4비트가 사용된다면 메모리의 할당할 수 있는 주소값의 개수는
2의 4승에 해당하는 16개가 전부이다.
따라서 사용할 수 있는 최대 메모리의 크기는 16바이트가 된다. 나머진 사용불가.
표현할 수 있는 주소의 범위가 넓으면서 연산속도도 빠르게 구성해야 한다.
32비트 컴퓨터에서는 32비트가 최선의 선택이다.
한 번에 처리할 수 있는 데이터(주소값 포함)의 크기가 32비트이기 때문이다.
32비트로 주소값을 표현하면 주소값의 이동 및 연산이 한 번에 이뤄진다.
뿐만 아니라 표현할 수 있는 주소의 범위도 4GB이니 매우 충분하다.
32비트 시스템에서 주소값의 이동 및 연산이 한 번에 처리 가능하다는 것은 다음과 같은 의미이다.
int arr[5] = { 1,2,3,4,5 };
int* pArr = arr;
pArr += 1;
이러한 연산을 위해서는 pArr이 지니고 있는 값을 ALU로 이동시켜야 한다.
최종적인 값의 증가는 ALU에 의해 이뤄지기 떄문.
pArr이 지니고 있는 주소값이 32비트라면, 한 번에 전송이 가능하고, 한 번에 연산이 가능하다.
32비트 데이터의 전송과 연산을 한 번에 처리할 수 있는 것이 32비트 시스템이기 때문.
만약 주소값을 64비트로 표현한다면, pArr이 저장하고 있는 64비트 주소값을 두 번에 나눠서 ALU로 전송해야 하고,
또 최소 두 번 이상에 걸쳐서 연산해야만 한다.
32비트 시스템은 64비트 데이터를 한 번에 처리하지 못하기 때문이다.
이는 상당한 속도의 저하로 이어진다.
마찬가지로 64비트 컴퓨터 환경에서도 포인터가 64비트로 표현되는 것이 최선이다.

주소값의 크기? 잘 이해되지 않는다.
1. 내부 메모리에 해당하는 RAM에 주소가 정해져 있나?
메인 메모리인 RAM에 주소가 붙어있는 것은 아니다.
운영체제에서 프로그램 실행을 위해 편의상 붙여놓은 가상의 주소이다(가상 메모리 주소).
2. 그렇다면, 주소값을 표현하기 위해 4비트를 사용했다는 것은 무슨 뜻이야?
0000번지부터 1111번지까지 주소를 표현할 수 있다.
즉, 많은 비트 수를 활용해서 주소를 표현할수록, 표현할 수 있는 주소의 범위는 더 넓어진다.
3. 왜 주소의 표현 범위가 넓으면 넓을수록 프로그래머에게 좋다는 거지?
표현할 수 있는 주소의 범위가 넓어지면, 그만큼 활용할 수 있는 메모리 크기가 커진다.
예를 들어 총 활용 가능한 메모리 크기가 40바이트라고 가정해보자.
int _tmain(void) {
	TCHAR str[100];
	_tscanf(_T("%s"), str);
	_tprintf(_T("%s"), str);
	return 0;
}
위와 같은 경우 TCHAR가 1바이트라고 가정해도 100바이트가 필요하기 때문에 실행될 수 없는 프로그램이다.
int _tmain(void) {
	TCHAR ch;
	do {
		_tscanf(_T("%c"), &ch);
		_tprintf(_T("%c"), ch);
	} while (ch != '\n');
	return 0;
}
위와 같은 경우는 같은 기능이면서 실행가능하다.
지금까지는 운영체제가 주소값을 32비트로 표현하면서 4GB라는 아주 큰 메모리를 제공해왔으면 64비트에선 더 크다.
4. 이게 난 제일 궁금해! 내 컴퓨터는 RAM이 256M야. 어떻게 4GB를 할당해?
32비트를 활용하므로 2의 32승에 해당하는 4GB이다.
문제는 시스템에 4GB의 RAM이 장착되어 있지 않다.
그럼에도 불구하고 Windows는 여전히 4GB까지 메모리 활용을 허락하고 있다.

02 프로그램 구현 관점에서의 WIN32 vs WIN64
MS에서는 64비트 기반의 운영체제를 내놓으면서도 32비트 시스템과의 호환성을 중시하였다.
그렇기 때문에 프로그래밍 스타일에 대한 가이드를 제시하고 있다.

LLP64 vs LP64
운영체제 모델   char  short  int  long  pointer
Windows LLP64  1B    2B     4B    4B    8B
UNIX    LP64   1B    2B     4B    8B    8B
Windows에서는 LLP64라는 데이터 표현 모델을 따르는데, int와 long은 그대로 4바이트로 표현하고, 포인터만 8바이트.
따라서 32비트 시스템과의 호환성을 중시한 모델.
UNIX에서는 long만 차이가 난다.

64비트와 32비트 공존의 문제점
#include <stdio.h>
int main(void) {
	int arr[10] = { 0, };
	int arrVal = (int)arr; //데이터 손실이 발생할 수 있는 위치
	printf("pointer : %d\n", arrVal);
	return 0;
}
배열이 선언된 주소값을 출력하기 위해 int형 변수에 그 값을 저장하고 있다.
이러한 방식의 코드가 32비트 시스템에서는 전혀 문제되지 않았다.
int형 자료형도 포인터도 4바이트로 표현되기 때문이다.
그러나 64비트 시스템에서는 포인터를 int, long등 4바이트 정수형 데이터로 형 변환해서는 안된다.
포인터는 8바이트로 표현되기 때문에 형변환 과정에서 데이터 손실이 발생할 수 있다.
64비트 Windows시스템은 16T바이트의 메모리 공간을 활용할 수 있도록 디자인 되었다.
따라서 배열 arr이 4G이하의 메모리 영역에 할당되어 4B로 주소값 표현이 가능하다면 데이터 손실이 발생하진 않겠지만,
그 이상의 메모리 영역에 선언된다면 데이터 손실이 발생해서 배열의 정확한 주소값을 확인하지 못하게 된다.
만약 주소가 1 00000000 00000000 00000000 00000000이라면 앞에 1의 값을 받을 수 없게 된다.
"64비트 시스템에서는 포인터가 지니고 있는 주소값을 4바이트 정수형으로 형 변환하지 말자."

Windows 스타일 자료형
다른 시스템으로서의 이식성을 고려한다면 기본 자료형을 사용하거나 프로젝트의 성격 및 특성에 맞게 새로운
이름으로 자료형을 정의하는 것이 보다 나은 방법이다.
다만 Windows기반에서의 실행만 고려한다면 MS에서 정의하고 있는 자료형을 사용하는 것도 좋은 선택.
MS에서 정의하고 있는 많은 양의 자료형 중에서 ANSI기본 자료형에 대응하는 일부.
WINDOWS자료형  의미                      정의 형태
BOOL          Boolean variable          typedef int BOOL
DWORD         32-bit unsigned integer   typedef unsigned long DWORD
DWORD32       32-bit unsigned integer   typedef unsigned int DWORD32
DWORD64       64-bit unsigned integer   typedef unsigned __int64 DWORD64
INT           32-bit signed integer     typedef int INT
INT32         32-bit signed integer     typedef signed int INT32
INT64         64-bit signed integer     typedef signed __int74 OMT64
LONG          32-bit signed integer     typedef long LONG
LONG32        32-bit signed integer     typedef signed int LONG32
LONG64        64-bit signed integer     typedef signed __int64 LONG64
UINT          Unsigned INT              typedef unsigned int UINT
UINT32        Unsigned INT32            typedef unsigned int UINT32
UINT64        Unsigned INT64            typedef unsigned __int74 UINT64
ULONG         Unsigned LONG             typedef unsigned int ULONG
ULONG32       Unsigned LONG32           typedef unsigned int ULONG32
ULONG64       Unsigned LONG64           typedef unsigned __int64 ULONG64
~32형태의 자료형은 시스템에 상관없이 32비트로 표현되고, ~64형태의 자료형은 시스템에 상관없이 64비트로 표현.

MS C/C++에서는 정수 타입으로 크기를 지정해서 선언하는 것이 가능하다.
__int(n)의 형태로 8, 16, 32, 64를 지정해서 변수를 선언할 수 있다.
__int8, __int16, __int32, __int64와 같은 타입 선언.
이들은 각각 ANSI표준의 char, short, int에 해당한다.
다만 __int64는 ANSI표준에 존재하지 않는, MS C/C++에만 존재하는 자료형이다.
그러나 기본 자료형과 마찬가지로 사칙연산이 가능하다.
WINDOWS자료형  의미                      정의 형태
PINT           INT32에 대한 포인터        typedef int* PINT
PINT32         INT32에 대한 포인터        typedef signed int* PINT32
PINT64         INT64에 대한 포인터        typedef signed __int64* PINT64
PLONG          LONG에 대한 포인터         typedef LONG* PLONG
PLONG32        LONG32에 대한 포인터       typedef signed int* PLONG32
PLONG64        LONG64에 대한 포인터       typedef signed __int64* PLONG64
PUINT          UINT에 대한 포인터         typedef unsigned int* PUINT
PUINT32        UINT32에 대한 포인터       typedef unsigned int* PUINT32
PUINT64        UINT64에 대한 포인터       typedef unsigned __int64* PUINT64
PULONG         ULONG에 대한 포인터        typedef ULONG* PULONG
PULONG32       ULONG32에 대한 포인터      typedef unsigned int* PULONG32
PULONG64       ULONG64에 대한 포인터      typedef unsigned __int64* PULONG64

WIN64로 이전하면서 등장한 자료들을 사용할 경우, 변수 선언 시 할당된 바이트 수를 정확하고도 쉽게 파악할 수
있어서 도움은 되지만, WIN32시절에 정의된 자료형이 WIN64환경에서 쓸모가 없어진 것은 아니다.
DWORD64를 사용해야 할 만큼 큰 정수 표현이 필요한 상황이 자주없어서 DWORD를 주로 사용.
"유니코드와 아스키코드를 공통으로 지원하도록 예제를 작성하되, 64비트 시스템에서 새롭게 정의된 자료형은
가급적 사용하지 않겠다"

WINDOWS 자료형 확인하기
확인하고자 하는 자료형의 위치에 마우스 커서를 올려 놓고 오른쪽 버튼을 누른다음에 [Go To Definition]이나
[Go To Declaration]을 선택한다.
차이점은 정의로 이동하느냐, 선언으로 이동하느냐에 있다.
함수 참조에서는 차이를 보이지만 자료형 확인을 위해서는 상관없다.
그럼 자료형이 선언된 헤더파일로 이동하게 된다.
그 외에도 MSDN을 참조하는 것도 좋은 방법이다.

Polymorphic 자료형
WIN64기반으로 넘어가면서 Polymorphic자료형을 정의하고 있다.
다형적이라는 의미는 하나의 대상이, 보는 관점에 따라서 다양한 의미나 상태를 지닌다는 뜻이다.
상황과 환경에 따라서 그 자료형이 의미하는 바가 유동적이라는 뜻.
#if defined(_WIN64)
	typedef __int64 LONG_PTR;
	typedef unsigned __int64 ULONG_PTR;

	typedef __int64 INT_PTR;
	typedef unsigned __int64 UINT_PTR;
#else
	typedef long LONG_PTR;
	typedef unsigned long ULONG_PTR;

	typedef int INT_PTR;
	typedef unsigned int UINT_PTR;
#endif
포인터값 기반의 산술 연산을 위해 정의된 자료형이기에 PTR이라는 이름.
32비트 시스템과 64비트 시스템의 포인터 정밀도(크기)가 다르기 때문에 발생할 수 있는 문제를 해결하기 위해 등장.

__WIN64는 64비트 기반으로 프로젝트 구성 시 자동적으로 삽입되는 매크로이다.
32비트 기반으로 프로젝트 구성 시 매크로 __WIN32가 자동으로 삽입된다.
따라서 이 매크로는 시스템 환경에 따라서 조건부 컴파일 및 실행하는 데 있어서 기준이 된다.

3_1.cpp PolymorphicType1.cpp
두 메모리 거리가 항상 12바이트만큼 떨어져 있는 이유는 사이에서 스택이 오작동하는 것을 찾아내기 위해 추가할당이 있다.
INT, UINT는 각각 int, unsigned int와 동일하다.
32비트 기반 Windows프로그래밍에서 익숙한 자료형들.
CalDistance함수는 WIN32만을 기반으로 한다.
왜냐하면 전달받는 인자나 반환값의 상태가 4바이트 기준으로 맞춰져 있기 때문이다.
이는 4바이트로 표현 가능한 범위의 주소값만 포인터에 저장된다는 가정이 들어가 있는 것.
결론적으로, WIN64기반에서는 4바이트로 표현 불가능한 범위의 주소값이 등장할 수 있으므로, WIN64기반에서는 사용불가.
UINT64 CalDistance(UINT64 a, UINT64 b) 
{
	return a - b;
}
로 고쳐주어야 한다.
WIN32기반에서는 기존과 같은 구성으로, WIN64기반에서는 위의 함수와 같은 구성으로 컴파일 및 실행시켜야 한다.
첫번째로 생각해볼 수 있는 것이 조건부 컴파일이다.
#if defined(_WIN64)
	 UINT CalDistance(UINT64 a, UINT64 b)
#else
	UINT CalDistance(UINT a, UINT b)
#endif
	{	return a - b;}
하지만 조건부 컴파일을 위한 매크로로 인해 가독성이 많이 떨어져서 지저분해보일 수 있다.
3_2.cpp PolymorphicType2.cpp
실제로 개발과정에서 이러한 Polymorphic자료형 변수를 직접 선언하는 일은 드물다.
다만 Windows에서 제공하는 시스템 함수 중 일부는 이 자료형 기반으로 구성되어 있는데, 이는 시스템 함수의
32비트, 64비트간 호환성을 높이기 위한 방법으로 사용된 것이다.

03 오류의 확인
GetLastError 함수와 에러코드
Windows시스템 함수를 호출하는 과정에서 오류가 발생하면, GetLastError함수 호출을 통해 오류의 원인을 확인할 수 있다.
많은 수의 Windows시스템 함수들은 오류가 발생했을 때 NULL을 반환한다.
반환되는 NULL값으로 오류가 발생한 것은 알 수 있지만, 원인은 알 수 없다.
오류가 발생했을 때, 이어서 바로 GetLastError함수를 호출하면 오류의 원인에 해당하는 에러코드를 얻을 수 있다.
DWORD GetLastError(void);
MSDN을 참조하면 시스템 에러코드의 종류와 해당 에러코드가 의미하는 바를 알 수 있다.
3_3.cpp GetLastError.cpp
3_4.cpp ErrorStateChange.cpp
"오류 확인은 오류가 발생한 직후에 바로 한다."
Windows 시스템 함수가 호출될 때마다 GetLastError 함수가 반환하는 에러코드는 갱신된다.
오류가 발생한 직후 바로 이어서 오류 확인을 하는 것은 기본적인 행동.
에러코드 0은 The operation completed successfully.
다시 한번 실행해보면 ABC2.DAT가 존재하기 때문에 함수 호출이 실패하였다.
에러코드 80은 The file exists.
"오류가 발생하면, 바로 이어서 GetLastError함수를 호출해서 오류코드를 얻어야 한다."

이것만은 알고 갑시다
1. 64비트 시스템과 32비트 시스템의 구조적 차이
기준 두가지는 "한 번에 송수신할 수 있는 데이터 크기"와 "한 번에 처리할 수 있는 데이터 크기".
64비트 시스템에서는 한 번에 64비트 데이터를 전송 및 처리할 수 있고,
32비트 시스템에서는 한 번에 32비트 데이터를 전송 및 처리할 수 있다.
2. 주소값 표현에 사용되는 바이트 수가 지니는 의미
64비트 시스템은 한 번에 처리할 수 있는 데이터가 64비트이므로, 주소값을 표현하는 데도 64비트를 활용한다.
이는 표현할 수 있는 값의 범위를 넓혔다는 데 의의가 있다.
3. Polymorphic 자료형
4. LLP64와 LP64
WINDOWS에서와 UNIX의 차이.
5.GetLastError 함수의 사용방법
가장 많이 호출하는 함수 중에 하나이다.ㅏ
6.난이도 있는 명령 프롬프트 프로젝트를 진행한다는 사실을 기억하자.

*/
