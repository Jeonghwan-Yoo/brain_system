/*
01 핸들 테이블과 오브젝트 핸들의 상속
오브젝트 핸들(커널 오브젝트 핸들)의 상속과 핸들 테이블에 대한 개념은 Windows를 이해하는 데 도움이 된다.

도입배경(Introduction to Jeffery Richter)
Windows가 핸들 테이블을 관리하는 실질적은 방법 설명은 다양할 수 있다.
1)MS에서 Windows운영체제를 공개하고 있지 않다.
공개하지 않는 한 프로세스 핸들 테이블이 어떻게 관리되는지를 세밀하게 알 수 없다.
2)Windows운영체제의 종류 및 버전마다 핸들 테이블이 관리되는 방법에 다소 차이가 있다.
Programming Application for Microsoft Windows에선 가장 일반적인 형태로 프로세스 핸들 테이블 관리를 설명.

프로세스의 커널 오브젝트 핸들 테이블
시스템 리소스의 생성과정에서 커널 오브젝트가 생성되면, 생성된 커널 오브젝트를 가리킬 때 사용되는
핸들이 반환된다.

핸들과 커널 오브젝트의 리뷰
CreateMailslot의 호출을 통해 메일슬롯을 생성한다.
그런데 이 리소스는 운영체제에 의해서 관리되므로 메일슬롯 정보를 담고 있는 커널 오브젝트가 생성되고,
최종적으로는 커널 오브젝트의 핸들이 반환된다.
이 핸들은 메일슬롯의 커널 오브젝트를 가리키는 용도로 사용된다.
프로세스 ───── 메일슬롯 리소스 생성 ─────> 메일슬롯
   ↑256(핸들)                                │
   └───────── 메일슬롯 커널 오브젝트 <────────┘
               (0x2400번지 할당)
0x2400번지에 메일슬롯 정보를 저장하는 커널 오브젝트가 생성되고 256은 커널 오브젝트를 가라키는 용도로 핸들.
그러나 어떠한 방식으로 알아서 해주는지를 이해하는 것이 중요하다.
0x2400번지에 커널 오브젝트가 생성되면서 핸들 256이 반환되었다.
그러나 핸들 256이 0x2400번지에 존재하는 커널 오브젝트를 의미한다는 정보는 없다.
CloseHandle함수를 호출하면서 256을 전달할 경우, 0x2400번지에 존재하는 커널 오브젝트의 Usage Count값이
하나 감소하는 부분에 대해서도 의문이 생긴다.
핸들 256이 0x2400번지에 존재하는 커널 오브젝트임을 알 방법이 없었다.
핸들 테이블이 추가로 들어가야만 완성되고 이해가 가능.

프로세스의 핸들 테이블 도입
프로세스 ───── 메일슬롯 리소스 생성 ─────> 메일슬롯
(핸들 테이블)                                │
핸들 주소                                    │
...  ...                                    │
256  0x2400(추가됨)                          │
...  ...                                    │
   ↑                                        │
   └───────── 메일슬롯 커널 오브젝트 <────────┘
	256|0x2400  (0x2400번지 할당)
유일한 차이점은 핸들 테이블이 추가로 등장했다.
핸들 테이블은 핸들 정보를 저장하고 있는 테이블로서 프로세스별로 독립적이다.
각각의 프로세스가 자신만의 핸들 테이블을 하나씩 구성하고 관리한다.
CreateProcess함수나 CreateMailslot과 같은 함수 호출을 통해 리소스 생성을 요구한 결과로 핸들 정보를 얻게 되면
프로세스 자신에게 속해 있는 핸들 테이블에 해당 정보가 등록된다.
핸들 테이블에 등록된 정보를 통해 핸들 256이 지시하는 커널 오브젝트가 0x2400번지에 존재하고 있음을 확인할 수 있다.

'핸들테이블', '오브젝트 핸들 테이블', '커널 오브젝트 핸들 테이블', '프로세스 핸들 테이블', '프로세스 커널
오브젝트 핸들 테이블'모두 같은 의미이다.

핸들의 상속
CreateProcess함수를 호출하면 새로운 자식 프로세스가 생성된다.
자식 프로세스를 위한 핸들 테이블도 더불어 생성된다.
CreateProcess함수 호출 시 전달되는 인자(5번째 인자)가 무엇이냐에 따라서 부모 프로세스 핸들 테이블에
등록되어 있는 핸들 정보는 새롭게 생성되는 자식 프로세스에게 상속될 수 있다.

핸들의 상속에 대한 이해
자식 프로세스는 부모 프로세스의 핸들 테이블에 등록되어 있는 핸들 정보를 상속받을 수 있다.
하지만 모든 핸들 정보를 상속받는 것은 아니다.
자식 프로세를 생성하는 과정에 있어서 구성되는 자식 프로세스의 핸들 테이블 형태는
부모 프로세스 핸들 테이블      자식 프로세스 핸들 테이블
핸들 주소    상속여부          핸들 주소    상속여부
127  0x1200  Y ─────────────> 127  0x1200  Y
168  0x1680  N  ┌───────────> 256  0x2400  Y
256  0x2400  Y ─┘               ...  ...     ...
...  ...     ...                 
실제 핸들 테이블에는 해당 핸들의 상속 여부를 결정짓기 위한 Column이 존재한다.
상속 여부가 Y이면 핸들 정보는 자식 프로세스에게 상속되고 N이면 상속되지 않는다.
또한 상속 여부에 대한 정보도 변경없이 그대로 상속되었다.
따라서 자식 프로세스의 자식프로세스를 생성해도 이 핸들에 대한 정보는 계속 상속된다.

핸들의 상속을 위한 전달인자
모든 자식 프로세스가 무조건 부모 프로세스의 핸들을 상속하는 것은 아니다.
BOOL CreateProcess(
	LPCTSTR lpApplicationName,
	LPTSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInHeritHandles, //handle inheritance option
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCTSTR lpCurrentDirectory,
	LPSTRATUPINFO lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
);
bInheritanceHandle은 자식 프로세스에게 핸들테이블에 등록되어있는 핸들 정보를 상속할지 말지를 결정하는 요소.
TRUE를 인자로 전달하면 부모 프로세스의 핸들 테이블 정보는 자식 프로세스로 상속된다.
부모 프로세스가 소유하고 있는 핸들 테이블 정보의 상속여부를 결정하는 것이다.
상속여부가 Y로 설정된 핸들에 한해서만 상속이 이뤄지고 FALSE가 인자로 전달되면 상속은 이뤄지지 않는다.

핸들 상속과 커널 오브젝트의 Usage Count
Usage Count는 참조하는 프로세스의 수만큼 증가합니다.
핸들을 얻은 프로세스가 커널 오브젝트를 참조하는 프로세스가 된다.
"프로세스가 핸들을 얻게 되었다는 의미는 핸들 테이블에 해당 핸들에 대한 정보가 추가되었음을 의미"
CreateMailslot함수의 호출을 통해 메일슬롯을 생성했다고 가정하면 순서대로 일이 진행된다.
1)메일슬롯 리소스 생성
2)커널 오브젝트 생성
3)핸들 정보가 핸들 테이블에 갱신
4)CreateMailslot함수를 빠져 나오면서 핸들값 반환
프로세스가 핸들을 얻었다고 말할 수 있는 부분은 3)이후이다.
즉 핸들 테이블에 A핸들에 대한 정보가 등록되면 A핸들을 얻은 것이다.
핸들 주소    상속여부
127  0x1200  Y       0x1200번지에 Kernel Object UC=1
168  0x1680  N       0x1680번지에 Kernel Object UC=1
256  0x2400  Y       0x2400번지에 Kernel Object UC=1
부모 프로세스의 핸들 테이블에만 핸들 정보가 등록되어 있는 관계로 UC의 값은 모두 1로 설정.
부모 프로세스가 CloseHandle함수를 호출하면서 어떤한 핸들값을 인자로 전달하더라도 UC의 값이 0이 되어
해당 커널 오브젝트와 리소스가 더불어 소멸될 것이다.
부모 프로세스가 자식 프로세스를 생성하면서 핸들 테이블을 상속했다고 가정하면
핸들 주소    상속여부          핸들 주소    상속여부
127  0x1200  Y ─────────────> 127  0x1200  Y      0x1200번지에 Kernel Object UC=2
168  0x1680  N  ┌───────────> 256  0x2400  Y      0x1680번지에 Kernel Object UC=1
256  0x2400  Y ─┘               ...  ...     ...  0x2400번지에 Kernel Object UC=2
...  ...     ...
자식 프로세스가 생성되면서 상속 여부가 Y인 핸들이 상속되었고, 일부 커널오브젝트의 UC가 2가 된다.

상속이 되기 위한 핸들의 조건
핸들의 상속 여부는 리소스가 생성되는 순간에 프로그래머에 의해 결정된다.
CreateProcess와 CreateMailslot함수를 기반으로 잘 이해하고 있으면 다른 형태의 리소스 생성에도 충분히 적용가능.
HANDLE CreateMailslot(
	LPCTSTR lpName,
	DWORD nMaxMessageSize,
	DWORD lReadTimeout,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes //inheritance
);
LPSECURITY_ATTRIBUTES는 구조체 SECURITY_ATTRIBUTES의 포인터로 정의되어 있다.
즉 SECURITY_ATTRIBUTES구조체 변수를 적절히 초기화한 다음, 주소값을 인자로 전달하라는 의미.
이 전달인자에 NULL이 전달되면 여기서 생성되는 메일슬롯의 핸들은 자식 프로세스에게 상속되지 않는다.
반대로 구조체 변수를 적절한 값으로 초기화해서 변수의 주소값을 전달하면 메일슬롯의 핸들은 상속될 수 있다.

핸들 정보를 상속한다는 것은 프로세스 입장에서 보면 보안에 관련된 사항이다. 따라서 상속에 대한 선언을 보안
관련 인자를 통해서 전달하는 것.

SECYRITY_ATTRIBUTES구조체 선언
typedef struct _SECURITY_ATTRIBUTES{
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES;
nLength에는 구조체 변수 크기를 바이트 단위로 설정해준다.
이 멤버는 함수 내부적으로 사용되는 멤버이므로 반드시 구조체 변수 크기로 초기화해야 한다.
lpSecurityDescriptor에는 NULL로 초기화한다.
bInheritHandle은 TRUE로 설정해준다. 상속여부를 결정짓는 요소다.
따라서
SECURITY_ATTRIBUTES sa;
sa.nLength = sizeof(sa);
sa.lpSecurityDescriptor = NULL;
sa.bInheritHandle = TRUE;
...
CreateMailslot(... &sa); //4번째
위에 예제는 대부분의 리소스 생성방식에 동일하게 적용된다.
CreateProcess함수를 통해 생성되는 자식 프로세스의 핸들을 상속하는 것은 호출함수의 종류와 인자위치만 차이있다.
SECURITY_ATTRIBUTES sa;
sa.nLength = sizeof(sa);
sa.lpSecurityDescriptor = NULL;
sa.bInheritHandle = TRUE;
...
CreateProcess(..., &sa ,...); //3번째
자식 프로세스의 핸들이 상속될 수 있도록 설정해 놓으면, 이후에 생성되는 자식 프로세스에게 상속될 것이다.

CreateProcess함수 호출시 핸들 상속과 관련해서 두가지 사항을 결정해야 하는데 하나는 자식 프로세스에게
핸들 테이블을 상속할 것인가와 자식 프로세스 생성시 얻게되는 핸들(자식 프로세스를 가리키는 핸들)의 상속여부를 
결정하는 것이다.

예제를 통해서 확인하는 핸들 정보의 상속
메일슬롯 예제의 고찰
MailReveiver 핸들 테이블      MailSender 핸들 테이블
핸들 주소    상속여부          핸들 주소    상속여부
127  0x1200  N                127  0x1700  N      
...  ...     ...              ...  ...     ...
0x1200번지                   0x1700번지
커널오브젝트 UC = 1           커널오브젝트 UC = 1
Reciver에는 핸들 127은 0x1200번지에 있는 커널 오브젝트를 가리키고 있는데, 이 커널 오브젝트는 CreateMailslot함수 
호출에 의해 생성된 것이다.
CreateMailslot함수의 네번째 전달인자가 NULL이어서 핸들의 상속 여부는 N으로 설정되었다.
Sender에는 핸들 127은 0x1700번지에 있는 커널 오브젝트를 가리키고 있는데, 이 커널 오브젝트는 CreateFile함수
호출에 의해 생성된 것이다.
함수가 호출될 때 상속을 위한 인자는 전달되지 않았기 때문에 핸들 상속 여부는 N이다.
양쪽 핸들 테이블의 핸들값이 모두 127인 것은 우연의 일치라고 생각해야 한다.
Sender와 Receiver는 서로 다른 프로세스로서 핸들 테이블이 서로 독립적이다.
메일슬롯은 Receiver의 리소스이고 편지를 보내기 위해 다리 역할을 하는 Sender의 리소스(데이터 스트림)도 존재한다.
이 리소스의 커널 오브젝트가 0x1700번지에 저장되어 있다.

메일슬롯 예제의 확장 그리고 확인!
MailReveiver 핸들 테이블        MailSender 핸들 테이블
핸들 주소    상속여부           핸들 주소    상속여부
127  0x1700  Y ──────────────> 127  0x1700  Y
...  ...     ... CreateProcess ...  ...     ...
0x1700번지                   
커널오브젝트 UC = 2          
핸들 127이 가리키는 커널 오브젝트를 통해 메일슬롯으로 메시지를 전송할 수 있다.
상속 여부가 Y인 것이 차이점. 즉 MailReceiver를 약간 수정해야 한다.
SECURITY_ATTRIBUTES구조체 변수를 적절히 초기화해서 인자로 전달해야 한다.
MailSender가 CreateProcess함수 호출을 통해 자식 프로세스를 생성했다는 가정이 있고 핸들정보가 상속되었다.
따라서 자식 프로세스는 상속된 핸들 정보를 참조해서 메일슬롯으로 데이터를 전송할 수 있게 된다.
우선 핸들이 상속가능하도록 변경해야하고, 또 자식프로세스를 생성하도록 변경해야 한다.
8_1.cpp MailSender2_1.cpp
자식 프로세스에게 메일 슬롯 관련 핸들을 상속하고 있다. 
따라서 자식 프로세스의 핸들테이블에는 이와 관련된 정보가 등록이 된다.
그러나 등록된 핸들 정보를 자식 프로세스는 확인할 길이 없다.
핸들 테이블은 운영체제에 의해서 관리된다.
따라서 우리가 프로그램상에서 핸들 테이블 정보를 조회해보거나 할 수는 없다.
결국 부모 프로세스는 자식 프로세스에게 "너에게 핸들정보127을 상속했으니 메일슬롯에 데이터를 보내는데 사용해라"
리소스를 생성할 때 반환되는 핸들값을 고정적이지 않다. 실행할 때마다 달라질 수 있는 것.
그러므로 프로그램이 실행되는 과정에서 얻어진 핸들 정보를 자식 프로세스에게 전달해 줘야만 상속된 핸들이 의미를 가짐.
결국 자식 프로세스에게 핸들 정보를 전달해줘야하는데 이를 위해 다양한 방법이 사용될 수 있지만, 파일을 이용했다.
자식 프로세스는 이 파일을 열어서 핸들 정보를 얻게 될 것이다.
자식프로세스는 파일을 열어 상속된 핸들값을 확인하고, 이를 통해 메일슬롯에 데이터를 전송한다.
8_2.cpp MailSender2_2.cpp
Receiver를 띄운 다음 메일 Sender를 띄어서 메시지를 전달하면 된다.

파일을 통해서 데이터를 주고 받는 방식은 흔히 쓰이지만 위험성을 지니고 있다. 자식 프로세스가 접근하기 전에
파일이 삭제되거나, 악정코드에 의해 파일에 저장된 데이터가 변경되는 문제가 있을수도 있다.
이보다는 프로세스 생성시 매개변수로 전달하는 것이 훨씬 안전한 방식이다.

Pseudo 핸들과 핸들의 중복(Duplicate)
현재 실행중에 있는 프로세스 자신의 핸들을 얻는 방법으로 GetCurrentProcess함수를 소개했다.
실제로 이 함수 호출을 통해 얻은 핸들을 이용해 프로세스 자신의 커널 오브젝트에 접근이 가능하다.
그런데 이 함수 호출을 통해 얻은 핸들을 가리켜 가짜핸들(Pseudo 핸들)이라 한다.
이렇게 얻어진 핸들은 핸들 테이블에 등록되어 있지 않은 핸들이고, 다만 현재 실행 중인 프로세스를 참조하기
위한 용도로 정의해 놓은, 약속된 상수가 반환되는 것이기 때문. (현재는 -1을 반환하고 있다)
따라서 자식 프로세스로 상속되지 않으며, CloseHandle함수의 인자로 전달할 필요도 없다.
혹 CloseHandle함수의 인자로 전달되더라도 아무 일도 발생하지 않는다.

핸들을 복사하는 기능
BOOL DuplicateHandle(
	HANDLE hSourceProcessHandle, 1)
	HANDLE hSourceHandle, 2)
	HANDLE hTargetProcessHandle, 3)
	LPHANDLE lpTargetHandle, 4)
	DWORD dwDesiredAccess, 5)
	BOOL bInheritHandle, 6)
	DWORD dwOptions 7)
);
If the function fails, the return value is zero.
만약 현재 실행 중인 프로세스의 Real핸들을 얻고자 한다면 DuplicateHandle을 사용하면 된다.
1)hSourceProcessHandle:복제할 핸들을 소유하는 프로세스를 지정한다.
2)hSourceHandle:복제할 핸들을 지정한다.
3)hTargetProcessHandle:복제된 핸들을 소유할 프로세스를 지정한다.
4)lpTargetHandle:복제된 핸들값을 저장할 변수의 주소를 지정한다.
5)dwDesiredAccess:복제된 핸들의 접근 권한을 지정한다. DUPLICATE_SAME_ACCESS가 인자로 전달되면, 이 전달인자는
무시된다. 따라서 0을 전달한다.
6)bInheritHandle:복제된 핸들의 상속 여부를 지정한다. TRUE전달 시 새로운 자식 프로세스로 상속된다.
FALSE전달 시 상속되지 않는다.
7)dwOptions:DUPLICATE_SAME_ACCESS를 전달하면 원본 핸들과 동일한 접근권한을 가지게 된다.
DUPLICATE_CLOSE_SOURCE가 올 수 있는데, 이 인자가 전달되면 원본 핸들을 종료시킨다.(CloseHandle함수의 인자로
전달한 것과 같은 효과). 이 둘은 비트 단위 OR연산자를 통해 동시 전달이 가능하다.

DuplicateHandle(A핸들, 256, B핸들, &val, ...); //HANDLE val = 364
프로세스 A                     프로세스 B
핸들 주소                      핸들 주소
...  ...     함수 호출에 의해  ...  ...
256  0x2400 ────────────────> 364  0x2400
...  ...                      ...  ...
0x2400번지 할당
커널 오브젝트

프로세스 A는 부모 프로세스이고, 프로세스 B는 자식프로세스이다.
프로세스 A는 자신의 핸들 테이블에 존재하는 핸들 256을 프로세스 B에게 복사하고 싶은데 256이라는 숫자를 넘기는
것은 아무런 의미가 없다.
프로세스 B의 핸들 테이블에 복사하고자 하는 핸들 정보가 등록되어야만 의미가 있다.
그래서 함수 호출을 한다.
DuplicateHandle(
	프로세스 A핸들, //프로세스 A에 존재하는
	256, //핸들 256의 정보를
	프로세스 B핸들, //프로세스 B의 핸들 테이블에 등록한다.
	&val, //등록된 핸들의 값은 변수 val에 저장한다.
	...
);
DuplicateHandle함수 호출을 통해 핸들 복사는 비교적 쉽게 이뤄진다.
중요한 사실은 핸들 테이블에 등록되어야 진정한 복사라는 것.
복사된다고 해서 핸들 값까지 똑같은 것이 아니라는 점을 주목.
서로 독립된 프로세스 영역의 핸들이기 때문에 값은 별 의미가 없다.

DuplicateHandle(
	프로세스 A핸들,
	256,
	프로세스 A핸들,
	&val,
	...
);
같이 호출하면 복사할 핸들을 소유하는 것도 A프로세스이고, 복사된 핸들 정보를 갱신할 대상도 A프로세스이다.
프로세스가 자신이 소유하고 있는 핸들을 자신의 핸들 테이블에 복사하는 것.
핸들 주소
...  ...
256  0x2400
...  ...
284  0x2400 : Duplicate Handle
...  ...
커널 오브젝트 Usage Count:2
또한 DuplicateHandle함수에 의해서 핸들이 복사되고 나면, 당연히 Usage Count는 증가한다.
따라서 복사된 핸들에 대해서도 CloseHandle함수호출을 통해서 핸들을 반환해야만 한다.

그리고 GetCurrentProcess함수 호출을 통해 얻은 핸들을 복사한다면(가짜핸들), 진짜핸들이 생성되어 핸들테이블에 등록.
프로세스가 자신의 핸들 테이블에 핸들 정보 하나를 더 추가했을 뿐이다.
핸들 주소
...  ...
...  ...
...  ...
284  0x2400 : Duplicate Handle
...  ...
커널 오브젝트 Usage Count:1

부모 프로세스의 핸들을 자식 프로세스에게 전달하기
일반적으로 부모 프로세스가 자식 프로세스의 핸들을 소유하는 것이 보통이지만, 경우에 따라서는 자식 프로세스도
부모 프로세스의 핸들을 얻어야만 하는 경우가 있다.
8_3.cpp DuplicateHandle.cpp
8_4.cpp DuplicateHandleChildProcess.cpp
자식 프로세스가 부모 프로세스의 정보를 참조하거나 상태를 알아야 할 경우 부모 프로세스는 핸들 복사를 통해서
자신의 핸들 테이블에 등록해야만 한다.
그 이외에도 다양한 경우에 유용하게 사용될 수 있다.

02 파이프 방식의 IPC
프로세스간 통신기법 중 가장 대표적인 파이프.

메일슬롯에 대한 회고와 파이프의 이해
Windows의 파이프 메커니즘에는 두 가지 종류가 있는데 하나는 "이름없는 파이프(Anonymous Pipe)" 다른 하나는
"이름있는 파이프(Named Pipe)"이다.
메일슬롯은 서로 관련이 없는 프로세스들(네트워크 프로세스들) 사이에서 통신할 때 유용한 IPC기법이다.
메일슬롯의 Sender와 Receiver는 주소정보를 공유한 것 이외에 아무런 관계가 없다.
반면에 이름없는 파이프는 지극히 관계가 있는(부모 자식관계)프로세스들 사이에서 통신하는 경우에 유용하다.
일반적으로 메일슬롯이 더 많은 기능을 제공하지만 상황에 따라서는 이름없는 파이프가 더 유용한 경우도 있다.
이름이 있다는 것은 주소 정보가 있다는 뜻이다.
그런 점에서 메일 슬롯과 비슷한 특징을 지닌다.
서로 관계없가 없는 프로세스들 사이에서도 주소 정보를 공유함으로써 데이터를 주고 받을 수 있다는 뜻.
실제로 이름있는 파이프는 메일슬롯과 마찬가지로 서로 관계가 없는 프로세스들 사이에서도 데이터를 주고받을 수 있다.
차이점으로는 메일슬롯과 달리 양방향 통신이 가능하다는 점이다.
따라서 채팅프로그램을 만들고자 한다면 메일슬롯보다는 이름있는 파이프가 훨씬 구현하기 용이하다.
반면에 메일슬롯은 브로드캐스트(Broadcast)방식의 데이터 전송이 가능하다.
따라서 여러 사람에게 동시에 메시지를 전달하는 시스템 구현 시에는 메일슬롯이 훨씬 유용하다.
정리해보면
메일슬롯:브로드캐스트 방식의 단방향 통신방식을 취하며, 메일슬롯에 할당된 주소를 기반으로 통신하기 때문에
관계없는 프로세스들 사이에서도 통신이 가능하다.
이름없는 파이프:단방향 통신방식을 취하며, 파이프를 통해서 생성된 핸들을 기반으로 통신하기 때문에
프로세스들 사이에는 관계가 있어야만 한다.
이름있는 파이프:메일슬롯과 유사하고 브로드캐스트방식을 지원하지 않는 대신 양방향 통신을 지원한다.

이름없는 파이프(Anonmous Pipe)
이 파이프를 이용해서 데이터를 한쪽 방향으로 전송할 수 있다.
BOOL CreatePipe(
	PHANDLE hReadPipe, 1)
	PHANDLE hWritePipe, 2)
	LPSECURITY_ATTRIBUTES lpPipeAttributes, 3)
	DWORD nSize 4)
);
If the function fails, the return value is zero.
1)hReadPipe:한쪽 끝에서는 데이터가 들어가고 다른 한쪽에서는 들어간 데이터가 흘러나오는 것이 파이프의 원리.
파이프는 두 개의 끝을 가지는데 파이프 생성 시 각각의 끝에 접근하기 위한 두 개의 핸들을 얻게 되는데,
이 인자를 통해서는 데이터를 읽기 위한 파이프 끝에 해당하는 핸들을 얻게 된다.
2)hWritePipe:다른 한쪽 끝에 해당하는 핸들을 얻게 된다.
3)lpPipeAttributes:보안 관련 정보를 전달할 때 사용된다. 핸들의 상속 특성을 지정할 때 사용.
4)nSize:파이프의 버퍼 사이즈를 지정하는 용도로 사용. 전달되는 값으로 버퍼의 크기가 결정되는 것은 아니다.
내부적인 버퍼링 매커니즘에 의해서 버퍼 사이즈가 결정된다. 이 값은 단지 참조로 활용될 뿐이다.
그리고 0을 인자로 전달하면 디폴트 사이즈로 버퍼 크기가 결정된다.
8_5.cpp anonymous_pipe.cpp
"anonymous pipe" ─────> |hWritePipe        hReadPipe| ─────> "anonymous pipe"
파이프 생성 시 얻게 되는 입력용, 그리고 출력용 핸들을 하나의 프로세스 내에서 사용했다.
그러나 자식 프로세스를 생성하면서, 입력용 혹은 출력용 핸들을 상속한다면, 부모 자식 프로세스간에 메시지 전송 가능.

이름있는 파이프(Named Pipe)
핵심은 양방향 통신이다.
───────────server─────────────────────┐
           PIPE ───────────────────> PIPE ───────────────────── client
CreateNamedPipe   ConnectNamedPipe    │   Client의 CreateFile
함수에 의해 생성   함수에 의해 연결      │  함수 호출에 의한 파이프 오픈(연결)
                  대기상태로 전환      │
──────────────────────────────────────┘
연결 요청을 수락하는 서버에선 CreateNamedPipe함수를 통해 파이프를 생성한다.
그런데 이때 생성되는 파이프는 아직 제 역할을 하지 못하는 파이프이다.
파이프가 제 역할을 하기 위해서는 ConnectNamedPipe함수가 호출되어야 하는데,
이 함수호출에 의해서 파이프는 연결 요청을 기다리는 파이프로 상태 변경된다.
서버의 할일은 끝나고 클라이언트는 서버가 만들어 놓은 파이프에 연결하기 위해서 연결요청을 위한 리소스를 생성하고
연결을 시도해야 하는데, CreateFile함수가 이 모든 것을 처리한다.
CreateFile함수는 파일 생성함수이다. 그러나 이 함수는 파이프로 연결 요청을 하는 경우에도 사용된다.

서버에서 파이프 오브젝트를 생성할 때 사용되는 함수
HANDLE CreateNamedPipe(
	LPCTSTR lpName, 1)
	DWORD dwOpenMode, 2)
	DWORD dwPipeMode, 3)
	DWORD nMaxInstances, 4)
	DWORD nOutBufferSize, 5)
	DWORD nInBufferSize, 6)
	DWORD nDefaultTimeOut, 7)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes 8)
);
If the function fails, the return value is INVALID_HANDLE_VALUE.
1)lpName:파이프 이름을 지정한다. \\.\pipe\pipename
2)deOpenMode:셋 중 하나를 지정한다.
PIPE_ACCESS_DUPLEX:읽기, 쓰기가 모두 가능하도록 설정.
PIPE_ACCESS_INBOUND:읽기만 가능하다(CreateNamedPipe함수를 호출하는 서버 입장에서)
PIPE_ACCESS_OUTBOUND:쓰기만 가능하다(서버 입장에서)
3)dwPipeMode:이 전달인자를 통해 데이터 전송타입, 데이터 수신타입, 블로킹 모드 이렇게 3가지를 설정한다.
4)nMaxInstance:생성할 수 있는 파이프의 최대 개수를 지정한다. 지정하는 개수만큼 파이프 클라이언트의
연결 요청을 수용할 수 있다. 인자로 올 수 있는 값의 범위는 1에서부터 PIPE_UNLIMITED_INSTANCES(255)까지다.
PIPE_UNLIMITED_INSTANCES가 전달되면 255까지가 아닌 생성 가능한 최대개수만큼(시스템 리소스에 따라 다르다) 생성허용.
5)nOutBufferSize:이름있는 파이프의 출력 버퍼 사이즈를 지정한다. 0입력 시 Windows디폴트 값이 설정된다.
6)nInBufferSize:이름있는 파이프의 입력 버퍼 사이즈를 지정한다. 0입력 시 Windows디폴트 값이 설정된다.
7)nDefaultTimeOut:WaitNamedPipe함수에 적용하 기본 만료 시간을 ms단위로 지정한다.
8)lpSecurityAttributes:보안 속성을 지정한다.

세 번째 전달인자인 dwPipeMode에는 다음 설정값들이 OR(|)연산되어 전달된다.
데이터 전송방식:PIPE_TYPE_BYTE(바이트), PIPE_TYPE_MESSAGE(메시지)
데이터 전송 시 바이너리 형태로 전송할 지 메시지 방식으로 전송할지를 결정한다.
파일을 개방할 때 바이너리, 텍스트 모드로 개방하는 것과 비슷하다. 메시지 전달 시 데이터가 텍스트 모드.
데이터 수신방식:PIPE_READMODE_BYTE(바이트), PIPE_READMODE_MESSAGE(메시지)
데이터 수신시 바이너리(바이트 스트림)방식으로 읽을 것인지, 메시지(텍스트)방식으로 읽을 것인지 결정한다.
함수 리턴방식:PIPE_WAIT(블로킹), PIPE_NOWAIT(넌 블로킹)
무조건 PIPE_WAIT이 전달된다고 생각하자. PIPE_NOWAIT는 호환성을 위해 제공되는 전달인자일 뿐이다.
문자열을 주고받는다면 PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
바이너리 데이터를 주고받는다면 PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT

위 함수를 통해서 생성한 파이프를 연결 요청 대기 상태로 변경시킬 때 사용하는 함수
BOOL ConnectNamedPipe(
	HANDLE hNamedPipe, 1)
	LPOVERLAPPED lpOverlapped 2)
);
If the function fails, the return value is zero.
1)hNamedPipe:CreateNamedPipe함수 호출을 통해서 생성한 파이프의 핸들을 전달한다.
2)lpOverlapped:중첩 I/O를 위한 전달인자이다. 일단 NULL을 전달하자.

Named파이프 통신은 어렵다. 디자인된 API를 정확히 인식하기는 조금 까다롭다. 하지만 중요하다.

우선 클라이언트가 서버에 접속한다.
이어서 클라이언트는 파일 이름 하나를 메시지 형태로(문자열로) 전달한다.
이 과정에서 완전경로를 지정해서 전달해도 된다.
마지막으로 서버는 이에 해당하는 파일을 열어서 파일의 전체내용을 클라이언에게 문자열로 전달한다.
8_6.cpp namedpipe_server.cpp
파이프의 최대 개수는 처음 CreateNamedPipe함수가 호출될 때 지정된다.
그러나 그 이후부터는 단지 파이프 생성의 목적만으로 호출된다.
그래도 처음 호출할 때 파이프의 최대 개수와 동일한 값이 이후에도 전달되어야 한다.
동시에 둘 이상의 클라이언트 연결을 허용할 수 없는 구조인데 멀티쓰레드 공부 후에는 구조를 변경할 수 있다.
8_7.cpp namedpipe_client.cpp
WaitNamedPipe함수
BOOL WaitNamedPipe(
	LPCTSTR lpNamedPipeName, 1)
	DWORD nTimeOut 2)
);
If an instance of the pipe is not available before the time-out internal elapses, the return value is zero.
1)lpNamedPipeName:상태 확인의 대상이 되는 파이프 이름을 지정한다.
2)nTimeOut:타임아웃 시간을 설정한다. 이 시간이 지나서 함수를 빠져나올 경우 FALSE가 반환된다.
그리고 여기서 타임아웃시간을 NMPWAIT_WAIT_FOREVER로 설정할 경우 연결 가능한 상태가 될 때까지 기다리게 되며,
NMPWAIT_USE_DEFAULT_WAIT로 설정할 경우 디폴트로 정의되어 있는 시간만큼만 기다리게 되는데, 이 디폴트 시간이라는
것이 서버에서 CreateNamedPipe함수를 호출하면서 전달한 7번째 인자를 통해 결정된다.
서버를 먼저 실행시킨 상태에서, 클라이언트를 실행시킨다.
비록 한 순간에 하나의 클라이언트밖에는 실행이 불가능하지만, 서버가 실행 중에 있는 한 계속해서 클라이언트를
실행시킬 수 있다.
파이프의 속성을 변경시키는 함수 SetNamedPipeHandleState. 값을 담고 있는 변수의 주소를 지정하는 방식이다.
BOOL SetNamedPipeHandleState(
	HANDLE hNamedPipe, 1)
	LPDWORD lpMode, 2)
	LPDWORD lpMaxCollectionCount, 3)
	LPDWORD lpCollectDataTimeout 4)
);
If the function failed, the return value is zero.
1)hNamedPipe:파이프와의 연결 속성을 변경시키기 위한 핸들 지정.
2)lpMode:읽기 모드와 함수 리턴방식에 대한값을 OR(|) 연산하여 전달한다. CreateNamedPipe함수의 전달인자와
같은 이름으로 구성된다. 메시지 기반으로 설정할 때에는 PIPE_READMODE_MESSAGE을, 바이너리 기반으로 설정하고자
하는 경우에는 PIPE_READMODE_BYTE을 인자로 구성한다. 그리고 리턴방식에 대한 값 PIPE_WAIT와 PIPE_NOWAIT 중에
하나를 설정해야 하는데, 무조건 PIPE_WAIT으로 설정한다.
3)lpMaxCollectionCount:서버로 데이터를 보내기에 앞서서 버퍼링할 수 있는 최대 바이트 크기를 지정하는데 사용.
여기서 지정한 값 이상으로의 버퍼링은 불가능하다. NULL을 전달해서 이 값을 지정하지 않아도 된다. 만약에
클라이언트와 서버가 같은 PC상에서 동작한다면 반드시 NULL을 전달해야 한다.
4)lpCollectionDataTimeout:서버로 데이터를 보내기에 앞서서 버퍼링을 허용하는 최대 시간(ms)을 지정하는데 사용.
세 번째 전달인자가 NULL이었다면 NULL을 전달할 수 있으며, 클라이언트와 서버가 같은 PC상에서 동작한다면 반드시
NULL을 전달해야 한다.

03 프로세스 환경변수
자식 프로세스에게 핸들 정보를 전달하기 위해서 파일을 활용했었다.
이보다는 프로세스 생성 시 main함수의 매개변수를 활용하는 것이 훨씬 안정적이다.
또한 프로세스 환경변수를 활용하는 방법도 있다.
프로세스별로 별도의 메모리 공간에 문자열 데이터를 저장하고 관리할 수 있도록 되어 있다.
문자열의 구조는 다음과 같으며, 환경변수라 한다.
key = value
[key, value]의 형태를 띠므로 둘 이상의 데이터를 관리하기가 좋다.
또한 부모 프로세스는 자식 프로세스 생성 시, 자식 프로세스의 환경변수를 등록할 수도 있고, 그냥 부모 프로세스의
환경변수를 상속시킬 수도 있다.
값을 참조하는 과정에서 key와 value를 따로 분리시킬 필요도 없다.
함수를 통해 우리가 쉽게 등록 및 참조할 수 있기 때문이다.
BOOL SetEnvironmentVariable(
	LPCTSTR lpName, 1)
	LPCTSTR lpValue 2)
);
If the function fails, the return value is zero.
1)lpName:key에 해당하는 값을 지정한다. 이후에 key를 통해서 value값을 참조하게 된다.
2)lpValue:value에 해당하는 값을 지정한다.
위 함수를 통해 등록한 환경변수를 참조할 때 사용하는 함수.
DWORD GetEnvironmentVariable(
	LPCTSTR lpName, 1)
	LPTSTR lpBuffer, 2)
	DWORD nSize 3)
);
If the function fails, the return value is zero.
1)lpName:key를 전달한다. key에 해당하는 value를 얻게 된다.
2)lpBuffer:value 값을 저장하기 위한 메모리의 주소를 지정한다.
3)nSize:lpBuffer가 가리키는 메모리의 크기를 지정한다.
함수는 성공 시 lpBuffer에 저장된 문자열의 길이를 반환한다.
부모 프로세스가 자신의 환경변수를 등록하고, 자식 프로세스에게 상속시켜 자식프로세스가 값을 확인하는 예제
8_8.cpp EnvParent.cpp

이것만은 알고 갑시다
1. 핸들 테이블
커널 오브젝트와 핸들 사이에 핸들 테이블이 존재한다. 이로서 핸들을 참조하여 특정 커널 오브젝트를 가리킬 수 있다.
2. 핸들과 핸들 테이블
핸들 테이블은 프로세스 별로 독립적이다. 그리고 숫자가 핸들로서 의미를 지니기 위해서는 해당 숫자가 핸들 테이블에
등록되어야 한다. 등록되는 순간부터 핸들이라 할 수 있으며 이 핸들을 통해서 커널 오브젝트에 접근하는 것이 가능.
3. 핸들의 상속
핸들은 자식 프로세스를 생성하는 과정에서 상속할 수 있다. 핸들이 자식 프로세스에게 상속된다는 말은 부모
프로세스의 핸들 테이블 정보가 자식 프로세스의 핸들 테이블에 복사된다는 뜻이다.
4. 가짜 핸들(Pseudo 핸들)
GetCurrentProcess함수 호출을 통해서 얻은 핸들을 가리켜 가짜 핸들이라 한다. 이는 핸들 테이블에 등록된 핸들값이
아닌, 자기 자신의 프로세스를 가리키기 위한 약속된 상수이기 때문이다. 핸들 테이블에 등록된 핸들을 얻기 위해서는
DuplicateHandle함수를 사용해야 한다.
5. 파이프
이름없는 파이프와 이름있는 파이프의 특성.

*/