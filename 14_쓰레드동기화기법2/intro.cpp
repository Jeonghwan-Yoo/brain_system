/*
아주 똑똑한 세 명의 개발자보다 서로 믿고 잘 어울리는 평범한 개발자 세 명이 더 큰일을 해내는 것이
가능하고 흔히 볼 수 있는 분야가 IT이다.
IT는 다양한 능력을 지닌 여러 사람들에게 정말로 많은 기회를 제공한다.

01 실행순서에 있어서의 동기화
임계 영역 접근을 제한하기 위한 동기화 방법이 아닌 쓰레드의 실행순서를 동기화하는 기법.
"메모리에 접근하는 쓰레드의 실행순서를 동기화한다."
즉 실행순서 동기화라는 것은 메모리 접근 동기화를 포함하는 개념.

생산자/소비자 모델
중요한 것은 순서이다.
생산자가 빵을 테이블에 올려 놓는 것이 먼저다.
그런 다음에야 소비자가 비로서 빵을 소비할 수 있다.
생산자는 문자열을 생성한다(입력받는다).
반면 소비자는 생산된 문자열을 소비한다(출력한다).
만약 하나의 쓰레드가 입력과 출력을 모두 담당한다면, 문제가 발생할 수 있다.
입력과 출력의 비율이 일치하다가 어느 순간 갑자기 입력의 양이 많아진 상황.
입력되는 문자열을 쓰레드가 감당하지 못하므로 어느 순간에는 문자열이 소멸되기 시작한다.
입력 -> 쓰레드 -> 출력

이를 해결하기 위해 두 개의 쓰레드를 활용해서 하나는 입력, 하나는 출력을 담당하게 하는 것.
그리고 그 사이에 메모리 버퍼를 둬서 두 개의 쓰레드가 입력 및 출력속도에 상관없이 독립적으로 실행되도록 한다.
입력 -> 쓰레드1 -> BUFFER -> 쓰레드2 -> 출력
쓰레드가 둘 이상이기 때문에 그에 따른 부담도 존재한다.
하지만 입력 및 출력속도가 시스템의 CPU 속도에 비해 현저히 느리다면, 좋은 선택이 될 수 있다.

이벤트(Event) 기반 동기화
Windows 개발자들은 쓰레드의 실행순서를 동기화한다고 하면, 가장 먼저 떠올리는 것이 이벤트 기반 동기화 기법이다.
세마포어나 뮤텍스와 같이 이 기법에서도 동기화를 위한 오브젝트가 사용된다.
"이벤트 오브젝트"를 보편적으로 '이벤트'라고 부른다.
이벤트를 생성 및 소멸시키는 함수와 이벤트를 소유 및 반환하는 함수가 전부.
상태(Signaled, non-Signaled)의 개념을 도입해서 설명한다.
상태에 따라서 실행되어야 할 쓰레드가 결정된다.

이벤트 오브젝트를 생성하는 데 사용되는 함수.
HANDLE CreateEvent (
	LPSECURITY_ATTRIBUTES lpEventAttributes, 1)
	BOOL bManualReset, 2)
	BOOL bInitialState, 3)
	LPCTSTR lpName, 4)
);
If the function fails, the return value is NULL.
1)lpEventAttributes:보안 속성을 지정할 때 사용한다. 핸들을 자식 프로세스에게 상속하고자 할 경우 NULL 이 아닌
다른 값을 전달.
2)bManualReset:가장 중요한 전달인자로서 수동 리셋모드로 이벤트 오브젝트를 생성하느냐, 자동리셋모드로 이벤트
오브젝트를 생성하느냐를 결정짓는다. TRUE가 전달될 경우 수동리셋모드 이벤트 오브젝트가, FALSE가 전달될 경우
자동리셋모드 이벤트 오브젝트가 생성된다는 것.
3)bInitialState:이벤트 오브젝트의 초기 상태를 결정짓는다. TRUE가 전달될 경우 Signaled 상태의 이벤트
오브젝트가 생성되고, FALSE가 전달될 경우 Non-Signaled 상태의 이벤트가 생성된다.
4)lpName:이벤트 오브젝트에 이름을 줄 경우에 사용하는 전달인자이다. NULL을 전달하면 이름없는 이벤트 오브젝트.

이벤트 오브젝트를 소멸시킬 때는 마찬가지로 CloseHandle 함수를 사용하면 된다.

쓰레드나 프로세스의 커널 오브젝트 경우, 초기에는 Non-Signaled 상태로 생성된다.
그러나 쓰레드나 프로세스가 종료될 경우 해당 커널 오브젝트는 Signaled 상태로 자동 변경된다.
그러나 이벤트 오브젝트는 자동으로 Signaled 상태가 되지 않는다.
함수 호출을 통해 직접 이벤트 오브젝트의 상태를 Signaled 상태로 변경해야 한다.
그리고 Non-Signaled 상태의 이벤트 오브젝트 핸들을 인자로 전달하면서 WaitForSingleObject 함수를 
호출한 쓰레드는 블로킹 상태가 된다.
그러나 Singaled 상태가 되면 마찬가지로 WaitForSingleObject 함수를 반환한다.
그러면 이벤트 오브젝트가 Singaled 상태가 되어 블로킹 상태에 있던 쓰레드가 빠져 나온다면, 빠져 나온 이후
(WaitForSingleObject 함수 호출 완료 이후) 이벤트 오브젝트는 어떤 상태일까?
만약에 Signaled 그대로라면, 수동리셋모드(Manual-Reset Mode) 이벤트 오브젝트라는 의미고, 
Non-Signaled 상태로 자동 변경되었다면, 자동리셋모드(Auto-Reset Mode) 이벤트 오브젝트라는 의미.

정리해보면 다음 특성을 이용해 쓰레드의 실행순서를 동기화하게 된다.
1)이벤트 커널 오브젝트는 프로그래머의 요청에 의해 Signaled 상태가 된다.
2)Non-Signaled 상태의 이벤트 오브젝트 때문에 WaitForSingleObject함수 호출이 블로킹되었다면, Signaled 상태가
되는 순간 블로킹된 함수를 빠져나오게 된다. 그리고 이때 자동 리셋 모드 이벤트 오브젝트라면, 
Non-Signaled 상태로의 변경은 자동으로 이뤄진다.

Manual-Reset Event
Non-Signaled ─────────────> Signaled
      ↑         SetEvent       │
	  └────────────────────────┘
	WaitForSingleObject+ResetEvent
Auto-Reset Event
Non-Signaled ─────────────> Signaled
	  ↑         SetEvent       │
	  └────────────────────────┘
		 WaitForSingleObject
수동 리셋 모드 이벤트이면 Signaled 상태에서 Non-Signaled 상태로의 변경을 위해 ResetEvent함수를 호출.
자동 리셋 모드 이벤트이면 WaitForSingleObject함수를 반환하면서 자동으로 Non-Signaled 상태로 돌아감.
수동 리셋 모드라고 해서 WairForSingleObject함수 호출이 필요없는 것이 아니다.
블로킹된 WaitForSingleObject 함수 호출을 빠져나올 경우 자동으로 Non-Signaled 상태로 변경되지 않으므로,
수동으로 ResetEvent함수를 호출해서 변경해줘야 하는 것이다.

BOOL ResetEvent (
	HANDLE hEvent 1)
);
If the function fails, the return value is zero.
1)hEvent:이벤트 오브젝트의 핸들을 인자로 전달한다. 전달된 핸들의 오브젝트는 Non-Signaled 상태가 된다.
BOOL SetEvent (
	HANDLE hEvent 1)
);
If the function fails, the return value is zero.
1)hEvent:이벤트 오브젝트의 핸들을 인자로 전달한다. 전달된 핸들의 오브젝트는 Signaled 상태가 된다.

14_1.cpp StringEvent.cpp
총 두 개의 쓰레드가 동작하는데 하나는 main 쓰레드이고 하나의 쓰레드를 추가로 생성했다.
문자열이 입력될 때까지, 문자열을 출력하는 쓰레드가 블로킹 상태에 놓인다.

수동리셋 모드 이벤트의 활용 예
수동 리셋 모드 이벤트가 아주 유용하게 사용되는 상황이 존재한다.
입력받은 문자열의 길이를 계산해 출력하는 역할의 쓰레드 하나의 쓰레드를 더 추가한다.
14_2.cpp StringEvent2.cpp
즉, 수동 리셋 모드 이벤트는 둘 이상의 쓰레드를 동시에 깨워서 실행해야 할 때 아주 좋은 도구가 될 수 있다.
수동 리셋 모드로 변경하게 되면 항상 제대로 출력되지 않는다.
두 개의 소비자 쓰레드가 순서대로 출력을 완료하면 문제가 되지 않는다.
그러나 문자열을 입력받은 생산자 쓰레드가 이벤트 오브젝트를 Signaled 상태로 변경하면, 두 개의 소비자 쓰레드는
동시에 블로킹 상태를 빠져 나와 실행을 재개한다.
그래서 기대했던 출력을 보장받지 못한다.
그렇다고 이것은 둘 이상의 쓰레드에 의해 접근되는 영역이 아니라 임계 영역은 아니다.
그렇다고 둘 다 소비자 역할의 쓰레드가 호출하는 함수여서 생산자/소비자 모델에 부합하지 않는다.
멀티 쓰레드 기반 프로그래밍을 하다 보면, 교과서적인 모델로 설명하기 애매한 상황들이 있다.
보다 넓고 포괄적으로 '동기화'라는 단어를 이해하고 느끼는 것이 중요.
그리고 이 문제를 뮤텍스를 활용해 해결할 것이다.
즉 두 가지 측면의 동기화가 필요해, 이벤트 오브젝트 기반의 동기화랑 뮤텍스 기반의 동기화가 필요하다.

02 이벤트 더하기 뮤텍스
이벤트와 뮤텍스를 동시에 사용해서 동기화해야 하는 상황은 실무 개발환경에서 자주 접하는 상황.
이벤트 오브젝트로는 생산자/소비자 모델을 구현하였고, 소비자가 둘 이상인 관계로 이 둘사이에서의
동기화를 위해 뮤텍스를 적용한다.

이벤트와 뮤텍스 오브젝트 적용 예제
14_3.cpp StringEvent3.cpp

03 Timer 기반 동기화
Windows에서는 Signaled 상태 개념이 중요하다.
이번 동기화 오브젝트는 정해진 시간이 지나면 자동으로 Signaled 상태가 되는 특성을 지닌다.
그래서 Waitable Timer.
타이머를 기반으로 쓰레드를 동기화한다는 것은 임계 영역 문제 해결을 위한 동기화와는 관점이 다르다.
여기서의 동기화는 쓰레드의 실행시간 및 실행주기를 결정하겠다는 의미.
그래서 타이머를 쓰레드 동기화 부분에서 다루기 다소 애매하다.
타이머 기반 동기화는 두 가지 형태로 구분 지을 수 있다.
1)수동 리셋 타이머:가장 일반적인 타이머로서, 알람 시계를 생각하면 된다. 
2)주기적 타이머:수동 리셋 타이머에 주기적인 특성이 가해진 형태로 이해하면 된다. 6시 이후 10분 주기로.

Manual-Reset Timer
타이머 오브젝트는 정해진 시간이 지나야 Signaled 상태가 되는 커널 오브젝트이다.
제일 먼저 해야 할 일은 타이머 오브젝트를 생성하는 일.
HANDLE CreateWaitableTimer (
	LPSECURITY_ATTRIBUTES lpTimerAttributes, 1)
	BOOL bManualReset, 2)
	LPCTSTTR lpTimerName 3)
);
If the function fails, the return value is NULL.
1)lpTimerAttributes:보안 속성을 지정하는 데 사용된다. 핸들을 자식 프로세스에게 상속하고자 할 경우 NULL이 아닌
다른 값을 전달.
2)lpTimerAttributes:타이머 오브젝트를 수동 리셋모드로 생성할 것인지, 자동리셋 모드로 생성할 것인지를 결정.
이벤트 오브젝트의 개념을 그대로 도입.
3)lpTimerName:타이머 오브젝트에 이름을 붙여줄 경우에 사용되는 전달인자이다. NULL을 전달하면 이름없는 타이머
오브젝트가 생성된다.
CreateEvent 함수와 비슷하다.
커널 오브젝트를 생성할 때 어떠한 상태로 둘 것인지를 결정하는 매개변수가 없다.
타이머 오브젝트의 특성 때문에 그렇다.
타이머는 시간이 지나서 Signaled 상태가 되어야 의미를 지닌다.
즉, 타이머 오브젝트가 생성되자마자 Signaled 상태가 된다면 아무런 의미가 없다.
때문에 타이머 오브젝트는 무조건 Non-Signaled 상태로 생성된다.

타이머 오브젝트를 생성한 후에 알람 시간을 설정한다.
BOOL SetWaitableTimer (
	HANDLE hTimer, 1)
	const LARGE_INTEGER* pDueTime, 2)
	LONG lPeriod, 3)
	PTIMERAPCROUTINE pfnCompletetionRoutine, 4)
	LPVOID lpArgToCompletionRoutine, 5)
	BOOL fResume 6)
);
If the function fails, the return value is zero.
1)hTimer:알람을 설정할 타이머 오브젝트의 핸들을 인자로 전달한다. 정해진 시간이 되면, 인자로 전달된 핸들의
커널 오브젝트는 Signaled 상태가 된다.
2)pDueTime:알람이 울리는 시간(커널 오브젝트가 Signaled상태가 되는 시간)을 지정하기 위한 매개변수이다.
+값이 전달되면 절대시간을 의미하게 되고, -값이 전달되면 상대시간을 의미하게 된다. 10억분의 1초(Nanoseconds)단위로
시간을 설정한다.
3)lPeriod:타이머가 주기적으로 알람을 울리게 할 때 사용하는 전달인자이다. 주기가 되는 시간 간격을 1/1000(Milli)
단위로 전달하면 된다. 0을 전달할 경우 주기적인 알람을 사용하지 않겠다는 의미.
4,5)pfnCompletionRoutine, lpArgToCompletionRoutine는 완료 루틴 타이머를 생성하는 용도의 함수.
6)fResume는 전원관리와 관련있는 매개변수로, 기본적으로 FALSE 전달을 원칙.

14_4.cpp ManualResetTimer.cpp
CreateWaitableTime와 SetWaitableTimer는 Windows 서버 버전을 기준으로 NT 4.0 이후부터 제공.
위의 선언이 있어야만 함수가 선언되도록 헤더파일 내부에 조건부 컴파일 형태를 취해놓고 있다.
없다면 에러가 발생하게 된다.
WINDOWS XP 이후 버전에서부터 제공하기 시작한 함수가 있다면 매크로 _WINNT_WIN32는 0x0501으로 정의.
제공되는 함수가 매크로 선언이 필요하다면, MSDN을 참조.
기억할 것은 이 매크로 정의는 헤더파일 선언 이전에 와야 한다.
64비트 정수를 표현하기 위한 자료형은 union으로 구성하지 않아도 제공하는 것이 있다(LONGLONG).
그러나 LARGGE_INTEGER는 64비트 정수를 표현하지 못하는 시스템에서 64비트 정수를 표현하기 위해
32비트 자료형 둘을 하나로 묶어서 선언된 자료형이기에 의미가 조금 다르다.
typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG HignPart;
	};
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
따라서 64비트 정수형 데이터를 표현하고자 하는 경우 LONGLONG(_int64)로 선언된 멤버 QuadPart를 활용한다.
대략 10초후에 MessageBeep 함수에서 들려주는 Windows 메시지 음을 듣게 된다.

Periodic-Timer
주기적 타이머는 일정 시간 간격으로 알람이 울리는 타이머를 의미한다.
10초 후에 매 5초마다 알람이 울리도록.
14_5.cpp PeriodicTimer.cpp
중간에 타이머를 해제하려면 다음 함수를 사용하면 된다.
주의할 것은 SetWaitableTimer 함수는 가동 중에 있는 타이머를 중지시키는 기능의 함수이지, 타이머를 소멸시키거나
할당된 자원을 반환하는 종류의 함수가 아니다.
할당된 자원을 반환하고 소멸을 시키고자 할 경우에는 CloseHandle 함수를 호출하면 된다.
BOOL CancelWaitableTimer (
	HANDLE hTimer 1)
);
If the function fails, the return value is zero.
1)hTimer:알람을 해제할 타이머 오브젝트의 핸들을 전달한다. 전달된 핸들의 타이머 오브젝트는 알람이 해제된다.
Inactive 상태가 된다.

이것만은 알고 갑시다
1. 실행순서 동기화와 이벤트 오브젝트
쓰레드의 실행순서가 중요한 이슈인 경우에는 실행순서 동기화를 고려해야 한다. 이를 위해서 Windows에서는
이벤트 오브젝트 기반의 동기화 기법을 제공한다.
2. 타이머 기반 동기화
타이머 역시 동기화 오브젝트이다. 다른 동기화 오브젝트와 달리 일정 시간이 지나면 자동으로 Signaled 상태가 되는
특성을 지니고 있어서 타이머라 한다.
3. 이벤트 더하기 뮤텍스
훨씬 복잡한 구성의 동기화가 필요한 경우. 쓰레드를 사용한다는 것은 여러 가지로 편리하고, 쓰레드 기반으로
프로그램을 구상할 경우 초반 설계도 훨씬 수월.

*/