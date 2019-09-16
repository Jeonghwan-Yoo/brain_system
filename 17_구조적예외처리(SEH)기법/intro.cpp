/*
언어 차원에서 제공되는 C++ 예외처리 메커니즘이나, Windows C/C++ 컴파일러에서 제공하는 구조적 예외처리인
SEH(Structured Exception Handling) 기법을 적용하는 개발자는 적은 편.

01 SEH(Structured Exception Handling)
필요한 예외처리는 예를 들어 메모리를 동적할당하는 함수 malloc을 호출하면 반환되는 주소가 NULL이 아닌지
확인해야 하고, 프로세스나 쓰레드, 그리고 동기화 오브젝트들을 생성할 때에도 해당 함수 호출 후에 오류가 발생했는지
확인하는 코드를 삽입해야 한다.

예외처리의 필요성
FILE* filerptr = fopen("test.txt", "r");
if(filePtr == NULL)
{
	//Exception Handling...
}
char* dataBuf = (char*)malloc(sizeof(char)*100);
if(dataBuf == NULL)
{
	//Exception Handling...
}
int numOfRead = fread(dataBuf, 1, 10, filePtr);
if(numOfRead != 10)
{
	//Exception Handling...
	//추가로 파일의 끝인지, EOF인지를 비교해야 한다.
}
파일 개방, 데이터를 읽기 위한 메모리할당, 할당된 메모리에 파일 데이터를 저장하는 작업이 순차적으로 진행.
그리고 각각의 상황에 맞는 적절한 예외처리 코드가 존재한다.
실제로 하는 일은 파일을 열고, 메모리를 할당한 다음, 데이터를 읽는 것이 전부인데 예외상황을 처리하는 코드로
인해 코드가 복잡해진다.
if문은 예외와 관련해서 사용될 수도 있지만, 알고리즘 자체에서도 자주 등장한다.
그래서 정확한 코드 분석을 위해서는 if문에 대한 분석도 필요하다.
그래서 예외를 처리하는 코드만 따로 모아보자.
프로그램의 실제 흐름
{
	FILE* fileptr = fopen("test.txt", "r");
	char* dataBuf = (char*)malloc(sizeof(char)*100)
	int numOfRead = fread(dataBuf, 1, 10, filePtr);
}
위 흐름에 대한 예외처리 영역
{
	if(filePtr == NULL)
	{
		//Exception Handling...
	}
	if(dataBuf == NULL)
	{
		//Exception Handling...
	}
	if(numOfRead != 10)
	{
		//Exception Handling...
		//추가로 파일의 끝인지, EOF인지를 비교.
	}
}
프로그램의 실제흐름에 해당하는 키워드가 __try이고, 흐름에 대한 예외처리 영역이 __except이다.

예외(예외상황)와 에러(혹은 오류)의 차이점
컴파일이 잘되면 일차적으로 언어의 문법적인 오류는 없는 것.
그러나 실행하는 과정에서 문제가 발생할 수 있다.
파일이 존재하지 않는다면 문제가 발생한다.
파일이 존재하지 않는다는 것을 에러로 보기는 어렵다.
사용자가 임의로 파일을 지워 존재하지 않는다면 예외적인 상황이다.
메모리 해제를 적절히 해주지 않는다면 문제가 발생할 수 있다.
프로그래머가 메모리 해제를 정확히 해주지 않았으니 에러라고 생각할 수 있겠지만 만약 프로그래머가 프로그램에서
필요한 메모리 공간을 예측했고 예측결과 메모리 해제과정이 필요없다고 생각했을 수 있다.
그런데 예외적인 흐름이나 데이터 입력이 발생해 문제가 되면 예외적인 상황이 프로그래머의 예측에 문제를 발생.
그래서 대부분의 에러는 예외라는 표현으로 쓸 수 있다.
프로그램에서는 메모리 참조 오류도 종종 발생한다.
예를 들어 잘못된 주소의 메모리를 참조하는 것.
void TestFunction(void)
{
	int* p = NULL;
	*p = 100;
	...
}
포인터 p는 NULL로 초기화되었다.
NULL은 메모리 번지수 0을 의미하는 것이 아닌 주소가 할당되지 않았음을 의미한다.
그런데 다음 줄에서 데이터를 넣으려하니 에러가 발생한 것.
개발자가 포인터를 적절히 초기화하지 못해 발생한 메모리 참조 오류라 생각할 수 있다.
그런데 하드웨어 입장에선 잘못된 주소에 접근하는 예외적 상황이 발생한 것으로 생각해 예외라는 표현으로 설명.
결론은 "프로그램 실행 시 발생하는 문제점 대부분을 예외라고 인식하자"
처리 불가능한 문제가 발생하면 프로그램은 종료하게 되는데, 문제가 발생한다고 해서 프로그램이 종료된다면
이 또한 문제가 된다.
따라서 외부적인 요소에 의한 문제점이든 내부적인 요소에 의한 문제점이든 구조적 예외처리 기법의 관점에서 보면
대부분 해결 가능해야 한다.
즉 프로그램 실행 시 예측 가능한 대부분의 문제점을 예외로 간주하고, 처리가능하도록 프로그램을 구현해야 한다.

메모리 참조 오류는 하드웨어에서 컨트롤한다. 잘못된 주소 정보 입력이라는 문제상황 발생 시, 이를 처리하기 위해
예외 핸들러라는 것을 등록해 놓고 있다. 그래서 하드웨어 관점에서 잘못된 주소 정보의 등장을 에러라기 보다는
처리가 가능한 예외적 상황으로 표현하는 것이 일반적.

하드웨어 예외와 소프트웨어 예외
프로그램 실행 시 예측 가능한 모든 문제점을 예외로 인식.
구조적 예외처리에서 말하는 예외는 크게 두 가지로 나뉜다.
하나는 Hardware Exception, 다른 하나는 Software Exception.
하드웨어 예외란 하드웨어에서 인식하고 알려주는 예외를 의미한다.
예외의 근본적 원인은 응용 프로그램에 있지만, 이를 감지하고 예외상황이 발생했음을 알리는 주체가 하드웨어라는 뜻.
예로 정수를 0으로 나누는 연산을 할 경우 하드웨어 예외가 발생한다.
사칙연산을 수행하는 주체는 CPU이고 수행하는 과정에서 정수를 0으로 나누는 잘못된 연산 요청이 들어올 경우,
문제가 있다는 신호를 운영체제에 전달한다.
그러면 운영체제는 예외상황이 발생했음을 알고, 구조적 예외처리 메커니즘에 의해 예외상황이 처리되도록 진행.
소프트웨어 예외는 소프트웨어에서 감지하는 예외를 의미한다.
작성한 프로그램뿐만 아니라 운영체제를 포함한다.
주목할 부분은 하드웨어 예외는 하드웨어에서 발생하기 때문에 우리가 하드웨어 예외의 종류를 늘리거나 그 성격을
변경시킬 수 없다는 점이다.
그러나 소프트웨어 예외는 예외의 종류를 늘리는 것이 가능하다.
예를 들어 정수가 한 자리 숫자나 세 자리 숫자가 입력되면 예외로 간주해 구조적 예외처리 메커니즘을 동작하게.
소프트웨어 예외라는 것은 프로그래머가 직접 정의할 수 있는 예외이다.
즉 하드웨어 예외는 결정되어 있고, 소프트웨어 예외는 결정해야만 한다.

02 종료 핸들러(Termination Handler)
SEH는 성능을 약간 저하시킨다.
그러나 요즘 시스템의 성능 향상으로 인해 성능에 관한 문제점은 많이 없어졌다.
서버 프로그래밍을 할 경우에는 성능에 관한 문제점이 민감하여 문제가 될 수도 있지만 서버 환경 프로그래밍에서는
시스템 호환성을 높이기 위해 SEH을 사용하지 않는다.
그래서 SEH 관점에서 성능에 관한 부분은 중요한 요소가 아니다.
가장 중요한 것은 SEH의 장점을 파악하고 적용할 위치에 적절히 적용하는 능력.
구조적 예외처리 메커니즘은 기능적 특성에 따라 두 가지로 나뉜다.
하나는 Termination Handler이고 나머지 하나는 Exception Handler이다.
각각의 특징과 성격을 잘 파악해서 상황에 맞는 핸들러를 적용해야만 한다.

종료 핸들러의 기본 구성과 동작 원리
종료 핸들러에서 사용되는 키워드는 __try, __finally 두개다.
__try는 예외 핸들러에서도 사용되는데 종료 핸들러에서 사용될 때와 예외 핸들러에서 사용될 때, 그 역할에
약간의 차이를 보인다.
종료 핸들러에서 사용될 때의 역할이란 것은 __finally 키워드와 함께 사용될 때의 역할.
__try만 올 수 없고, __finally만 올 수도 없다.
이 둘 사이에는 다른 어떤 코드도 삽입될 수 없다.
즉, 컴파일러는 이 둘을 하나의 문장으로 인식한다.
__try
{
	//...
}
__finally
{
	//...
}
"__try 블록을 한 줄이라도 실행하게 되면, 반드시 __finally 블록을 실행해라!"
17_1.cpp __try__finally.cpp
__finally 블록의 실행은 컴파일러에 의해 보장되는 것이다.
컴파일러는 return문에 의해 반환되는 값을 임시 변수(컴파일러가 임시로 만든)에 저장하고, __finally 블록을
실행한 다음, 값을 반환하도록 바이너리 코드를 구성한다.
__try 블록을 빠져나오는 상황이 발생하더라도 __finally 블록은 반드시 실행된다.
__try블록을 빠져 나오게 하는 대표적인 상황:return, continue, break, goto, "예외"
예외가 발생해도 __finally 블록이 실행된다.
17_2.cpp exception_finally.cpp
ExitProcess, ExitThread 그리고 ANSI C 라이브러리의 exit 함수에 의한 프로세스 또는 쓰레드의 강제 종료는
__finally 블록의 실행으로 이어지지 않는다는 점이 유의사항.

구조적 예외처리 메커니즘의 관점에서 보더라도, 쓰레드의 종료는 return문에 의해 이뤄지는 것이 가장 좋다.

종료 핸들러 활용 사례 연구1
종료 핸들러의 특징은 프로그램이 정상적이든 문제가 발생하든 무조건 실행되는 __finally 블록이 있다.
문제의 발생 유무에 상관없이 무조건 실행되어야 하는 코드들을 생각해보자.
파일의 개방과 이에 따른 종료 상황.
파일은 열리면 닫아줘야 한다.
문제가 생겨 프로그램이 당장 종료되어야 하는 상황인데, 이전에 개방된 파일을 닫아주지 못한다면 저장된 데이터 일부가
손실될 수도 있는 일.
메모리의 동적 할당에서도 함수 내에서 메모리를 동적할당한다.
그리고 함수의 끝에서는 이 메모리를 해제하는 코드가 존재한다.
근데 중간에 문제가 생겨 함수를 빠져나가면 할당된 메모리는 유출된 상태로 남아있게 된다.
int AllocFunction()
{
	int* p = (int*)malloc(sizeof(int)*100);
	if(문제 발생)
	{
		return -1;
	}
	free(p);
	return 1;
}
문제가 존재하는지의 여부를 판단하는 if문 안에서도 할당된 메모리의 해제 코드를 삽입해야해서 잘못된 코드.
또한 발생 가능한 예외상황이 여럿인 경우도 있다.
그러면 if문 안에 매번 메모리 해제 코드를 삽입해야 한다.
이러한 상황에서 종료 핸들러를 적절히 활용한다면, 코드는 한결 간결해지고 코드에 대한 안전성도 높아지게 된다.
17_3.cpp TerminationHandlerEx1.cpp
실행 이후에 파일이 생성되고 생성된 파일에는 입력한 문자열이 저장.
반드시 실행되어야 하는 코드들이 __finally 블록으로 묶여 코드가 상대적으로 간결해지고, 안전성이 보장.

종료 핸들러 활용 사례 연구2
종료 핸들러의 특성을 잘 이해하고 보다 다양하게 적용할 수 있어야 한다.
뮤텍스를 소유한 쓰레드는 자신이 소유한 뮤텍스를 반드시 반환해야 한다.
만약에 문제가 생겨서나 코드의 오류로 뮤텍스를 반환하지 못한다면 문제가 될 수 있다.
17_4.cpp TerminationHandlerEx2.cpp
사실 WaitForSingleObject 함수의 반환값을 참조해서 세밀한 코드의 구현이 필요.

03 예외 핸들러(Exception Handler)
종료 핸들러는 무조건 실행이라는 특징을 지니지만, 예외 핸들러는 예외상황 발생 시 선별적 실행이라는 특징.
예외 핸들러는 일종의 약속.

예외 핸들러와 필터(Exception Handler & Filters)
__try
{
	//예외 발생 경계 지역
}
__except(예외 처리 방식) //EXCEPTION_EXECUTE_HANDLER, EXCEPTION_CONTINUE_EXECUTION, EXCEPTION_CONTINUE_SEARCH
{
	//예외 처리를 위한 코드 지역
}
__try 블록은 예외 상황이 발생 가능한 영역을 묶는데 사용된다.
만약 __try 블록에서 예외 상황이 발생하면 이어서 등장하면 __except블록에서 이 상황을 처리하게 된다.
예외상황을 처리하는 적절한 코드는 상황에 맞게 개발자가 직접 구현해야 한다.
__try 블록 내에서 예외 상황이 발생했음을 어떻게 감지하고, 처리하기 위해 어떻게 __except 블록으로 실행을
옮길까에 대한 부분은 그렇게 동작하도록 컴파일러가 코드를 구성하고 실행과정에서 Windows가 이를 돕는다.
예외처리 방식 부분을 예외필터라 하는데, __except 블록을 보면 함수처럼보이고 필터는 인자처럼 보인다.
하지만 인자절달을 위해 지정된 곳이 아닌 예외처리 메커니즘을 어떻게 동작시킬지 그 동작방식을 결정하기 위한 영역.
이곳에 올 수 있는 값은 총 3가지(필터 표현식) 중 가장 대표적인 것은 EXCEPTION_EXECUTE_HANDLER이다.
예외필터에 선언할 수 있는 값이 3가지라는 것은 예외처리 핸들러가 동작하는 방식이 세 가지라는 것을 의미.

먼저 예외필터 EXCEPTION_EXECUTE_HANDLER의 흐름을 본다.
17_5.cpp SEH_FlowView.cpp
예외상황이 발생하면 Windows에 의해 예외처리 메커니즘이 동작한다.
*p = NULL <--- 1. 예외상황 발생
__except() <--- 2. 예외처리 방식 결정
_tprintf() <--- 3. 예외처리 이후 실행
그래서 예외상황 발생한 이후 __try 안에 코드는 실행되지 않는다.
이것이 예외필터 EXCEPTION_EXECUTE_HANDLER의 특징.
__try 블록의 나머지 부분(예외 상황 발생 이후)을 건너 뛰게 되는 것.
또한 이렇게 예외를 처리하면 프로그램이 강제 종료되지 않는다는 점.
Windows는 예외가 적절히 처리된 것으로 생각하고 예외필터에서 명시하는 방식대로 실행을 이어간다.

예외상황이 발생하였음을 초기에 발견하는 것은 예외의 종류에 따라 하드웨어가 될 수도 있고, OS인 Windows가 될 수도 
있다. 하드웨어로부터 감지되는 예외상황이어도 최종적으로 예외상황을 알려서 예외처리 메커니즘을 동작시키는 것은
Windows이다.

예외 핸들러의 활용 사례 연구
EXCEPTION_EXECUTE_HANDLER에 대해서는 "건너 뛰기"를 떠올리자.
예외가 발생한 이후의 나머지 __try 블록을 건너 뛴다.
17_6.cpp SEH_Calculator_One.cpp
__try 블록의 범위는 단순히 예외발생 가능 영역만을 고려해서 결정하지 않는다.
예외처리 이후에 실행위치(얼마나 멀리 건너뛸 것인지)도 고려해서 결정해야만 한다.
처음부터 다시 시작하게끔 유도할 수도 있지만, 문제가 발생한 부분에 대해서만 정정하도록 _except 예외처리
블록을 구현하는 것도 가능한데 예외필터 표현식은 EXCEPTION_CONTINUE_EXECUTION이다.

처리되지 않은 예외의 이동
case별로 실행할 내용이 길다면(하나의 함수로 독립시킬 만큼), 각각을 하나의 함수로 묶는 것도 고려해야 한다.
17_7.cpp SEH_Calculator_Two.cpp
__try 블록 내에서 Divide 함수를 호출하고 있다.
Divide 함수 내에서 예외상황이 발생할 수 있다.
__try 블록 내에서 함수를 호출하면, 그리고 호출한 함수 내에서 예외상황이 발생한다면, 이 역시 __try 블록
내의 예외발생으로 인식하고 처리된다.
1. __try 블록 내 함수 호출 : Divide -> void Divide()
2. 예외상황 발생 이후 복귀 : a/b -> Divide
3. 나머지 __try 블록 실행 생략 : Divide -> __except
세분화하지 않고 그냥 예외발생 이후 나머지 __try 블록 실행 생략이라고 얘기할 수 있다.
Divide 함수가 호출될 때의 스택은 다음과 같은 구조로 구성된다.
         예외상황 발생
          /
|    Divide|─┐
|Calculator|←┘─┐ 예외처리 이동
|    _tmain|←──┘ 예외처리 이동
Divide 함수에서 예외가 발생했다.
예외가 발생한 Divide 함수 내에는 __try __except 블록이 존재하지 않아 예외의 처리가 Calculator로.
이 과정에서 Divide 함수의 스택 프레임은 반환된다.
Calculator에서 다시 확인하고 __try 블록이 있어 예외처리가 가능하다.
여기서도 못했으면 _tmain으로 이동한다.
정확히는 _tmain 함수 내에서 Calculator 함수를 호출한 위치로 이동을 한다.
그리고 _tmain 함수 내에서도 예외를 처리하지 못한다면 더 이상 예외를 넘길 스택 영역이 존재하지 않기 때문에
프로그램은 종료된다.

핸들러의 중복
예외 핸들러는 중복이 가능하다.
그리고 종료 핸들러와도 중복이 가능하다.
17_8.cpp SEH_Calculator_Three.cpp

정의되어 있는 예외의 종류와 예외를 구분하는 방법
예외상황에 따라서 처리하는 방식이 달라져야 하기 때문에 발생한 예외의 종류를 구분할 수 있어야 한다.
예외가 발생했을 때 어떠한 종류의 예외가 발생했는지를 확인하기 위해서 GetExceptionCode함수를 호출한다.
DWORD GetExceptionCode(void)
예외상황 발생 시 이 함수를 호출하면 값을 반환해 주는데, 이 값을 통해 "발생한 예외 정보"를 얻을 수 있다.
17_9.cpp GetExceptionCode.cpp
두 예외는 시스템에서 발생할 수 있는 예외로서 이미 약속된 예외의 종류에 해당한다.
사실 GetExceptionCode는 함수가 아닌 매크로이다.
EXCEPTION_STACK_OVERFLOW는 스택 메모리가 넘쳤을 때 발생하는 예외.
MSDN의 자세한 설명과 직관적인 이름이 있다.
GetExcetionCode 함수는 "__except 블록 내에서"나 "예외필터 표현식을 지정하는 위치"에서만 호출가능하다.
예외가 발생한 이후에 호출되는 함수이기 때문에 제한을 두고 있다.

EXCEPTION_CONTINUE_EXECUTION & EXCEPTION_CONTINUE_SEARCH
프로그램 개발 시 EXCEPTION_EXECUTE_HANDLER와 EXCEPTION_CONTINUE_EXECUTION만 사용하는 것이 좋다.
EXCEPTION_CONTINUE_EXECUTION은 문제된 부분만 재입력을 받게하자는 취지.
17_10.cpp SEH_Calculator_ContinueExecution.cpp
_tprintf(ReturnString());가 가능하다.
_tprintf 함수의 인자로는 반드시 문자열이 와야 하고 함수 호출문이 와도 된다.
다만 그 함수가 문자열(문자열의 주소값)을 반환하기만 하면 된다.
마찬가지로 __except 블록에서 예외 필터를 구성할 때도 반환값은 예외필터 표현식이어야 한다.
예외필터 표현식은 정수형 데이터로 정의되어 있으니 문제 없다.
예외 핸들러의 동작방식잉 EXCEPTION_CONTINUE_EXECUTION으로 결정났다.
그래서 __except블록의 내부를 실행하지 않고 예외가 발생한 위치로 다시 이동해 실행을 이어간다.
num2의 값이 0이 아닌 다른 값이 들어가면 문제없이 잘 동작하게 된다.
GetExceptionCode는 일반 함수 내부에서 호출할 수 없다.

EXCEPTION_CONTINUE_SEARCH
17_11.cpp SEH_Calculator_ContinueSearch.cpp
main에 있는 do~while문을 감싸는 예외처리 블록이 추가되었다.
BOOL Calculator()
{
	__except(EXCEPTION_CONTINUE_SEARCH){} 
}                          │
_tmain()                   │
{                          │
    __try{ Calculator(); } │
	__except(){} <─────────┘     
}
예외가 발생했고, 예외 핸들러의 구동방식 결정을 위해 __except의 필터를 참조한다.
EXCEPTION_CONTINUE_SEARCH는 다른 곳에 있는 예외 핸들러를 통해 예외를 처리하라는 뜻.
함수가 호출된 순서(스택)를 바탕으로 예외 핸들러를 찾게 된다.
Calculator 함수를 호출한 영역이 _tmain이므로, _tmain함수의 Calculator 함수 호출 문이 있는 위치에서
다시 예외 핸들러를 찾는다.
그래서 Calculator 함수 호출 문장을 감싸고 있는 __try__except 블록에 의해 예외는 처리된다.
기존과 동일한 방식으로 예외 핸들러를 찾게 된다.
_tmain함수에 있 는 예외 핸들러가 실행되어 재입력을 받은 숫자는 의미가 없다.
EXCEPTION_CONTINUE_SEARCH는 예외가 처리되어야 하는 위치를 별도로 지정하기 위한 용도로 사용.

문법 지향? 문법 지양!
다른 사람이 구현한 코드는 아무리 잘 구현한 코드라 할지라도 가독성이 떨어지는 법.
코드 문제일 수도 있지만, 스타일의 차이에서 비롯된 문제.
그리고 ANSI 표준 함수를 벗어나는 영역의 이해도 차이에서 올 수도 있다.
구조적 예외처리를 반영은 하되 너무 문법 지향적인 반영은 피하고 점진적 반영을 고려해야 한다.
그러면 이후 진행하는 프로젝트에서는 다른 개발자들 사이에서도 다양한 접근이 시도.
EXCEPTION_CONTINUE_SEARCH을 반드시 써야만 할 필요는 없어서 지양.
즉 세련미를 더해 갈 수 있는 범위 안에서 소극적인 접근을 시도해보자.

04 소프트웨어 기반의 개발자 정의 예외
개발자는 소프트웨어 예외상황을 정의 및 추가할 수도 있다.

소프트웨어 예외의 발생
소프트웨어 예외는 소프트웨어가 디자인될 당시에 결정되기 때문에 얼마든지 추가가 가능하다.
하드웨어 예외는 결정되어 있지만 소프트웨어 예외는 결정해야만 한다.
다음 함수는 소프트웨어 예외를 발생시키는 역할을 하는데, 예외의 종류를 늘릴 수 있다.
void RaiseException (
	DWORD dwExceptionCode, 1)
	DWORD dwExceptionFlags, 2)
	DWORD nNumberOfArguments, 3)
	const ULONG_PTR* lpArguments 4)
);
1)dwExceptionCode:발생시킬 예외의 형태를 지정한다.
2)dwExceptionFlags:예외발생 이후의 실행방식에 있어서 제한을 둘 때 사용한다.
3)nNumberOfArguments:추가정보의 개수를 지정한다.
4)lpArguments:추가정보를 전달한다.
이 함수는 예외발생을 알리기 위한 용도로 사용된다.
이 함수가 호출되면 SEH 메커니즘이 작동하면서, 흐름대로 예외처리가 전개된다.

가장 중요한 첫 번째 전달인자는 예외의 종류를 지정할 때 사용된다.
GetExceptionCode 함수를 호출할 때 얻게 되는 값을 지정한다고 생각할 수 있다.
하지만 아무렇게 정의할 수 없고, 예외를 정의하는 기본적인 방식이 이미 정해져 있다.

dwExceptionCode 구성
|31|30|29|28|27|  |  |  |  |  |  |  |  |  |  |16|15|  |  |  |  |  |  |  |  |  |  |  |  |  |  | 0|
   ↑    ↑  ↑                  ↑                                          ↑  
Severity│ Reseved       Facility Code                             Exception Code
Microsoft or Customer
이 구성은 마이크로소프트에서 정의한 것으로, 이 범위 내에서 사용자 정의 예외를 얼마든지 만들 수 있다.
31, 30번째 비트에는 예외의 심각도 수준을 나타내는 것으로
00:Success(성공)
01:Informational(예외의 알림)
10:Warning(예외에 대한 경고)
11:Error(강도 높은 오류 상황)
이 값들에 대한 절대 기준은 없다.
예외를 저의하는 과정에서 생각해보고 결정하는 순간 그것이 기준.
마이크로소프트에서 정의하고 있는 예외의 종류를 참조해 보면, 적용하는 기준을 가늠해 볼 수도 있다.
헤더파일 winnt.h를 참조하면 확인할 수 있다.
29비트에는 예외를 정의한 주체에 대한 정보를 담는다.
소프트웨어 예외는 Windows 운영체제 개발자들도 사용한다.
마이크르로소프트가 정의한 예외는 0을, 일반 개발자가 정의한 예외는 1을 채워 넣기로 약속.
28번째 비트는 시스템에 의해서 예약되어 있는 비트이다.
0으로 초기화한 상태에서 그냥 내버려 둔다.
16~27까지는 예외발생 환경 정보를 담게 된다.
다음 값 중에 하나를 지정한다.
Facility Code        Value
FACILITY_NULL          0
FACILITY_RPC           1
FACILITY_DISPATCH      2
FACILITY_STORAGE       3
FACILITY_ITF           4
FACILITY_WIN32         7
FACILITY_WINDOWS       8
FACILITY_SECURITY      9
FACILITY_CONTROL      10
FACILITY_CERT         11
FACILITY_INTERNET     12
FACILITY_MEDIASERVER  13
FACILITY_MSMQ         14
FACILITY_SETUPAPI     15
FACLIITY_SCARD        16
FACILITY_COMPLUS      17
MSMQ나 COM+에 대해 알고 있으면 대부분 이해할 수 있다.
FACILITY_INTERNET은 인터넷 관련 예외상황임을 기록하기 위해 쓰면 좋을 것이다.
0~15까지 인덱스는 예외의 종류를 구분하는 용도로 사용된다.
순수하게 정의할 내용은 여기에 해당한다.

RaiseException 함수의 정확한 사용방법과 함수 호출 이후의 예외처리 과정
17_12.cpp RaiseException.cpp
이렇게 해서 채워진 변수 DefinedException의 값은 0xE0000008이다.
실제 개발에서는 다음과 같이 정의해야 한다.
#define STATUS_INTEGER_DIVIDE_BY_ZERO ((DWORD)0xE0000008L)
등록한 예외정보는 GetExceptionCode 함수 호출을 통해 그대로 얻을 수 있다.
또한 GetExceptionCode 함수 호출을 통해 얻게 되는 예외 코드를 통해 부가적인 정보를 얻을 수 있다.
예를 들어 Windows 운영체제에서 발생시킨 예외인지, 개발자 라이브러리에서 발생한 예외인지를 알고자 한다면
__except(EXCEPTION_EXECUTE_HANDLER)
{
	DWORD exptType = GetExceptionCode();
	if(exptType & (0x01<<29))
	{
		//개발자가 발생시킨 예외
	}
	else
	{
		//MS 운영체제 예외
	}
}

RaiseException의 두 번째 전달인자 dwExceptionFlags에는 0이나 EXCEPTION_NONCONTINUABLE 둘 중 하나다.
0은 특별한 설정을 하지 않는다는 뜻이고, EXCEPTION_NONCONTINUABLE은 예외가 발생한 지점에서부터의 실행을
막겠다는 뜻.
17_13.cpp EXCEPTION_NONCONTINUABLE.cpp
예외가 발생하더라도 계속이어서 실행하게 된다.
두 번째 전달인자를 EXCEPTION_NONCONTINUABLE로 변경하면 아무런 출력이 이뤄지지 않는다.
즉 프로그램이 그냥 종료된 것.
예외가 발생하면 처리가 불가능한 경우가 있는데 이럴때 예외가 발생한 위치에서 실행을 재개하면 더 큰 문제가 발생한다.
그래서 EXCEPTION_NONCONTINUABLE은 EXCEPTION_CONTINUE_EXECUTION의 예외처리 흐름을 막는 용도로 사용된다.
EXCEPTION_NONCONTINUABLE은 Windows 운영체제 내부에서 사용하기 위해 정의한 것.

GetExceptionInformation
예외발생 시 함수 GetExceptionCode가 반환해 주는 정보보다 더 많은 정보를 얻기 원한다면, GetExceptionInformation
함수의 사용을 고려해 볼만하다.
이 함수는 "예외필터 표현식을 지정하는 부분"에서만 호출 가능하다.
LPEXCEPTION_POINTERS GetExceptionInformation(void);
GetExceptionInformation이 호출되면, EXCEPTION_POINTERS 구조체 변수의 주소값이 반환된다.
이 구조체 변수에는 예외에 관련된 정보가 채워지는데 알 필요가 있다.
typedef struct _EXCEPTION_POINTERS
{
	PEXCEPTION_RECORD ExceptionRecord;
	PCONTEXT ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;
EXCEPTION_POINTERS 구조체는 EXCEPTION_RECORD 구조체의 포인터(PEXCEPTION_RECORD)와 CONTEXT 구조체의 포인터
(PCONTEXT)로 구성되어 있다.
즉 예외발생 이후에 GetExceptionInformation 함수가 호출되면 다음과 같은 구조로 구성된 예외 관련 정보를 얻는다.
|ExceptionRecord| ----------> |프로세서 비종속적 예외 관련데이터|
|ContextRecord  | --           EXCEPTION_RECORD
EXCEPTION_POINTERS  \-------> |프로세서 종속적 데이터|
                               CONTEXT

EXCEPTION_POINTERS 구조체 변수에는 두 가지 정보가 채워지는데 하나는 예외 자체에 대한 정보가, 또 하나는
프로세서(CPU)의 레지스터 데이터를 비롯한 프로세서의 종속적인 정보가 채워진다.
프로세서 종속적인 데이터 정보는 시스템이 내부적으로 연산하는 과정에서 참조하게 된다.
그 선언이 궁금하면 winnt.h를 참조.

구조체 EXCEPTION_RECORD
이 구조체 변수에는 지금까지 봐왔던 예외 관련 데이터가 저장된다.
typedef struct _EXCEPTION_RECORD
{
	DWORD ExceptionCode;
	DWORD ExceptionFlags;
	struct _EXCEPTION_RECORD* ExceptionRecord;
	PVOID ExceptionAddress;
	DWORD NumberParameters;
	ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD, *PEXCEPTION_RECORD;

이 구조체의 멤버 중 RaiseException 함수와 관련있는 멤버 4가지를 봐본다.
void RaiseException (                    typedef struct _EXCEPTION_RECORD {
	DWORD dwExceptionCode,	-------------->	DWORD ExceptionCode;
	DWORD dwExceptionFlags, --------------> DWORD ExceptionFlags;
	DWORD nNumberOfArguments,    -----┐     struct _EXCEPTION_RECORD* ExceptionRecord;
	const ULONG_PTR* lpArguments ---┐ │     PVOID ExceptoinAddress;
);                                  │ └---> DWORD NumberParameters;
                                    └-----> ULONG_PTR ExceptionInformation[..];
										 }
RaiseException 함수의 첫 번째, 두 번째 전달인자로 구조체의 첫 번째, 두 번째 전달인자가 채워지게 된다.
RaiseException의 세 번째, 네 번째 전달인자는 main함수의 argc, argv와 같은 역할을 담당한다.
차이가 있다면 lpArguments는 ULONG_PTR로 선언되어 있다.
만약 특정 예외상황 발생 시에 예외와 관련된 정보를 담아 예외처리 영역에 전달하고 싶으면, RaiseException 함수의
세 번째, 네 번째 전달인자를 활용하면 된다.
이렇게 전달된 인자들은 EXCEPTION_RECORD 구조체의 다섯 번째와 여섯 번째 멤버를 채우게 된다.
따라서 GetExceptionInformation 함수 호출 시 추가로 전달되는 정보를 얻을 수 있다.
17_4.cpp RaiseExceptionParam.cpp
주목해서 봐야할 부분은 FilterFunction 함수 내부.

이것만은 알고 갑시다
1. SEH가 가져다 주는 이점
프로그램의 흐름에 관련된 코드와 예외를 처리하는 코드를 분리시켜 준다는 것도 큰 장점.
뿐만 아니라 프로그램을 디자인하는 데에도 많은 도움을 준다.
SEH의 특성을 잘 이용하면 프로그램의 흐름을 간결히 할 수 있고, 그만큼 코드의 양도 줄일 수 있다.
2. 종료 핸들러의 동작원리와 적용 범위에 대한 이해
종료 핸들러는 그 특성상 활용범위가 넓다.
파일을 개방하면 반드시 닫아줘야 하고, 커널 오브젝트의 핸들도 반드시 닫아줘야 한다.
종료 핸들러의 활용은 프로그램의 안전성에도 기여를 하고, 코드의 구성도 간결히 유지하는데 도움을 준다.
3. 대표적인 예외처리 방식
EXCEPTION_EXECUTE_HANDLER와 EXCEPTION_CONTINUE_EXECUTION의 예외처리 방식을 이해하자.
예외 핸들러를 활용해야 할 때 두 가지 중에서 하나를 선택하는 경우가 대부분.
4. 처리되지 않은 예외의 이동
처리되지 않은 예외는 스택 메모리 영역을 팝업해 가며 이동한다.
예외가 처리될 때까지 이동하는 특성이 있다.
5. 과도한 SEH 처리는 좋지 않다.
익숙하지 않은 개발자는 부담스러우니 최소한의 사용으로 보조를 맞추는 것이 좋다.

*/