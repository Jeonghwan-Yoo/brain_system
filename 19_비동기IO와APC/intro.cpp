/*
API는 DLL 인젝션이나 API 후킹 같은 기술이 중요.
요구되는 소프트웨어의 기술적 수준도 높아져 프로그래밍 실력 이상의 것이 필요하다.
전공을 포함한 폭넓은 학문적 지식이 필요.

01 비동기(Asynchronous) I/O
I/O는 중요하고 비동기I/O는 개념적으로나 실무적으로 중요한 내용이다.

비동기 I/O의 이해
프로그램의 성능에 문제가 있어 특정 수준 이상으로 향상시켜야 한다면, CPU 사용내용을 확인해봐야한다.(작업관리자)
CPU활용도에 심한 기복이 있으면 프로그램이 CPU를 활용하는 방식에 문제가 있다는 것을 의미한다.
그리고 이는 심각한 성능저하로 이어진다.
그리고 CPU나 메모리의 사양을 높인다고 해서 성능 향상에 큰 기대를 하기 어렵다.
기복이 심한 이유는 대부분 I/O 연산을 의심해볼 수 있다.
동영상 플레이어가 있다고 하고 서버로부터 데이터를 수신받아 플레이하는 방식이라 하자.

동기 I/O
데이터 수신   플레이   데이터 수신   플레이   데이터 수신
---------------------------------------------------------> CPU 동작 시간
데이터 수신 후 플레이라는 아주 기본적인 원칙을 철저히 지키고 있다.
그리고 데이터 수신과 플레이라는 두 개의 작업이 계속해서 반복적으로 이뤄진다.
데이터 수신은 CPU가 동작하지 않는다.
CPU 관전에선 플레이를 할 때에는 CPU가 동작한다 CPU연산에 의해서.
그러나 데이터를 수신할 때는 CPU가 동작하지 않는다.
I/O는 CPU와 거의 독립적으로 수행되는(CPU연산을 거의 필요로 하지 않는) 연산이기 때문.
발생하는 빈도수만큼 CPU가 일을 하지 않는 시간도 늘어나게 되며, 따라서 성능의 저하로 이어진다.
그래서 이 방법대로는 중간중간에 계속해서 버퍼링 현상이 발생할 것이다.
처음부터 끝까지 부드럽게 동영상을 감상하는 것은 절대 불가능하고 근본적인 문제가 있는 것.
또한 ANSI 표준 함수를 기반으로 간단한 텍스트 편집기 프로그램을 작성하는 경우에도 위와 같은 구조로 동작한다.
ANSI 표준 파일 입출력 함수를 사용해서 파일에 데이터를 쓰거나 읽을 경우, 작업이 완료될 때까지 호출된 함수가 
블로킹 상태(함수 호출이 완료되지 않은 상태)에 놓이기 때문이다.
이렇게 한번 호출되면, 완료될 때까지 블로킹되는 함수들을 블로킹 함수라 하고, 이 함수들을 활용한 입출력 연산을
가리켜 동기(Synchronous) I/O라 표현한다.
대부분의 편집기들은 대용량 파일을 열면 약간의 시간지연을 발생시킨다.
하지만 이정도로는 문제가 되지 않는다.
오히려 구현 관점에서 현명한 선택.

그러나 동영상이나 오디오를 플레이 하는 과정에서 중간중간에 끊김 현상이 발생하면 문제가 된다.
그래서 다음과 같은 구조로 프로그램을 변경하면 해결이 가능하다.
시스템 사양을 아무리 높여도 이 구조로 변경했을 때 얻게 되는 성능 향상과는 비교가 안되게 좋다.

비동기 I/O의 이해
데이터 수신
플레이
---------------------> CPU 동작시간
데이터를 수신하는 동안에도 플레이가 진행되는 상황.
어차피 데이터 수신은 CPU할당을 크게 요구하지 않는 작업이어서 플레이가 진행되는 동안 I/O작업이 병행될 수 있다.
I/O 작업은 I/O작업대로 계속 전개하면서, 버퍼링된 데이터를 기반으로 플레이를 병행하므로 사이사이 발생하는
시간지연 문제는 상당 폭 줄어든다.
데이터 수신속도가 빠르면 사라지는 효과.
이러한 구조의 I/O를 가리켜 비동기(Asynchronous) I/O라 한다.
비동기를 사용하면 CPU의 활용도는 모든 시간대에 걸쳐 평균적으로 고루 분포된다.
CPU 사용량이 시간대별로 고루 분포되어있는 그림은 아주 중요한 하나의 참고 모델.

I/O는 파일 I/O뿐 아니라 네트워크 I/O에서부터 다양한 디바이스와의 모든 I/O를 의미한다. 그리고 네트워크상에서
더 이슈화되는 주제이다.

중첩(Overlapped) I/O
Windows에서 제공하는 비동기 I/O 방식 중에서 가장 대표적인 것이 중첩 I/O이다.
예를 들어 대용량 파일 편집기가 있다고 가정하자.
편집을 위해 대용량 파일을 읽어 들이는 경우, 음악을 들려주는 특별한 기능을 추가했다고 하자.

동기I/O의 시나리오
fread call  fread return
↓            ↓
|데이터 수신  |
             | 사운드 플레이 |
			 ↑              ↑
		  play call     play return
---------------------------------------------> CPU 동작시간
ANSI 표준 함수인 fread 함수는 파일로부터 데이터를 읽어들이는 함수이니 호출은 I/O연산으로 볼 수 있다.
ANSI 표준 함수이기 때문에 데이터 수신이 완료될 때까지 함수는 반환하지 않고 블로킹 상태에 놓이게 된다.
반환하지 않으므로 사운드 플레이를 위한 play 함수를 호출하고 싶어도 할 수 없다.
fread 함수가 반환한 다음에야 가능.
그래서 결국 데이터를 읽어들이는 지루한 시간이 지난 다음에야 비로소 음악이 흐르는 결과.
문제는 블로킹 방식의 함수 때문이다.
이렇게 대부분의 함수들은 블로킹 방식이다.
함수가 호출되면 완료할 때까지 블로킹 상태에 놓인다.
이런 특성 때문에 데이터 수신과 플레이라는 두 가지 작업이 동시에 이뤄지지 못한다.

데이터도 읽으면서 플레이도 동시에 진행하려면 fread 함수가 넌블로킹 함수여야 한다.
넌블로킹함수는 작업의 완료에 상관없이 바로 반환해 버리는 특성을 지닌다.
반환 후에도 작업은 계속된다.
사실 fread 함수는 넌블로킹 방식이 되지 못한다.
ANSI 표준 함수에는 넌블로킹 개념이 없기 때문.
그러나 Windows 시스템 함수인 ReadFile 함수나 ReadFileEx 함수는 넌블로킹 방식으로 동작시킬 수 있다.

중첩 I/O의 시나리오
ReadFile call  ReadFile return
↓               ↓
|        데이터 수신         |
			    | 사운드 플레이 |
			    ↑              ↑
		     play call     play return
---------------------------------------------> CPU 동작시간
ReadFile 함수가 호출되자마자 바로 이어서 반환하고 있다.
여전히 데이터 수신 작업은 진행 중.
ReadFile 함수 호출도 반환된 상태여서 다른 함수를 호출할 기회도 있다.
이어서 play 함수를 호출한다.

중첩(Overlapped) I/O
위와 같은 방법으로 I/O의 중첩을 발생시킬 수 있다.
|        데이터 수신         |
    |        데이터 수신         |
        |        데이터 수신         |
	        |        데이터 수신         |
	             | 사운드 플레이 |
넌블로킹 함수 호출을 통해 여러 작업이 동시에 진행될 수 있다.
함수가 바로 반환하므로, 얼마든지 이어서 I/O요청을 할 수 있다.
I/O연산을 여러 번 중첩시킬 수 있다는 의미.

비동기 I/O방식은 서버와 같은 성능에 민감한 시스템이 아니라면 적용하는 기술이 아니다.
그래서 Windows98과 같은 클라이언트 운영체제에서는 지원하지 않는다.
높은 사양의 컴퓨팅 환경을 요구하고 속도에 대한 요구사항 떄문에 Windows는 이미 클라이언트 버전에서도
비동기 파일 I/O를 지원하기 시작했고, 향후 출시되는 Windows에서는 기존에 서버 버전에서만 지원되던 기능들을
완벽히 구사할 수 있을 것이다.
이러한 움직임은 Windows 커널 구조가 NT와 98로 양분되던 이후로 변화되었다.
비동기 I/O는 파일보다 네트워크 통신에서 더 큰 의미를 지닌다.
이와 유사한 모델로 파이프 통신이 맞는 모델.

중첩 I/O 예제
중첩 I/O는 비동기 I/O기반 모델 중 하나이다.
중첩 I/O는 대상이 파일이건, 파이프이건, 네트워크건 기본적인 코드 구성방식이 거의 동일하다.

중첩 I/O 기본 모델
OVERLAPPED--->EVENT┐Signaled state로 변경
    |             ↖┘
 인자 전달
    ↓
WriteFile Function call
    ↑
 인자 전달
    |
PIPE FILE_FLAG_OVERLAPPED

중첩 I/O 기반 파이프 통신 1단계
중첩 I/O기반 파이프 통신을 위해서는 중첩 I/O 가능한 비동기 특성을 띄는 파이프를 생성해야 하는데 파이프 생성 시
상수 FILE_FLAG_OVERLAPPED를 인자로 전달해서 비동기 특성을 부여하면 된다.

중첩 I/O 기반 파이프 통신 2단계
그 다음으로 OVERLAPPED 구조체 변수를 선언해야 한다.
typedef struct _OVERLAPPED {
	ULONG_PTR Internal;
	ULONG_PTR InternalHigh;
	union {
		struct {
			DWORD Offset;
			DWORD OffsetHigh;
		};
		PVOID Pointer;
	};
	HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;
멤버 Internal과 InternalHigh는 개발자를 위한 멤버가 아닌, Windows 시스템이 사용하기 위한 멤버이므로 무조건
0으로 초기화.
멤버 Offset과 OffsetHigh는 파일 포인터 위치를 지정하기 위한 멤버이고 일단 0으로 초기화.
OVERLAPPED가 화살표로 EVENT를 가리키는 것은 이벤트 오브젝트를 생성해 그 핸들을 OVERLAPPED 구조체 변수의
멤버 hEvent에 저장한다는 의미.
이 이벤트 오브젝트는 입출력 연산이 완료되었음을 확인하기 위한 것.
입출력 연산이 완료되면 멤버 hEvent가 가리키는 이벤트 오브젝트는 Signaled 상태가 된다.

중첩 I/O 기반 파이프 통신 3단계
구조체 변수 초기화가 끝나면, WriteFile(혹은 ReadFile) 함수를 호출하게 되는데, 반드시 FILE_FLAG_OVERLAPPED가
설정된 파이프와 OVERLAPPED 구조체 변수의 포인터를 인자로 전달한다.
그러면 WriteFile 함수는 중첩 I/O 방식으로 동작하게 된다.
19_1.cpp namedpipe_asynch_server.cpp
이벤트 오브젝트의 특성은 Signaled 상태로 생성되며, 사용자 리셋 모드의 이벤트 오브젝트이다.
입출력이 완료되었을 때 이를 확인하기 위한 용도로 생성한 이벤트인데, 초기 상태가 Signaled 상태가 되도록 구성.
초기 생성 시 Non-Signaled 상태가 되어야 한다.
이벤트 오브젝트는 입출력 완료를 확인하기 위한 용도로 반복적으로 사용되므로 Signaled 상태에서 Non-Signaled 상태로
변경시켜야 한다.
그래야 입출력이 완료될 때마다 Signaled 상태가 된다.
그런데 Non-Signaled 상태로 변경하는 코드는 없다.
이것은 ReadFile 함수의 특성을 통해 풀 수 있다.
OVERLAPPED 구조체 변수의 멤버(hEvent)로 등록된 이벤트 오브젝트는 ReadFile, WriteFile 함수 호출 시 자동으로
Non-Signaled 상태가 된다.
따라서 이벤트 오브젝트를 Signaled 상태로 생성해도 문제되지 않으며, 이를 명시적으로 Non-Signaled 변경할 필요없다.
WriteFile 함수가 중첩 I/O 방식으로 호출되었으니, 전송할 데이터 용량이 제법 크다면 여전히 I/O가 진행 중.
그러나 WriteFile 함수는 반환되어서 다른 연산을 진행할 수 있다.
실제 추가적인 작업을 하고 있진 않지만, 추가적인 작업을 하도록 요구하면 데이터 전송과 동시에 진행되는 것.
마지막으로 요청한 I/O 연산이 잘 마무리 되었는지 확인.
이때 사용하는 함수가 GetOverlappedResult 함수이다.
이 함수를 이용하면 실제 전송된 바이트 크기를 확인할 수 있다.

중첩 I/O에서는 WriteFIle, ReadFile 함수가 NULL을 반환했다고 해서 무조건 오류로 취급하고 프로세스를 종료하면 안된다.
일반적으로 블로킹 모드로 동작하는 I/O 연산에서는 I/O연산 자체에 병목현상(I/O 연산이 밀려들어 작업이 지체되는)이
발생하지 않는다.
왜냐하면 하나의 I/O연산이 완전히 끝날 때까지 블로킹 상태에 놓이기 때문이다.
그러나 중첩 I/O에서는 하나의 I/O연산이 끝나기 전에 새로운 I/O 연산이 들어올 수 있다.
떄문에 과도한 I/O 연산 요청으로 어느 순간 이후부터는 병목현상이 발생할 수 있다.
이때에는 기존에 진행 중이던 I/O 연산이 완료된 것을 확인한 후 다시 요청하면 된다.
결코 프로세스를 종료하거나 병목현상 처리를 위해 동분서주 할 일이 아니다.
따라서 WriteFile 함수가 호출된 이후, 그 결과가 오류 발생을 의미하는 NULL이라면 GetLastError 함수 호출을
통해 과도한 I/O 요청에 의한 문제인지(반환값이 ERROR_IO_PENDING인지), 아니면 더 심각한 문제인지를 확인하고
이에 대한 처리를 달리 해야 한다.
WriteFile 함수 호출 시 블로킹되지 않고 바로 반환하는지를 확인해야 한다.
CreateNamedPipe에서 파이프의 출력 버퍼와 입력 버퍼의 크기를 결정하기 위한 전달인자가 있다.
파일로부터 데이터를 읽어 들이기 위해, 그리고 전송하기 위해 할당한 버퍼 사이즈 BUF_SIZE의 반으로 구성해 놓았다.
WriteFile 함수를 호출하면서 전송할 데이터 크기가 100바이트이고, 파이프의 출력 버퍼 크기가 100바이트라고 하면,
동기 방식의(블로킹 함수 호출 방식의) I/O 연산이라도 결코 블로킹되지 않고 바로 반환하게 된다.
동기 방식 I/O 연산에서 최종 목적지인 클라이언트에게로 데이터 전송이 완료되어야만 반환하는 구조가 아닌,
전송을 위해 할당된 내부 메모리 버퍼에 복사가 이뤄지고 나면 반환하는 구조이기 때문이다.
그래서 출력 버퍼의 크기를 반으로 줄여 놓은 것.
그러면 WriteFile 함수가 블로킹될 수 있는 조건을 갖춰놓은 셈.
WriteFIle 함수 호출을 통해 전송하고자 하는 데이터 크기가 버퍼 크기의 두 배가 된것.
디버거로 브레이크 포인터를 서버와 클라이언트에 모두 걸어야 하는데, 서버는 WriteFile 함수를 호출하는 위치에 걸고,
클라이언트는 ReadFile 함수를 호출하는 위치에 걸어놓는다.
이 상태에서 서버와 클라이언트를 각각 브레이크 포인트 위치까지 실행시킨 다음에 서버 코드를 한 단계 Step Over한다.
즉 WriteFile 함수를 호출하는 것.
이 과정에서 블로킹되지 않고 바로 반환한다.
이로써 중첩 I/O 방식으로 처리되었음.

서버 코드의 WriteFile 함수 호출의 마지막 전달인자를 NULL로 변경해보자.
OVERLAPPED 구조체를 지정하지 않았으므로 블로킹 모드 함수로 동작하게 된다.
역시 브레이크 포인트를 동일한 위치에 걸어놓고 스텝오버 한다.
그러면 WriteFile 함수 호출이 블로킹되는 것을 확인할 수 있다.
결과가 이상하면 출력 버퍼의 크기를 조금씩 줄이거나 한 번에 전송할 데이터의 크기를 늘려보자.

예제에서는 I/O 연산이 완전히 완료된 것을 확인하고 나서, 다음 I/O 연산으로 넘어가는 구조이기 때문에
ERROR_IO_)PENDING 오류에 대한 처리가 불필요하다. 

I/O 연산이 완료된 이후에 전송된 데이터 크기 확인을 위해 호출한 GetOverlappedResult 함수
BOOL GetOverlappedResult (
	HANDLE hFile, 1)
	LPOVERLAPPED lpOverlapped, 2)
	LPDWORD lpNumberOfBytesTransferred, 3)
	BOOL bWait 4)
);
If the function fails, the return value is zero.
1)hFile:입력 및 출력결과 확인을 위한 파이프 핸들을 전달한다. 이곳에 파이프 핸들뿐 아니라, 다른 오브젝트의 핸들도
지정할 수 있다. 이 함수는 중첩 파이프 I/O만을 위한 함수가 아닌 모든 중첩 I/O를 위한 일반적인 함수.
2)lpOverlapped:WriteFile, ReadFile 호출 시 마지막 인자로 전달했던 OVERLAPPED 구조체 변수의 주소값을 전달.
3)lpNumberOfBytesTransfered:실제 전송이 완료된 바이트 크기를 얻기 위해 변수의 주소값을 인자로 전달.
4)bWait:I/O 연산이 끝나지 않은 상황에서의 처리를 결정한다. TRUE를 전달하면 I/O 연산이 끝날 때까지 기다린다.
반대로 FALSE를 전달하면 I/O 연산이 끝나지 않아도 반환한다.

완료루틴(Completion Routine) 기반 확장 I/O
중첩 I/O의 불편한 점은 입력 및 출력이 완료되었음을 확인하는 번거로운 작업을 항시 고려해야 한다.
각각의 I/O 연산을 A,B,C라 하고, I/O 연산이 완료되었을 때, 이어서 실행해야 할 다음 연산이
Routine D,E,F라고 하면 I/O연산 A가 끝이 났을 때 루틴 D가 실행되어야 한다.
루틴은 보통 함수로 구성되어 함수 D를 호출한다고 생각해도 된다.
여기서 루틴은 I/O 연산이 완료되었을 때 실행되는 루틴으로 Completion Routine이라고 한다.
그리고 이런 프로그램을 구현해야 한다면, 중첩I/O 방식을 적용하면 각각의 I/O 연산을 완료했을 때,
이어지는 완료루틴의 호출을 고민해야 한다.
이를 위한 콘트롤을 프로그램 코드상에서 직접해야만 한다.
쉽게 말하면 I/O A가 완료되었을 때, 루틴 D가 실행되도록 하는 역할을 직접 구현해야 하는 것.
완료된 I/O가 A인지 B인지 구분해야 하기 때문에 코드가 복잡해질 것이다.
연산 A가 완료되면 자동으로 루틴 D를 실행시키는 방법은 완료루틴 기반 확장 I/O이다.
완료루틴 기반 확장 I/O는 입출력 연산도 기본적으로 중첩방식이다.
따라서 확장 I/O를 기반으로 I/O 연산을 할 때에도 연산이 중첩된다.
확장 I/O 제공 기능 = 중첩 I/O 제공 기능 + 알파
여기서 알파는 루틴 컨트롤을 자동으로 해준다는 것.

확장 I/O 기본 모델
OVERLAPPED
     |
 인자 전달
     ↓
WriteFileEx Function call ← 인자전달 - Completion Routine
     ↑
 인자 전달
     |
PIPE FILE_FLAG_OVERLAPPED

PIPE 생성 시 FILE_FLAG_OVERLAPPED 속성을 주는 것은 같다.
OVERLAPPED 구조체 변수를 지정해 주는 것도 같다.
그러나 이벤트 오브젝트를 생성하지 않는다.
어차피 입력 및 출력이 완료되면, 해당 완료루틴(함수)이 자동으로 호출되기 때문에 이벤트 오브젝트가 필요없다.
그리고 WriteFile/ReadFile 함수 대신에 WriteFileEx/ReadFileEx 함수를 호출한다.
이 함수는 입력 및 출력 연산이 완료되었을 때, 호출되어야 할 완료루틴 지정을 위한 매개변수가 추가로 선언 되어 있다.
즉 확장 I/O를 위해 디자인된 함수.
BOOL WriteFileEx (
	HANDLE hFile, 1)
	LPCVOID lpBuffer, 2)
	DWORD nNumberOfBytesToWrite, 3)
	LPOVERLAPPED lpOverlapped, 4)
	LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine 5)
);
1)hFile:데이터 전송(쓰기)의 대상 핸들을 지정한다. 여기 인자로 전달되는 핸들은 FILE_FLAG_OVERLAPPED 속성이 지정.
2)lpBuffer:전송할 데이터를 지니는 버퍼의 주소를 지정한다.
3)nNumberOfBytesToWrite:전송할 데이터의 크기를 지정한다.
4)lpOverlapped:OVERLAPPED 구조체 변수의 포인터를 지정한다.
5)lpCompletionRoutine:출력 연산 완료 시 자동으로 호출되는 완료루틴의 지정을 위해 사용된다.

typedef VOID (WINAPI * LPOVERLAPPED_COMPLETION_ROUTINE) (
	DWORD dwErrorCode,
	DWORD dwNumberOfBytesTransfered,
	LPOVERLAPPED lpOverlapped
);
LPOVERLAPPED_COMPLETION_ROUTINE 선언을 통해 완료루틴의 선언 형태를 파악할 수 있다.
LPOVERLAPPED_COMPLETION_ROUTINE은 완료루틴을 가리킬 수 있는 함수 포인터의 typedef 선언이기 때문.
VOID WINAPI FileIOCompletionRoutin (
	DWORD dwErrorCode,
	DWORD dwNumberOfBytesTransfered,
	LPOVERLAPPED lpOverlapped
);
BOOL ReadFileEx (
	HANDLE hFile, 1)
	LPVOID lpBuffer, 2)
	DWORD nNumberOfBytesToRead, 3)
	LPOVERLAPPED lpOverlapped, 4)
	LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine 5)
);
1)hFile:데이터 수신 대상을 지정한다. 여기 인자로 전달되는 핸들은 FILE_FLAG_OVERLAPPED 속성을 지녀야 한다.
2)lpBuffer:데이터 수신을 위한 버퍼의 주소를 지정한다.
3)nNumberOfBytesToRead:읽어 들일 데이터의 최대 크기를 바이트 단위로 지정한다. 보통 버퍼의 최대 길이를
바이트 단위로 지정한다.
4)lpOverlapped:OVERLAPPED 구조체 변수의 포인터를 전달한다.
5)lpCompletionRoutine:입력 연산 완료 시 자동으로 호출되는 완료루틴을 지정한다.

WriteFile, ReadFile 함수에서는 완료된 입출력 데이터 크기를 얻기 위해 변수의 주소값을 전달할 수 있었다(4번째 인자).
그러나 WriteFileEx, ReadFileEx 함수에는 이에 대응하는 매개변수가 없다.
WriteFileEx, ReadFileEx는 오로지 비동기, 그 중에서도 확장 I/O를 위해 디자인된 함수이다.
첫 번째 인자로 전달되는 핸들이 반드시 FILE_FLAG_OVERLAPPED 속성을 지닐 것을 요구한다.
때문에 완료된 출력 및 입력 데이터 크기를 얻기 위한 매개변수는 존재할 이유가 없다.
반환하는 시점에서 얻을 수 있는 정보가 아니니 말이다.
19_2.cpp completion_routine_file.cpp
FileIOCompletionRoutine의 첫 번째 전달인자를 통해 시스템 에러코드가 전달된다.
여기로 전달되는 값만 보더라도 어떤한 문제가 생겼는지 알 수 있다.
따라서 GetLastError 함수를 별도로 호출하지 않아도 된다.
MSDN에서 FileIOCompletionRoutine 함수를 찾아보면, 시스템 에러코드를 확인할 수 있도록 링크가 걸려 있다.
에러코드 0은 에러가 발생하지 않았음을 의미한다.
FileIOCompletionRoutine의 두 번째 전달인자를 통해 완료된 입력 및 출력 데이터의 크기가 전달된다.
FileIOCompletionRoutine의 세 번째 전달인자를 통해 WriteFileEx 함수 호출 시 전달된 OVERLAPPED 구조체
변수의 포인터가 전달된다.
따라서 OVERLAPPED 구조체의 이벤트 오브젝트 핸들을 저장하기 위한 멤버 변수를 간단한 데이터 전송의 용도로
사용하는 것이 가능하다.
가장 중요한 것은 FileIOCompletionRoutine 함수가 적절히 호출되느냐.
문제는 생성한 쓰레드(프로세스 생성 시 기본 흐름의 주체가 되는 메인 쓰레드)는 알림 가능 상태(Alertable State)가
아니었다는 점.
주석 처리를 해제하고 다시 실행해보면 원하는 결과를 얻을 수 있다.

FileIOCmopletionRoutine 함수와 같이 Windows 시스템에 의해 자동으로 호출되는 함수를 콜백(Callback)함수라 한다.

알림 가능한 상태(Alertable State)
I/O연산이 완료되어 완료루틴을 실행할 차례가 되면, 바로 완료루틴이 실행되어야 할 텐데, Windows는 완료루틴
실행 타이밍을 결정할 수 있도록 하고 있다.
프로그램 흐름을 컨트롤 할 수 있는 요소가 하나 더 생겼으니 좋은 일.
SleepEx 함수가 완료루틴을 실행하라는 신호를 주는 용도로 사용되고 있다.
DWORD SleepEx (
	DWORD dwMilliseconds, 1)
	BOOL bAlertable 2)
);
1)dwMilliseconds:쓰레드의 실행을 잠시 멈추는데 사용하는 Sleep 함수의 전달인자와 동일한 역할을 한다.
전달되는 값을 1/1000초 단위로 멈추게 한다.
2)bAlertable:FALSE가 전달되면, Sleep 함수와 완전히 동일한 형태가 된다. 그러나 TRUE가 전달되면
SleepEx 함수에서 빠져 나오는 조건이 Sleep 함수에 비해 하나 더 추가된다.
TRUE가 전달되면 이 함수를 호출한 쓰레드를 알림 가능한 상태(Alertable State)로 변경한다.

두 번째 전달인자로 TRUE가 전달되었다.
그러면 쓰레드는 일단 알림 가능한 상태가 되는데, 이 상태에서는 호출되어야 할 완료루틴의 호출이 이뤄진다.
물론 완료루틴 실행 후에는 SleepEx 함수도 반환하게 된다.
호출되어야 할 완료루틴이 둘 이상인 경우에는 모두 다 호출된다.
따라서 위 함수를 중복해서 호출할 필요는 없다.
만약에 완료된 I/O가 없어서 호출할 완료루틴도 없고, 첫 번째 전달인자를 통해 전달된 시간도 지나지 않았다면,
위 함수는 계속해서 블로킹 상태에 놓이게 된다.
첫 번째 전달인자 dwMillisesconds에서 지정한 시간이 다 되면 0을 반환하며 함수를 빠져 나오고, 완료루틴이
실행되어 함수를 빠져나올 때는 WAIT_IO_COMPLETION을 반환한다.
이를 잘 활용하면 I/O 연산이 끝나고 난 다음에 처리해야 할 일들을 상황에 따라서 뒤로 미룰 수 있다.
예를 들어 비동기 I/O 연산을 중첩시켜 총 열 개의 I/O 연산을 실행할 때 속히 진행하는 I/O 연산들이어서 중첩.
네 번째 비동기 I/O 연산까지 잘 실행하고 다섯 번째 비동기 연산을 실행하려는데, 그 순간에 첫 번째 I/O 연산이 완료.
결국 첫 번째 I/O에 연결된 완료루틴이 실행된다.
그리고 다시 다섯 번째 비동기 I/O 연산을 실행하려는데 네 번째 I/O 연산들도 줄줄이 완료가 되어서 연결되어 있는
완료루틴이 실행되어 버린다.
결국 다섯 번째 I/O 연산을 실행하기까지는 제법 긴 시간이 소요된다.
만약 알림 가능한 상태라는 개념이 없었더라면 실제로 고민하고 해결해야 할 문제이다.
그런데 다행히도 완료루틴이 실행되는 타이밍을 프로그래머가 결정할 수 있다.
열 번째 I/O 연산이 실행될 때까지 알림 가능한 상태에 빠지지 않게만 하면 I/O 연산을 얼마든지 중첩시킬 수 있다.
SleepEx 함수와 마찬가지로 쓰레드를 알림 가능한 상태로 만드는 기능을 지닌 함수들
WaitForSingleObjectEx, WaitForMultipleObjectsEx
이 함수들도 알림이 가능한 상태로 변경하기 위한 마지막 전달인자가 존재한다.

OVERLAPPED 구조체의 파일 위치 정보
19_3.cpp nonBlocking_fileIOErr.cpp
하지만 파일에서 확인할 수 있는 문자열은 마지막 문자열 하나다.
그 이유는 동기화된 파일 I/O 방식에 너무나도 익숙해져 있기 때문.
WriteFileEx와 같은 함수 호출이 성공할 것이라는 믿음은 파일입출력 연산 시, 파일 위치 정보가 갱신되기 때문.
핸들 hFile이 가리키는 파일의 커널 오브젝트 안에는 파일의 위치 정보를 담고 있는 멤버변수가 존재한다.
파일 포인터는 동기화된 입출력 함수 호출이 완료될 때마다 완료된 크기만큼 갱신이 이뤄진다.
때문에 순차적으로 데이터를 읽거나 쓸 수 있다.
그러나 이것은 어디까지나 동기화된 파일 I/O에만 해당하는 말.
함수 호출이 완료되지 않은 상태에서 파일 포인터가 옮겨져 있을 보장이 없다.
그리고 연속해서 중첩되어 데이터 출력 연산이 진행 중이라 어느 장단에 맞춰 파일 포인터의 위치를 결정할지 모름.
즉, 비동기 I/O에서 커널 오브젝트에 존재하는 파일의 위치 정보는 의미 없다.

해결책은 OVERLAPPED 구조체의 멤버 중에서 일부는 데이터 입출력 시작 위치를 지정하는 용도로 
사용된다. (Offset, OffsetHigh).
이 멤버들을 활용하는 것이 해결책.
물론 데이터 입출력 시작 위치를 개발자가 직접 계산해야만 한다.
19_4.cpp nonBlocking_fileIO.cpp
WriteFileEx 함수를 총 세 번 호출하는데, 각각의 호출마다 독립된 OVERLAPPED 구조체 변수를 선언하고 있다.

타이머에서의 완료루틴
BOOL SetWaitableTimer (
	HANDLE hTimer,
	const LARGE_INTEGER* pDueTime,
	LONG lPeriod,
	PTIMERAPCROUTINE pfnCompletionRoutine, 1)
	LPVOID lpArgToCompletionRoutine, 2)
	BOOL fResume
);
If the function fails, the return value is zero.
1)pfnCompletionRoutine:완료루틴을 지정한다.
VOID CALLBACK TimerAPCProc (
	LPVOID lpArgToCompletionRoutine,
	DWORD dwTimerLowValue,
	DWORD dwTimerHighValue
);
전달인자 dwTimerLowValue와 dwTimerHighValue을 통해 타이머가 Signaled 상태가 된 시간 정보가 전달되며,
첫 번째 전달인자 lpArgToCompletionRoute는 SetWaitableTimer 함수의 다섯번째 전달인자가 그대로 전달된다.
2)lpArgToCompletionRoutine:타이머 완료루틴의 첫 번째 전달인자로 그대로 전달된다.
19_5.cpp CompletionRoutinePeriodicTimer.cpp

지금까지의 내용 정리
Windows는 기본적으로 두 가지 방식의 비동기 I/O를 지원하고 있는데 하나는 중첩 I/O방식이고, 또 하나는
완료루틴 확장 I/O 방식이야.
블로킹 함수는 호출된 함수가 일을 다 끝낸 다음에 반환하는 함수를 말하는 것.
넌블로킹 함수는 호출되자마자 바로 반환을 하기 때문에 일이 완료되는 시점과 반환하는 시점이 서로다른 함수들.
동기 I/O는 블로킹 함수를 사용하는 것이 보통이고, 비동기 I/O는 넌블로킹 함수를 주로 사용.
그래서 중첩 I/O와 완료루틴 I/O는 비동기 I/O에 속하고, 다만 완료루틴의 경우 I/O가 완료될 때 지정된
함수가 호출된다는 특징을 지니고, 중첩 I/O는 그러한 장치가 없기 때문에 중간에 I/O가 완료되었음을
확인하는 과정이 별도로 필요하다는 차이점.
어떻게 I/O가 완료되고 나면 완료루틴이 호출되는지는 APC에 대한 공부.

02 APC(Asynchronous Proceduce Call)
ApC는 비동기 함수 호출 메커니즘을 의미한다.
완료루틴도 내부적으로는 이 APC를 활용하여 구현되어 있다.
완료루틴 구성과정에서 호출하는 ReadFileEx(WrtieFileEx) 함수와 SetWaitableTimer 함수는 APC 메커니즘을
기반으로 구현된 함수들이다.

APC의 구조
두 가지로 나뉘는데 하나는 User-mode APC이고 다른 하나는 Kernel-mode APC이다.
Kernel-mode APC는 다시 Normal kernel-mode APC와 Special kernel-mode APC로 나뉘는데, User-mode APC만 언급.
모든 쓰레드는 자신만의 APC Queue라는 것을 가지고 있다.

APC Queue 구조
                                   I/O 완료시                APC Queue
Function & Param --- writeFileEx() ----------> |Function&Param Function&Param ... | ---> 실행
완료루틴을 구성하는 과정에서 WriteFileEx 함수가 호출되고 있다.
그리고 이때에 인자로 전달된 함수(완료루틴) 포인터와 매개변수 정보가 쓰레드의 APC Queue라는 곳에 저장되고 있음을
보여준다(I/O 완료시).
APC Queue는 쓰레드별로 독립적이다.
모든 쓰레드는 자신만의 APC Queue를 지니고 있다.
이처럼 APC Queue에는 비동기적으로 호출되어야 할 함수들과 매개변수 정보가 저장된다.
그러나 저장되었다고 해서 함수가 바로 호출되는 것은 아니다.
쓰레드가 알림 가능 상태에 놓이게 될 때에 비로소 호출되는 것.
사실 완료루틴이라는 것 자체가 쓰레드별로 독립적인 메커니즘이라는 결론.

APC Queue의 접근
APC Queue에 함수 정보를 전달할 수 있는 방법은 총 3가지이다.
WriteFileEx, ReadFileEx, SetWaitableTimer.
그러나 다음 함수를 이용하면 직접적으로 APC Queue에 호출하고자 하는 함수 정보를 전달할 수도 있다.
DWORD QueueUserAPC (
	PAPCFUNC pfnAPC, 1)
	HANDLE hThread, 2)
	ULONG_PTR dwData 3)
);
If the function fails, the return value is zero.
1)pfnAPC:비동기로 호출될 함수를 지정한다. 이 함수를 통해 지정할 수 있는 함수의 타입은 다음 형태로 제한.
VOID CALLBACK APCProc(ULONG_PTR dwParam);
2)hThread:비동기 함수 정보를 추가할 APC Queue를 지정한다. APC Queue를 소유하는 쓰레드 핸들을 지정한다.
3)dwData:APC Queue에 등록된 함수 호출 시 전달할 인자를 지정한다.
19_6.cpp APCQueue.cpp

이것만은 알고 갑시다
1. 다음 여섯 단어를 충분히 설명하는 하나의 문장을 만들어 보자
비동기I/O, 동기I/O, 블로킹 함수, 넌블로킹 함수,, 중첩, 완료루틴.
2. 완료루틴 I/O, 중첩 I/O

*/