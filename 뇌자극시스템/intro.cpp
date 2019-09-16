/*
03_04 System Programming Project Design
명령 프롬프트 프로젝트의 제안
help를 입력하면 실행 가능한 명령어들의 종류와 기능이 간단히 나열된다.

명령 프롬프트 프로젝트의 제안과 EXIT명령어의 구현
주목해야할 점은
1)명령어를 추가할 때 변경되는 부분
2)명령어의 대소문자를 구분하지 않기 위해서 고려된 부분
3)명령어 EXIT가 입력되었을 때 프로그램 종료방식
CommandPrmpt_One.cpp

05_06 명령 프롬프트 프로젝트 기능 추가
CmdProcessing함수만 변경하면 된다.
생소한 명령어가 입력되면 표준 검색경로에 존재하는 실행파일로 간주하고 프로세스를 생성하면 된다.
CommandPrmpt_Two.cpp

06_04 명령 프롬프트 프로젝트 기능 추가
이번에는 echo명령어와 start명령어를 추가해보자.
start는 입력된 명령어를 별도의 명령 프롬프트를 띄운 상태에서 실행하도록 요구하는 명령어이다.
>start dir하면 다른 프롬프트 창에서 결과를 보여준다.
start만 입력해도 새로운 명령 프롬프트가 생성된다.
dir명령어(파일 및 디렉터리 리스트 출력 명령어) 앞에 start를 붙여주면, 새로운 명령 프롬프트를 띄운 다음에
dir명령어가 실행된다.
옵션도 추가가 가능해서 dir명령어에 /l을 옵션으로 붙여주면 출력이 소문자로만 나타난다.
echo명령어는 문자열을 에코 출력한다.
echo명령어 뒤에 입력된 문자열을 그대로 출력하는 기능을 가진다.
>start echo This is a echo message!라고 치면 다른 프롬프트 창에서 This is a echo message!가 출력된다.
특히 프로세스 생성 시 문자열 매개변수의 전달에 신경써보자.
기존 코드를 기반으로 하되, 필요하다면 코드 일부를 변경시키고 세분화하자.

필자가 구현한 답안
CommandPrmpt_Three.cpp
Check Point 1에 대한 설명
인터넷 익스플로러의 실행파일의 이름은 IEXPLORE.EXE이다.
이러한 응용프로그램도 명령 프롬프트 상에서 실행하면서 전달할 수 있다.(main함수에 전달되는 문자열)
만약에 >iexplore www.daum.net하면 익스플로러가 실행되면서 홈페이지로 접속하게 된다.
IEXPLORE.EXE는 'C:\Program Files\Internet Explorer'에 저장되어 있다.
명령 프롬프트상에서 실행되는 유용한 프로그램들도 문자열을 인자로 전달받는 것이 보통이다.
따라서 우리가 구현하는 프로그램에서도 실행파일의 이름뿐만 아니라 뒤에 붙어서 전달되는 문자열도 처리해야 한다.

08_04 명령 프롬프트 프로젝트 기능 추가
추가할 명령어는 두가지로 하나는 현재 실행 중인 프로세스 정보를 출력하는 명령어이고, 다른 하나는 이름으로
프로세스를 종료시키는 명령어이다.

CreateToolhelp32Snapshot
현재 실행 중인 프로세스 정보를 얻기 위해서 알아야 할 함수들이 더 있다.
8_10.cpp ListProcessInfo.cpp

여러분 차례
위 예제를 참조해서 프로세스 정보를 출력하는 명령어와 프로세스 이름으로 해당 프로세스를 종료시키는 명령어를 추가.
첫번째 명령어를 lp(List Process), kp(Kill Process)로 하자.
프로세스 종료를 위해서는 TerminateProcess함수를 사용하면 된다.
BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode);
종료시킬 프로세스의 핸들을 요구하고 있는데, 문제가 된다.
CreateToolHelp32Snapshot함수를 통해 얻을 수 있는 프로세스 정보는 핸들이 아닌 프로세스 ID정보이다.
즉 TerminateProcess를 사용하기 위해서는 프로세스이름 -> 프로세스ID -> 프로세스핸들의 변환 과정.
OpenProcess함수를 이용하면 해결할 수 있다.

필자가 구현한 답안
HANDLE OpenProcess(
	DWORD dwDesiredAccess,
	BOOL bInheritHandle,
	DWORD dwProcessId
);
If the function fails, the return value is NULL.
이 함수는 프로세스를 열 때 사용된다.
프로세스를 연다는 것은 프로세스 ID를 통해 핸들을 얻겠다는 뜻이다.
dwProcessId로 프로세스ID를 전달하면 이 ID에 해당하는 프로세스 핸들이 반환된다.
첫 번째, 두 번째 전달인자는 반환되는 핸들의 성격을 결정짓는다.
함수 호출이 성공하면 해당 프로세스의 Usage Count는 하나 증가한다.
따라서 반드시 CloseHandle함수를 통해 핸들을 반환해야 한다.
CommandPrmpt_Four.cpp
Windows시스템 디렉터리에 tskill.exe라는 실행파일이 존재하는데 명령 프롬프트 상에서 실행 가능한 프로그램이다.
이 프로그램이 제공하는 기능은 이름을 통해서 프로세스를 종료시키는 것이다.

09_03 명령 프롬프트 프로젝트 기능 추가
추가할 것은 Redirection 기능.

Redirection의 이해
리다이렉션은 방향 재지정을 의미한다.
콘솔로 출력이 이뤄져야 하는 상황에서 방향 재지정을 하면 파일에 출력이 이뤄지게끔 할 수 있다.
마찬가지로 콘솔로부터 입력이 이뤄져야 하는 상황에서 방향 재지정을 하면 파일로부터 입력이 이뤄지게끔 할 수 있다.
꼭 파일과 콘솔 관계에서만 리다이렉션이 성립하는 건 아니고 입력과 출력의 방향이 재지정된다는 사실이 중요하다.
C:\>sort
bbbbb
ccccc
aaaaa
^Z
aaaaa
bbbbb
ccccc
콘솔에 sort라는 명령어가 있어 sort를 입력하고 문자열을 여러 개 입력한다.
그리고 Ctrl+Z키를 입력하면 입력이 완료되고, 입력된 문자열을 순서대로 정렬해서 출력한다.
Ctrl+Z는 콘솔에서 EOF를 의미한다. 입력의 끝.
sort명령어의 입력과 출력을 재지정할 수 있다.
즉 sort의 입력을 파일로 재지정하면 지정된 파일로부터 데이터를 읽어 들이게 된다.
마찬가지로 sort의 출력을 파일로 재지정하면 출력 내용이 파일에 저장된다.
명령 프롬프트는 이러한 리다이렉션 기능을 제공한다.
type명령어는 파일의 내용을 출력하는 기능을 지닌다.
C:\>sort > sort.txt
44444
88888
22222
11111
^Z
C:\>type sort.txt
11111
22222
44444
88888
'>'기호는 출력 리다이렉션을 의미한다.
sort의 출력결과를 sort.txt로 리다이렉션하라는 의미이다.
따라서 sort의 출력결과는 sort.txt에 저장된다.
입력을 재지정하기 위해 입력 재지정에 사용되는 파일을 하나 만든다.
입력 리다이렉션에 사용되는 기호는 '<'이다.
C:\>type sort.txt
4. System Programming
2. C++
1. JAVA
3. Visual Basic
C:\>sort < sort.txt
1. JAVA
2. C++
3. Visual Basic
4. System Programming
C:\>sort < sort.txt > sort2.txt
C:\>type sort2.txt
1. JAVA
2. C++
3. Visual Basic
4. System Programming

Redirection 구현방법
일단 sort명령어를 구현해야 한다.
구현의 편의를 위해 최대 문자열의 개수는 100개 정도로 제한.
STARTUPINFO si = { 0, };
si.cb = sizeof(si);
PROCESS_INFORMATION pi;
//리다이렉션 대상이 되는 파일의 핸들은 상속가능해야 한다.
//파일이 자식 프로세스 리다이렉션 대상이 된다는 것은 핸들의 상속을 의미한다.
SECURITY_ATTRIBUTES fileSec = { 0, };
fileSec.bInheritHandle = TRUE; //상속가능해야 지정 가능!
TCHAR fileName[] = _T("output.txt");
HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ, &fileSec, CREATE_ALWAYS,
	FILE_ATTRIBUTE_NORMAL, NULL);
//파일 핸들 정보를 저장하고 있다. hStdOutput은 표준 출력을 리다이렉션하는 용도.
//따라서 생성되는 자식 프로세스의 표준 출력은 fFile이 가리키는 파일이 된다.
si.hStdOutput = hFile; 
si.hStdInput = GetStdHandle(STD_INPUT_HANDLE); //표준입력 리다이렉션하는 용도
si.hStdError = GetStdHandle(STD_ERROR_HANDLE); //표준 에러출력을 리다이렉션하는 용도
si.dwFlags |= STARTF_USESTDHANDLES; //위에 지정한 리다이렉션 정보들을 반영하라는 의미.
isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
입력 및 출력의 리다이렉션은 STARTUPINFO구조체를 통해 지정할 수 있다.
HANDLE GetStdHandle(
	DWORD nStdHandle
);
If the function fails, the return value is INVALID_HANDLE_VALUE.
이 함수는 표준 입출력 핸들을 얻기 위해 사용된다.
표준 입력으로 지정되어 있는 장치(기본적으로 콘솔)의 핸들을 얻으려면 STD_INPUT_HANDLE을 인자로 전달하면 된다.
표준 출력의 핸들을 얻기 위해서는 STD_OUTPUT_HANDLE을, 표준 에러 출력핸들을 얻으려면 STD_ERROR_HANDLE을 인자로.

필자가 구현한 답안
이 문제해결의 포인트는 프로세스 생성에 있다.
활용하려면 sort명령어는 독립된 프로세스로 생성해야 한다.
RedirectSort.cpp
실행파일로 만들어두면, 명령 프롬프트 프로세스가 자식 프로세스로 만들 수 있다.
CommandPrmpt_Five.cpp

15_03 명령 프롬프트 프로젝트 기능 추가
입력과 출력을 연결하는 파이프
type이라는 명령어가 있다.
이 명령어는 텍스트 파일이 저장하고 있는 내용을 콘솔창에 출력하는 기능을 지닌다.
>type Random.txt
555
Good
222
Best
777
Dream
Last
111

>type Random.txt | sort
111
222
555
777
Best
Dream
Good
Last
같이 명령어를 조합하고 있다.
'|'기호를 파이프라고 한다.
표준입력               표준출력  표준입력
-------> Process type -------> --------> Process sort
|연산자 왼쪽에 오는 프로세스의 표준 출력이 |연산자 오른쪽에 오는 프로세스의 표준 입력으로 연결된다.
명령어를 조합할 경우, type 프로세스가 내보내는 표준 출력이 sort명령어의 표준입력으로 삽입.
이처럼 서로 다른 프로세스의 입력과 출력을 연결하는 경우, 파이프를 구성한다고 한다.
그래서 type명령어를 구현하고, 이전에 구현한 sort 명령어와의 파이프 구성이 가능하도록해야 한다.

구현 원리
파이프 구현을 위해서는 Anonymous Pipe를 활용해야 한다.
그리고 리다이렉션 기법을 활용해야 한다.
다만 파이프 통신과 입출력 리다이렉션을 동시에 적용해야 한다.

프로세스간 통신기법으로 소개한 파이프도 입력과 출력이 연결된 핸들을 생성하는 방식이고, '|'연산도 두 프로세스의
입력과 출력을 연결하는 방식이다.

구현 사례
파이프를 생성해서 하나는 출력을 리다이렉션하고, 또 다른 하나는 입력을 리다이렉션한다.

파이프 구현 원리
            출력 리다이렉션  이름없는 파이프 생성 anonymous pipe                    입력 리다이렉션  
Process type ------------> |파이프 Input handle ------------ 파이프 Output handle| -----------> Process sort 

위와 같은 구현을 위해서는 type 명령어도 sort 명령어와 마찬가지로 독립된 프로세스로 생성해야 한다.
type.cpp
CommandPrmpt_Six.cpp

18_03 명령 프롬프트 프로젝트 기능 추가
재귀를 통한 xcopy 명령어를 구현해본다.

XCOPY의 이해
xcopy는 디렉터리 단위 복사 기능이 있다.
xcopy '디렉터리A' '디렉터리B' /s
'디렉터리A'는 복사 대상이 되는 원본 디렉터리 정보이고, '디렉터리B'는 복사할 위치 정보를 나타낸다.
옵션 /s는 하위 디렉터리까지(파일을 포함해서) 전부 복사하라는 의미를 지닌다.

XCOPY의 구현 범위 및 방법
옵션 정보가 붙을 수 있다는 것은 그만큼 다양한 기능을 제공하고 조합도 가능하다는 뜻이다.
여기서는 단순한 디렉터리 복사만 가능하도록(하위 포함) xcopy 명령어의 기능을 제한.
모든 서브 디렉터리 구조를 복사해야 하므로, 재귀적인 탐색방법을 고려하는 것이 좋다.
그리고 탐색을 위해, 파일인지 디렉터리 정보인지 확인하기 위해 참조하고, 구조체 WIN32_FIND_DATA의 멤버
wFileAttributes을 통해 얻을 수 있는 정보들을 확인해본다.
더불어 파일 복사와 관련된 함수 사용.
BOOL CopyFile (
	LPCTSTR lpExistingFileName, 1)
	LPCTSTR lpNewFileName, 2)
	BOOL bFailIfExists 3)
);
If the function fails, the return value is zero.
1)lpExistingFileName:복사 대상인 원본 파일 이름을 지정한다.
2)lpNewFileName:복사 결과로 생성될 파일 이름을 지정한다.
3)bFailIfExists:TRUE가 전달되고, 두 번째 전달인자 lpNewFileName이 지정하는 파일이 존재할 경우 함수 호출은 실패.
 
XCOPY의 구현 사례
디렉터리를 순차적으로 검색해 가며, 디렉터리이면 디렉터리 생성, 파일이면 파일 복사를 반복하는 구조이다.

*/