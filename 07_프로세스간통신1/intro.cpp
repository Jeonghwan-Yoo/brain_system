/*
커널 오브젝트의 두 가지 상태와 핸들 테이블에 대한 개념을 이해하기 위한 IPC

01 프로세스간 통신(IPC)의 의미
IPC는 Inter-Process Communication으로 프로세스 사이의 통신.
통신이란 기본적으로 데이터를 주고 받는 행위이다.
따라서 둘 이상의 프로세스가 데이터를 주고 받는 행위이다.

프로세스 사이에서 통신이 이뤄지 위한 조건
서로 통신하고자 하는 프로세스가 서로 만날 수 있는 여건(공유하는 메모리 영역이 존재)이 허락되면 프로세스간
통신은 쉽지만 허락되지 않는다면, 전화나 메신저와 같은 보조 수단이 필요하다.

프로세스들이 서로 만날 수 없는 이유
결론적으로 프로세스들은 서로 만나서 데이터를 주고 받는 것이 불가능하다.
프로세스들은 자신에게 할당된 메모리 공간 이외에는 접근이 불가능하다.
따라서 두 프로세스가 만날 수 있는 접선 장소를 마련하는 것은 불가능하다.

프로세스들이 서로 만나지 못하게 디자인한 이유
만약 다른 영역에 접근이 가능하다면, MP3 Player와 Word프로세스를 실행하면 문제가 되어 문자가 깨지거나 할것이다.
결국 프로그램의 신뢰도는 낮아진다.
그래서 프로세스는 자신에게 할당된 메모리 공간 이외에는 접근이 불가능하다.
이렇게 제한을 가하는 이유는 안전성을 높이기 위한 것.

02 메일슬롯 방식의 IPC
Windows에서는 다양한 IPC기법을 제공하고 있다.
원리를 이해하는 것이 중요하다.

메일슬롯(Mail Slot) 원리
메일슬롯은 파이프와 더불어 대표적인 IPC기법이다.
메일슬롯은 편지를 넣을 수 있는 가느다란 우체통의 입구를 의미한다.
선형적인 메모리 구조의 특성을 만영하기위해 슬롯이라고 한 것 같다.
기본 원리는 "데이터를 주고 받기 위해서 프로세스가 우체통을 마련하는 것."
메일슬롯이 바로 접선 장소를 대신해 주는 역할을 한다.
Receiver는 밖에다가 우체통을 하나 걸어둔다.
Sender는 Receiver의 주소를 통해 Receiver의 메일슬롯을 향해 데이터를 날린다.
그러면 Receiver는 메일슬롯을 통해 데이터를 얻게 된다.

메일슬롯(Mail Slot) 구성을 위해 필요한 요소
첫째로 Receiver가 준비해야 할 것에 대해서 먼저 살펴보자
Receiver에 해당하는 프로세스는 우체통을 생성해야 한다.
HANDLE CreateMailslot(
	LPCTSTR lpName, 1)
	DWORD nMaxMessageSize, 2)
	DWORD lReadTimeout, 3)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes 4)
);
If the function fails, the return value is INVALID_HANDLE_VALUE
1)lpName:생성하는 메일슬롯의 이름을 결정하는 데 사용된다. 쉽게 말해 주소를 지정하는 것.
\\computername\mailslot\[path]name
2)nMaxMessageSize:메일슬롯의 버퍼 크기를 지정하는데 사용된다. 우체통의 크기를 지정하는 데 사용되는 인자.
만약에 0이 전달되면 시스템이 허용하는 최대 크기로 지정된다.
3)lReadTimeout:메일슬롯을 통해 전송된 데이터를 읽기위해서 파일 입출력 함수인 ReadFile함수가 사용된다.
만약에 메일슬롯으로부터 읽어 들일 데이터가 있다면, 이 데이터들을 읽어 들이면서 ReadFile함수를 빠져나온다.
그러나 메일슬롯이 비어있다면 데이터가 채워질 때까지 ReadFile은 반환하지 않고 Blocking상태에 놓인다.
lReadTimeout은 최대 블로킹 시간을 ms단위로 지정하는 데 사용된다.
따라서 0을 인자로 전달하면 데이터가 있든없든 블로킹상태없이 빠져나와 다음단계를 실행한다.
상수 MAILSLOT_WAIT_FOREVER를 인자로 전달하면 데이터가 존재할 때까지 블로킹 상태에 놓인다.
4)lpSecurityAttributes:핸들을 상속하기 위한 용도로도 사용된다.
함수의 반환 타입은 커널 오브젝트의 핸들이 반환됨을 알 수 있다.
메일슬롯도 커널에 의해서 관리되는 리소스이기 때문에 커널 오브젝트가 더불어 생성되고, 이 커널 오브젝트 핸들이 반환.

둘째로 Sender가 준비해야 할 것에 대해서 살펴보자
Sender는 데이터를 Receiver에게 보내는 역할을 한다.
Sender는 Receiver가 만들어 놓은 메일 슬롯의 이름을 알아야 한다.
주소는 프로그램 코드상에서 표현하게 된다.
일반적으로 Sender와 Receiver는 동시에나 같은 팀에서 개발을 진행하므로 알 수 있다.
이제 주소가 적혀 있는 편지봉투를 마련하고 편지봉투를 이용해 데이터를 전송하기만 하면 된다.
주소가 "\\.\mailslot\mailbox'라고 하고 주소가 적힌 편지봉투를 마련해 데이터를 전송해보자(아스키코드 기반)
//1단계. 편지봉투나 편지봉투를 보내기 위한 통로를 마련하는 작업
HANDLE nMailSlot;
hMailSlot = CreateFile("\\\\.\\mailslot\\mailbox", ...);
//CreateFile함수의 호출을 통해 이전에 생성한 메일슬롯에 데이터를 보내기 위한 기반을 마련한다.
//메일 슬롯에 데이터를 보내기 위해 주소 정보를 담고 있는 리소스를 생성하는 작업.
//이 과정에서 반환되는 핸들은 메일슬롯으로 데이터를 전달하는 용도로 사용.
//해당 주소의 메일슬롯을 개방한다는 의미는 데이터를 전송하기 위한 데이터 스트림을 형성하는 것.
//데이터를 담은 편지봉투를 상대방 메일슬롯으로 보내기 위한 통로를 형성하는 것.
...
//2단계. 데이터(데이터가 담긴 편지봉투를) 전송하는 작업
CHAR message[50];
WriteFile(hMailslot, message, ...);
//해당 메일슬롯과의 연결 통로를 의미하는 핸들을 이용해 메시지를 전달하고 있다.
...
//CreateFile(파일 생성 함수), WriteFile(파일에 데이터 쓰는 기능의 함수)함수를 호출한다.
//ANSI표준 함수가 아닌 Windows에서 제공하는 파일 관련 시스템 함수이다.
//CreateFile는 파일을 생성하거나 개방할 때 사용하는 함수이고, WriteFile함수는 파일에 데이터를 저장할 때 사용.
메일슬롯은 파일은 아니지만 Windows파일 시스템을 기반으로 구현되어 있다.
그래서 메일슬롯을 기반으로 하는 CreateMailslot이나 WriteMailslot의 함수를 만들면 기능은 같고 이름만 다른
함수 여러개를 만들어 버리는 것이 되서 이렇게 안만듬.
실제로 채워 넣어야 할 부분은 "computername"과 "[path]name"부분이다.
메일슬롯은 동일한 네트워크 도메인에 존재하는 호스트들 사이의 데이터 전달을 목적으로 사용될 수 있다.
computername부분이 '.'을 넣으면 로컬컴퓨터를 의미한다.
[path]name은 실질적인 메일슬롯 이름이다.
[path]name은 path정보를 포함해 계층 구조의 형태로 체계화할 수도 있다.
"\\.\mailslot\abc\def\mailslot"
메일슬롯에 데이터를 전송하려면 해당 메일슬롯의 연결을 의미하는 데이터 스트림이 필요한데 CreateMailslot을 통해
생성되는 메일슬롯과는 또 다른 형태의 리소스로서 운영체제에 의해 커널 오브젝트와 핸들의 생성을 동반한다.

메일슬롯의 예
7_2.cpp MailReceiver.cpp
BOOL ReadFile(
	HANDLE hFile, 1)
	LPVOID lpBuffer, 2)
	DWORD nNumberOfBytesToRead, 3)
	LPDWORD lpNumberOfBytesRead, 4)
	LPOVERLAPPED lpOverlapped 5)
);
If the function fails, the return value is zero.
1)hFile:메일슬롯의 핸들을 인자로 전달한다. 그러면 ReadFile함수는 해당 메일슬롯에 존재하는 데이터를 읽어들임.
2)lpBuffer:읽어들인 데이터를 저장할 버퍼를 지정하는 용도로 사용된다.
3)nNumberOfBytesToRead:읽어들일 데이터의 최대 크기를 지정한다.
4)lpNumberOfBytesRead:함수호출이 완료된 후에, 읽어들인 데이터 크기를 바이트 단위로 얻기 위한 변수를 지정.
5)lpOverlapped:일단은 NULL을 전달.
계속해서 메일슬롯에 들어오는 데이터를 읽어 콘솔에 출력할 것이다.
7_3.cpp MailSender.cpp
CreateFile함수의 첫 번째 전달인자는 생성 및 개방하고자 하는 파일 이름을 지정하는 용도로 사용된다.
데이터를 전달할 메일슬롯을 지정하는 용도로 사용되었다.
CreateFile함수의 두 번째 전달인자는 파일의 개방모드(Open Mode)를 지정하기 위한 것.
즉 읽기모드냐 쓰기모드냐 아니면 읽기/쓰기 모드냐를 지정하는 것.
쓰기 모드에 해당이 되는 GENERIC_WRITE를 인자로 전달해야 한다.
CreateFile함수의 다섯 번째 전달인자는 파일의 생성방식을 결정짓는 용도로 사용된다.
새로운 파일을 생성할 것인지 아니면 기존에 존재하는 파일을 열어서 접근할 것인지를 결정.
Receiver가 이미 만들어 놓은 메일슬롯에 접근하는 것이 목적이기 때문에 OPEN_EXISTING을 전달.
기존에 만들어진 파일을 개방할 때 사용하는 전달인자다.
WriteFile함수의 각각의 전달인자가 지니는 의미는 ReadFile함수에 상대적이다.
BOOL WriteFile(
	HANDLE hFile, 1)
	LPCVOID lpBuffer, 2)
	DWORD nNumberOfBytesToWrite, 3)
	LPDWORD lpNumberOfBytesWritten, 4)
	LPOVERLAPPED lpOverlapped 5)
);
If the function fails, the return value is zero.
1)hFile:데이터를 읽어 들일 파일을 지정한다. 여기선 데이터를 읽어들일 메일슬롯을 지정한다.
2)lpBuffer:전송할 데이터가 저장되어 있는 버퍼를 지정한다.
3)nNumberOfBytesToWrite:전송할 데이터 크기를 지정한다.
4)lpNumberOfBytesWritten:함수 호출 완료 후 전송된 실제 데이터의 크기를 바이트 단위로 얻기 위한 변수의 주소를 지정.
5)lpOverlapped:일단 NULL을 전달하자.
사용자로부터 입력받은 데이터를 메일슬롯으로 전달하는 과정을 구성하고 있다.
주의할 것은 Receiver를 먼저 띄우고 Sender를 띄어야 한다.
Sender에서는 CreateFile함수를 호출하면서 다섯 번째 전달인자로 OPEN_EXISTING을 전달하고 있다.

메일슬롯의 고찰과 앞으로의 전개에 대해서
메일슬롯은 단방향 통신만 가능하다.

메일슬롯과 IPC에 대한 고찰
메일슬롯은 한쪽 방향으로만 메시지를 전달할 수 있다.
따라서 두 프로세스가 서로 메시지를 주고받을 수 있는 채팅 프로그램 구현을 위해서는 두 개의 메일슬롯을 생성해야.
양쪽 방향으로 메시지를 주고 받고자 할 때 사용가능한 IPC기법도 있다.
파이프를 이용한 IPC는 Anonymous파이프와 Named파이프가 있다.
Named파이프는 기본적으로 양방향 데이터 송수신을 지원한다.
즉 채팅프로그램을 작성하기에 아주 적절한 형태의 IPC기법이다.
메일슬롯은 Broadcasting방식의 통신을 지원한다.
하나의 Sender는 한번의 메시지 전송으로 여러 Receiver에게 동일한 메시지를 동시에 전송하는 것이 가능하다.
예를 들어 동일한 네트워크로 연결되어 있는 서로다른 컴퓨터에서 실행중인 Receiver프로세스 A,B,C가 존재한다고 가정.
Receiver들은 동일한 메일슬롯 주소를 기반으로 메일슬롯 오브젝트를 생성하였다.
"\\.\mailslot\mailbox"
그리고 동일한 네트워크상에 존재하는 Sender프로세스 D가 데이터를 전송하려면
"\\*\mailslot\mailbox"
*는 모든 컴퓨터를 지칭하는 것이다.
따라서 "\\.\mailslot\mailbox'을 주소로 생성된 모든 메일슬롯에 동일한 메시지가 전달된다.
receiver들은 네트워크로 연결되어 있어야 한다.

메일슬롯은 생성과 동시에 Usage Count가 1이다. 참조하는 프로세스는 메일슬롯을 생성한 프로세스 하나이기 때문.
자식 프로세스의 경우에는 생성과 동시에 참조하는 프로세스가 둘이되어 2가 되는 것.
따라서 프로세스와 쓰레드를 제외한 모든 모든 커널 오브젝트는 생성과 동시에 Usage Count가 1이되는 것.
Windows는 내부적으로 생성하는 대부분의 리소스들에 대해서 커널 오브젝트를 생성한다.

03 Signaled vs Non-Signaled
커널 오브젝트의 두가지 상태(State)
Windows 운영체제에 의해서 생성되는 커널 오브젝트는 두 가지 상태를 지닌다.
이는 리소스에 특정 상황이 발생되었음을 알리기 위한 용도로 사용된다.

상태에 대한 이해
상태라는 용어를 사용하는 이유는 변하기 때문이다.
그 상태는 특정 상황하에서 변경된다.
하나는 Signaled상태(신호를 받은 상태)이고, 다른 하나는 Non-Signaled상태(신호를 받지 않는 상태)이다.
그리고 특정 상황 하에서 커널 오브젝트의 상태는 Signaled->Non-Signaled나 Non-Signaled->Signaled로 변경된다.
커널 오브젝트를 구성하는 메버 변수 중 하나는 커널 오브젝트의 상태 정보를 담당한다.
만약 Non-Signaled상태라면 이 멤버는 FALSE값을 지니게 되고, Signaled라면 TRUE를 지니게 된다.

프로세스 커널 오브젝트의 상태에 대한 이해
특정 상황이라는 것은 리소스마다 다르다.
커널 오브젝트의 상태가 변하는 시점은 커널 오브젝트의 종류에 따라서 달라진다.
프로세서 커널 오브젝트는 프로세스가 생성될 때 만들어진다.
이렇게 처음 커널 오브젝트가 생성되면 커널 오브젝트의 상태는 Non-Signaled상태에 놓이게 된다.
그러다가 프로세스가 종료되면 Signaled상태로 변경된다.
이러한 약속 덕분에 Signaled상태의 프로세스 커널 오브젝트를 보고 프로세스가 종료되었음을 알 수 있다.
프로세스 실행중에는 Non-Signaled상태에 놓이고 종료되면 Windows운영체제에 의해서 자동으로 Signaled상태.
그런데 문제는 종료된 프로세스는 다시 실행을 재개하지 못한다.
종료된 프로세스는 새로 다시 실행해야 한다.
즉 프로세스 커널 오브젝트의 상태는 일단 Signaled가 되면 절대로 다시 Non-Signaled로 변하지 않는다.

커널 오브젝트의 두 가지 상태를 확인하는 용도의 함수
커널 오브젝트가 상태를 지니도록 Windows운영체제가 디자인된 것은 프로그래머에게 다양한 기능을 제공하기 위해.
핸들을 인자로 전달해서 커널 오브젝트의 상태를 확인하는데 사용되는 함수.
DWORD WaitForSingleObject(
	HANDLE hHandle, 1)
	DWORD dwMilliseconds 2)
);
If the function fails, the return value is WAIT_FAILED
1)hHandle:상태 확인을 원하는 커널 오브젝트의 핸들을 인자로 받는다.
2)dwMilliseconds:WaitForSingleObject함수는 인자로 전달된 hHandle이 가리키는 커널 오브젝트가 Signaled상태가
되었을 때 반환한다. 즉 커널 오브젝트가 Signaled상태가 될 때까지 기다리는 함수이다.
dwMilliseconds는 Signaled상태가 될 때까지 기다릴 수 있는 최대 시간을 ms단위로 지정하는 용도로 사용된다.
일반적으로는 Time Out을 설정하는 인자라고 표현을 많이 한다.
만약에 상수 INFINITE를 인자로 전달하면, 커널 오브젝트가 Signaled상태가 될 때까지 반환하지 않고 무한정 기다림.
WaitForSingleObject함수가 반환하는 상황은 다양하다.
따라서 함수 호출이 완료된 후에 반환값을 확인해야만 한다.
WAIT_OBJECT_0:커널 오브젝트가 Signaled상태가 되었을 때 반환되는 값
WAIT_TIMEOUT:커널 오브젝트가 Signaled상태가 되지 않고, dwMilliseconds인자를 통한 설정된 시간이 다 된 경우.
WAIT_ABANDONED:소유 관계와 관련하여 함수가 정상적이지 못한 오류 발생에 의해 반환하는 경우.

만약에 상태를 확인하고자 하는 커널 오브젝트가 둘 이상이고, 핸들이 배열로 묶여있다면 
DWORD WaitForMultipleObjects(
	DWORD nCount, 1)
	const HANDLE* lpHandles, 2)
	BOOL bWaitAll, 3)
	DWORD dwMilliseconds 4)
);
If the function fails, the return value is WAIT_FAILED.
1)nCount:배열에 저장되어 있는 핸들 개수를 전달한다.
2)lpHandles:핸들을 저장하고 있는 배열의 주소 정보를 전달한다. 이 주소값을 시작으로 총 nCount개의 핸들이
관찰 대상이 된다.
3)bWaitAll:관찰 대상이 모두 Signaled상태가 되기를 기다리고자 하는지(TRUE), 아니면 하나라도 Signaled상태가
되면 반환할 것인지(FALSE)를 결정짓는다.
4)dwMilliseconds:WaitForSingleObject와 같은 의미로 타임아웃을 설정하는 용도로 사용된다.

커널 오브젝트의 상태 확인이 필요한 상황의 연출
구현해야할 프로그램의 시나리오
두 개의 자식 프로세스를 생성해서 각각 1부터 5까지, 그리고 6부터 10까지 덧셈을 시킨 다음 결과를 반환하게 하자.
그리고 부모 프로세스는 반환된 값을 더해서 그 결과를 출력하는 형태로 작성해보자.
우선 부모 프로세스는 1부터 5까지의 합을 계산할 자식 프로세스를 생성한다.
이어서 6부터 10까지의 합을 계산할 자식 프로세스도 생성한다.
첫 번째 생성된 자식 프로세스는 계산 결과를 부모 프로세스에게 넘기고 종료한다.
두 번째 생성된 자식 프로세스도 계산 결과를 부모 프로세스에게 넘기고 종료한다.
마지막으로 부모 프로세스는 두 자식 프로세스가 반환해준 값을 더해 그 결과를 출력한다.

구현에 있어서 고민해 봐야 할 내용들
두 프로세스가 하는 일은 같지만 계산 범위만 다를 뿐.
자식 프로세스의 역할을 하는 프로그램 하나를 작성하고, 이 프로그램이 프로세스가 되는 순간 덧셈의 범위를
전달하는 형식이 가장 쉽고 간결한 방법이다.
7_4.cpp PartAdder.cpp

커널 오브젝트에 존재하는 종료코드(Exit Code)
반환값을 부모 프로세스에게 전달돼야 의미를 지닌다.
프로세스가 종료되면서 전달하는 값을 가리켜 종료코드라 하고, 이 종료코드는 종료되는 프로세스의 커널
오브젝트에 저장된다.
이 종료코드를 활용해 부모 프로세스에게 데이터를 전달할 수 있다.
그리고 부모 프로세스는 GetExitCodeProcess함수 호출을 통해 자식 프로세스의 종료코드를 얻는다.
부모 프로세스 영역          A프로세스 커널 오브젝트            A프로세스
       0 <──────────────────────── 0                        int main()
			GetExitCodeProcess     ↑						{... 
								   └──── Exit Code 0 ───────	return 0; 
															}
자식프로세스가 부모 프로세스에게 데이터를 전달해야만 한다.
즉 프로세스간 통신이 필요한 상황.

구현의 예와 문제점
7_5.cpp NonStopAdderManager.cpp
위 예제의 출력결과는 518이다. GetExitCodeProcess함수는 프로세스가 종료되지 않은 상태에서 호출되면,
상수 STILL_ACTIVE를 얻게 된다. 이 값은 259이다.
의미를 지니는 종료코드를 얻기 위해서는 두 자식 프로세스가 종료코드를 반환하면서 이미 종료된 상태여야 한다.

WaitForSingleObject함수의 유용성
자식 프로세스의 생성과 소멸시간을 향상시키는 것은 불가능하므로(가능해도 의미가 없다) 자식 프로세스가 종료될 때까지
기다렸다가 GetExitCodeProcess함수를 호출하는 방법을 고민해봐야 한다.
부모 프로세스는 CreateProcess함수 호출 과정에서 자식 프로세스의 핸들을 얻게 된다.
이 핸들을 인자로 전달하면서 WaitForSingleObject함수를 호출하면 부모 프로세스는 자식 프로세스가 종료될 때까지
기다리는 효과를 얻게 된다.
프로세스의 커널 오브젝트는 생성과 동시에 Non-Signaled상태가 된다.
따라서 부모 프로세스가 WaitForSingleObject함수를 호출하면 이 함수는 블로킹상태에 놓인다.
즉 부모 프로세스는 더 이상 실행되지 않고 함수의 블로킹 상태에서 빠져 나오기만을 기다리는 것.
자식 프로세스가 종료되면, 자식 프로세스의 커널 오브젝트는 Signaled상태가 된다.
따라서 WaitForSingleObject함수를 호출한 부모 프로세스는 블로킹 상태를 빠져나와서 나머지 부분을 실행한다.
7_6.cpp AdderManager.cpp
두 개의 자식 프로세스를 생성한 다음 GetExitCodeProcess함수를 호출하기에 앞서 WaitForSingleObject함수를 호출.
두 번째 전달인자는 INFINITE로 자식 프로세스가 종료될 때까지 함수의 호출은 블로킹 상태에 놓인다.
결국 부모 프로세스는 자식 프로세스가 종료될 때까지 기다려주는 효과를 얻는다.

이것만은 알고 갑시다
1. 프로세스간 통신 기법이 별도로 존재하는 이유
프로세스는 개별적으로 독립적인 메모리 공간을 유지한다. 따라서 둘 이상의 프로세스가 데이터를 주고받기 위해서는
Windows운영체제에서 제공하는 기능상의 도움을 받아야만 한다.
2. 메일슬롯의 특성
단 방향 통신과 브로드캐스팅 방식을 지원하는 통신기법이다.
3. 커널 오브젝트의 두 가지 상태가 지니는 의미
커널 오브젝트는 Signaled상태와 Non-Signaled상태 둘 중 하나의 상태에 놓이게 된다.
그리고 이 상태는 나머지 다른 하나의 상태로 변경되는데, 상태가 변경되는 시점은 커널 오브젝트의 종류에 따라 다르다.
4. WaitForSingleObject, WaitForMultipleObjects함수와 커널 오브젝트의 관계
WaitForSingleObject함수는 커널 오브젝트를 감시하는 역할을 한다. 커널 오브젝트가 Non-Signaled상태에 있을 때에는
함수를 반환하지 않고 블로킹 상태에 있다가 함수가 Signaled상태가 되면 함수를 빠져나오는 특성.
WaitForMultipleObjects함수는 둘 이상의 커널 오브젝트를 감시할 때 사용하는 함수다.
5. 종료코드(Exit Code)
main함수의 return문에 의한 반환값은 프로세스의 종료코드로 커널 오브젝트에 저장된다.
이 종료코드를 얻기 위해서는 GetExitCodeProcess함수를 호출하면 되고, 이 종료코드는 프로세스의 종료 이유를 담는
용도로 사용하는 것이 일반적이다.

*/