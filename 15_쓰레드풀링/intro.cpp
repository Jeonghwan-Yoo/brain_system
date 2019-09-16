/*
쓰레드 풀에 대한 이해
쓰레드 풀 제작으로 명령 프롬프트 프로젝트를 대신.
쓰레드 풀을 직접 만들어 보는 것은 쓰레드의 이해와 응용력 향상을 위해서 가치 있는 일.
쓰레드의 생성과 소멸은 시스템에 많은 부담을 준다.
때문에 빈번한 쓰레드의 생성과 소멸은 피해야 한다.
만약 은행 창구 앞에 앉아 업무를 보는 행원들은 밀려오는 고객들의 업무를 처리해 준다.
서너 명의 은행 직원이 수십, 수백 몇이나 되는 고객의 업무를 처리하는 것이 쓰레드 풀 모델이다.
만약 밀려오는 고객의 수만큼 행원들을 할당하고, 업무 처리가 끝났을 때 행원들도 그 자리를 같이 일어선다면,
그리고 이어서 들어오는 고객의 수만큼 다시 새로운 행원들이 자리에 앉고, 한다면 상당히 어수선하고 업무 처리도 지연.
이것이 처리해야 할 일이 있을 때마다 새로운 쓰레드를 생성해서 할당하는 시스템 모델이다.
그러니 쓰레드 풀을 유지하는 것은 성능 향상에 도움이 된다.
쓰레드 풀의 기본 원리는 쓰레드의 재활용이다.
할당된 일을 마친 쓰레드를 소멸시키지 않고, 쓰레드 풀에 저장해뒀다가 필요할 때 다시 꺼내 쓰는 개념.
즉, 쓰레드의 생성과 소멸에 필요한 비용을 지불하지 않겠다는 뜻.

쓰레드풀 동작 원리
                                 ┌─── 쓰레드 풀 ───┐
-------> work|쓰레드1 <---------- │ 쓰레드1 쓰레드2 │
처리요구              쓰레드 할당  │    ...         │
<------- work|쓰레드1 ----------> │  쓰레드1       │
처리완료            메모리 풀 반환 └────────────────┘

쓰레드 풀은 처리해야 할 일(Work)이 등록되기 전에 생성되는데, 풀이 생성됨과 동시에 쓰레드들도 생성되어
풀에서 대기.
지능적인 풀은 처리해야 할 일의 증가 및 감소에 따라서 풀 안의 쓰레드 개수를 늘리기도 하고, 줄이기도 한다.
일이 등록되면 쓰레드 풀이 존재하는 쓰레드 하나를 임의로 할당해서 일의 처리를 도모한다.
만약에 풀에 존재하는 쓰레드 수보다 처리해야 할 일의 수가 많다면, 일의 순서대로 처리되도록 디자인할 수도 있고,
빠른 일 처리를 위해 추가적인 쓰레드가 생성되도록 풀을 디자인할 수도 있다.

02 쓰레드 풀의 구현
만들어볼 쓰레드 풀은 단순한 구조를 지닌다.
개념의 이해 측면에서 장점.
부족한 부분만 일부 보완하고 개선하면 실제 개발에 활용할 수 있다.
쓰레드 풀의 구현 자체가 난이도 있는 일.
쓰레드를 잘 이해하고 있어야 하며, 동기화 기법에 대한 충분한 이해도 필요.

쓰레드 풀 구현의 모듈별 해석
쓰레드 풀을 구성하는 데 있어서 정의된 자료형과 함수들.
자료형과 함수들의 역할 및 관계를 이해하면, 전체 구조를 이해할 수 있다.

쓰레드 풀 자료구조
typedef void (*WORK) (void);

typedef struct __WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

//Work와 Thread 관리를 위한 구조체
struct __ThreadPool
{
	//Work를 등록하기 위한 배열
	WORK workList[WORK_MAX];

	//Thread 정보와 각 Thread별 Event 오브젝트
	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];

	//Work에 대한 정보
	DWORD idxOfCurrentWork; //대기 1순위 Work Index
	DWORD idxofLastAddedWork; //마지막 추가 Work Index+1

	//Number of Thread;
	DWORD threadIdx; //Pool에 존재하는 Thread의 개수
} gThreadPool;
Work는 함수를 가리키는 포인터로 선언되어 있다.
void function(void);
이것이 쓰레드에게 일을 시키기 위한 작업의 기본 단위.
쓰레드에게 일을 시키기 위해서는 일에 해당하는 하나의 함수를 정의해야 하는데, 이 함수의 반환형과 매개변수
타입이 모두 void여야 한다.
필자가 임의로 정한 것으로 변경 가능.
구조체 WorkerThread는 생성되는 쓰레드의 정보를 담기 위한 구조체.
간단히 쓰레드의 핸들과 ID 정보만 담도록 구성했는데, 필요에 따라 확장이 가능.
가장 중요한 구조체 _ThreadPool은 typedef 없이 자료형 선언과 동시에 전역 변수 형태로 gThreadPool을 선언.
그리고 쓰레드 풀에 해당하고 쓰레드 풀을 표현하는 자료구조이다.
멤버들은 두 부류로 나뉘는데, 하나는 Work에 관련된 멤버들이고 다른 하나는 쓰레드에 관련된 멤버들.

일에 관련된 멤버들
WORK workList[WORK_MAX];
DWORD idxOfCurrentWork; //대기 1순위 Work Index
DWORD idxOfLastAddedWork; //마지막 추가 Work Index+1
workList는 Work을 등록하는 저장소이다.
idxOfLastAddedWork는 마지막에 추가된 Work index보다 1많은 값을 유지하면서 새로운 Work가 등록될 때
등록 위치를 가르쳐준다.
idxOfCurrentWork은 처리되어야 할 Work의 위치를 가리킨다.
         idxOfCurrentWork    idxOfLastAddedWork
workList         ↓                    ↓ 
(work)|(work)|(work)| work | work |      |...
                ↙할당                  ↖등록
             쓰레드                   work

풀에 저장된 쓰레드와 관련된 멤버들
WorkerThread workerThreadList[THREAD_MAX];
HANDLE workerEventList[THREAD_MAX];
DWORD threadIdx;
풀에 저장된 쓰레드 정보는 workerThreadList에 저장한다.
그리고 workerEventList는 각 쓰레드 별로 하나씩 할당되는 이벤트 동기화 오브젝트를 저장하고 있는 배열.
workerThradList[3]에 등록된 쓰레드는 workerEventList[3]에 저장된 이벤트 동기화 오브젝트와 쌍을 이룸.
마지막으로 threadIdx는 저장된 쓰레드의 개수 정보를 담는다.
따라서 쓰레드 정보가 저장되어야 할 인덱스 정보로 활용할 수 있다.
쓰레드에게 일이 부여된다는 것은 쓰레드가 호출해서 실행할 함수를 지정해 준다는 뜻.
만약 쓰레드에게 할당된 일이 없다면 쓰레드는 Waitfor 관련 함수 호출을 통해 Blocked 상태가 되어야 한다.
그리고 새로운 일이 들어 왔을 때 일을 실행해야 한다.
이러한 컨트롤을 위해 쓰레드 하나당 하나씩의 이벤트 오브젝트가 필요한데, 이를 workerEventList에 저장.
idxOfCurrentWork와 idxOfLastAddedWork는 증가는 하되 감소는 하지 않는다.
WORK_MAX만큼 일이 등록되고 나면 더 이상의 등록은 불가능하다.
배열을 원형배열의 형태로 변경하면(STL) 된다.
원형 배열 대신에 Work와 Work의 등록여부를 나타내는 멤버로 구조체를 정의하고, 이를 기반으로 배열을 선언하는
방법도 고려할 수 있다.

쓰레드 풀의 함수 관계
WORK GetWorkFromPool(void);
쓰레드 풀에서 Work를 가져올 때 호출하는 함수.
DWORD AddWorkToPool(WORK work);
새로운 Work을 등록할 때 호출하는 함수이다.
DWORD MakeThreadToPool(DWORD numofThread);
쓰레드 풀이 생성된 이후에 풀에 쓰레드를 생성(등록)하는 함수이다. 인자로 전달되는 수 만큼 쓰레드가 생성.
void WorkerThreadFunction(LPVOID pParam);
쓰레드가 생성되자마자 호출하는 쓰레드의 main함수이다. 이 함수의 구성을 봐야 어떻게 Work을 할당받아서
처리하는지 그리고 Work가 없을 때의 쓰레드 상태들을 알 수 있다.

쓰레드 풀 메커니즘
                2. 등록:AddWorkToPool     
workList                ↓
(work)|(work)|(work)| work |      |....
                                ↖────5. Work 얻음:GetWorkFromPool────────┐
3. 이벤트 오브젝트 Signaled 상태로 변경                                    \
 event   event  event                                                     \
   ↑       ↑      ↑ WaitForSingleObject:Blocked 상태                        \
┌──┼───────┼──────┼──┐                                                     쓰레드
│쓰레드  쓰레드  쓰레드│──4. WaitForSingleObject 함수 반환:Running 상태로 변경──↗
└────────────────────┘쓰레드 풀
1. 쓰레드 등록:MakeThreadToPool(3)

[단계 1]
전역으로 선언된 쓰레드 풀에 MakeThreadToPool 함수의 호출을 통해서 쓰레드를 생성해 등록시킨다.
이렇게 생성된 쓰레드는 이벤트 오브젝트가 Signaled 상태가 되기를 기다리며 Blocked 상태가 된다.
[단계 2]
AddWorkToPool 함수 호출을 통해 Work를 등록한다.
[단계 3]
Work가 등록되면, 쓰레드 풀에서 Blocked 상태에 있는 모든 이벤트 오브젝트를 Signaled 상태로 변경.
[단계 4]
모든 이벤트 오브젝트가 Signaled 상태가 되므로, 모든 쓰레드가 Running 상태가 된다.
그러나 Work를 할당받은 하나의 쓰레드를 제외하고 나머지는 다시 Blocked 상태가 된다.(다소 비효율적인 부분)
[단계 5]
Running 상태로 남아 있게 될 하나의 쓰레드는 GetWorkFromPool 함수 호출을 통해 Work를 할당받아 실행하게 된다.

논리적으로 workList는 쓰레드 풀 안에 존재하는 대상이 아니다. 그러나 쓰레드 풀 안에 존재한다고 해도 문제 없다.
구현방법에 따라 달라질 수 있는 것이다. 설명은 분리해서 하지만 예제에서는 쓰레드 풀 안에 workList가 존재.

전역으로 선언된 쓰레드 풀 접근 동기화
쓰레드 폴에 해당하는 gThreadPool은 전역으로 선언되어 있고, 둘 이상의 쓰레드에 의해서 참조되는 메모리 영역.
따라서 gThreadPool의 접근에 동기화가 필요하다.
뮤텍스 기반 동기화 함수들을 래핑(Rapping)한 것.
void InitMutex(void);
void DeInitMutex(void);
void AcquireMutex(void);
void ReleaseMutex(void);

쓰레드 풀 구현 소스코드
ThreadPooling.cpp
Work에 해당하는 함수는 TestFunction이다.

이것만은 알고 갑시다
1. 쓰레드 풀링의 이해
쓰레드 풀링은 한번 생성한 쓰레드를 재활용해서 시스템의 부담을 덜어주기 위한 기법이다.
이는 쓰레드의 생성과 소멸에 소모되는 리소스가 상당하기 때문에 등장. 일단 여러 개의 쓰레드를 생성하고
실행해야 할 일이 등록될 때마다 미리 생성해 놓은 쓰레드 중 하나를 할당한다. 그리고 일이 끝나면 쓰레드는
소멸시키지 않고 다음 일을 위해 보관한다.
2. 쓰레드 풀링의 동작 원리
필요한 상황에 최적의 쓰레드 풀을 제공할 수도 있고, 쓰레드 풀의 특성을 정확히 알아서 풀의 도입여부를 결정하는 데
도움이 된다.

*/