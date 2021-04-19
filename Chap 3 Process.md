# Chap 3 Process

# Concept of Process

### Process

- 실행 중인 프로그램

### Representing a process

- Current instruction : PC = 현재 실행 중인 명령어 주소를 저장하는 CPU register
- Register state (CPU) → 프로세스는 register의 값을 변경함
- Memory contents (Stack, Heap, 전역 변수)
- Parent info

⇒ 프로그램은 하나 이상의 프로세스를 가질 수 있다

# Process Memory Layout (⇒process가 어떻게 메모리공간을 사용하는지)

![Untitled](https://user-images.githubusercontent.com/33208303/115229194-b370cd00-a14d-11eb-849a-d4b6455c5167.png)

- 32bit라고 가정했을 경우, 각 프로세스에는 위와 같은 형태의 **가상** 메모리가 4GB 할당된 것으로 생각
  - 4GB인 이유는 32bit architecture에서 인식할 수 있는 최대 메모리 크기가 4GB임  
  - 이때, Reserved by Kernel은 1GB를 가짐
- Stack area (segment)
  - grows downward as functions are called
  - 호출되는 함수들의 파라미터, 지역변수, return value가 저장
- Heap area
  - grows upward as more dynamic memories are requested
  - 동적 할당 메모리 처리
  - ex. malloc() or brk()
- Data segment
  - 전역 변수가 저장되는 지역 (thin region)
- Text segment
  - 프로그램 code가 위치 (Binary)
  - PC는 Text segment 안에서 이동
- 프로그램이 많은 함수를 호출하고, 많은 메모리를 동적으로 할당하게 된다면, stack 영역과 heap 영역이 충돌하게 됨
- Kernel stack이 필요한 이유
  - System call 호출하여 Kernel로 이동하였을 때, return 값을 저장하기 위해 필요

![Untitled 1](https://user-images.githubusercontent.com/33208303/115229195-b4096380-a14d-11eb-9505-7a3277d70c81.png)

- Kernel Stack은 여러 개가 존재하고, 각 프로세스에 할당됨

# Process State (Process Life Cycle)

![Untitled 2](https://user-images.githubusercontent.com/33208303/115229197-b4096380-a14d-11eb-9e08-3eea3ecdac21.png)

- new : process create
- ready : ready queue가 존재, processor에 할당되기를 기다리는 프로세스 존재
- running : ready queue에서 OS가 알고리즘에 의해 한 프로세스를 동작시킴
  - single core의 경우, 어느 한 시점에서나 항상 1개의 프로세스만 동작 중
- waiting : event의 occur을 기다리는 프로세스들이 wait queue에 존재
  - 특히 I/O completion을 기다리는 프로세스가 위치
- terminated : 프로세스 종료
- preempted : 한 프로세스가 일정 시간 이상 CPU를 사용하여 다른 프로세스의 동작을 위해 다시 ready queue로 이동

# Process (Task) Control Block (PCB) → concept

### PCB : 프로세스를 표현하는 kernel 안의 자료구조

![Untitled 3](https://user-images.githubusercontent.com/33208303/115229199-b4a1fa00-a14d-11eb-86ee-1fb7b4334dcb.png)

- process state : New, ready, running, waiting, halted
- PID
- PC
- register (CPU) : + CPU scheduling info
- memory limits : + Memory-management info (mapping) (page table, segment table)
- list of open files
- Accounting info (keeping track)
  - CPU time usage, job, process # ⇒ scheduling에도 관여

# PCB Representation in Linux

### Struct task_struct

![Untitled 4](https://user-images.githubusercontent.com/33208303/115229200-b4a1fa00-a14d-11eb-93db-2c988688f35c.png)

- 각 프로세스들은 Doubled Linked List 형태로 모두 연결되어져 있다 → 앞, 뒤 모두 참조 가능

# Threads

### 프로세스 내의 single sequence of execution

### PC, register states and stack area가 분리

- 각 thread는 서로 다른 PC값, register 값, stack area를 가짐

### 하나의 프로세스는 하나 이상의 threads를 가질 수 있음

![Untitled 5](https://user-images.githubusercontent.com/33208303/115229204-b53a9080-a14d-11eb-910a-f3b4385fa8a7.png)

- exe 파일 내, 서로 다른 위치에서 code들이 실행됨

⇒ 프로세스에게 할당된 memory 내에서 thread는 memory 사용

# Process switch

![Untitled 6](https://user-images.githubusercontent.com/33208303/115229207-b53a9080-a14d-11eb-9130-af1f2b57ea88.png)

- 프로세스 0이 실행되다가 System call 또는 Interrupt가 발생하면 프로세스 0이 잠시 OS가 되어, PCB0에 현재 프로세스의 상태를 저장하고, PCB1에 저장된 프로세스 1의 상태를 불러온다 → 프로세스 1이 실행된다. 이때 프로세스 0은 idle한 상태
- 프로세스 1의 경우도 동일

⇒ CPU가 쉬지 않고 프로세스를 동작시킴

![Untitled 7](https://user-images.githubusercontent.com/33208303/115229210-b5d32700-a14d-11eb-9d10-4b7cbed1621f.png)

- syscall handling 후 어느 프로세스로 return할 지 결정하는 것 → schduling

# Process Scheduling

- scheduling하는 이유 : CPU 사용을 최대화하기 위함
- Multi-programming : 여러 프로그램을 memory에 올려두고 실행 → **CPU 사용 최대화를 위함**
- Time-sharing : CPU의 시간을 잘게 나누어 여러 user가 사용할 수 있도록 하는 것, 여러 프로그램을 빠르게 switching하면서 동작 → **scheduling을 위함**

⇒ Process Scheduling

: Process에서 실행할 다음 프로세스를 select

### Scheduling Queues → memory에 저장

- job queue
  - Ready Q 전에 프로세스가 load되는 Q → 모든 프로세스가 저장
- Ready queue
  - 실행 준비가 된 프로세스를 저장하고 있는 Q → linked list of PCBs로 구현
- Device queue (=Wait Q, I/O Q)
  - I/O device를 wait하는 프로세스가 저장되는 Q
  - 각각의 device들은 모두 각자의 Device Q를 가짐
  - 작업이 완료되면 다시 ready Q로 돌아감

# Queuing digram

![Untitled 8](https://user-images.githubusercontent.com/33208303/115229192-b2d83680-a14d-11eb-8ac1-23e62ea1a7ba.png)

- 프로세스가 ready Q로 전달 → ready Q에서 특정 알고리즘에 의하여 CPU에서 동작시킬 프로세스를 결정하고 CPU로 전달
- CPU에서는
  - 프로세스가 작업을 모두 완료하고 exit
  - I/O issue로 인해 I/O Q로 전달 → block되었다가 → 작업 완료 후 다시 ready Q로 전달
  - 일정 시간 이상 CPU를 사용하여 다시 ready Q로 전달 (OS가 timer를 set on ⇒ interrupt 발생)

# Scheduler

→ 일종의 function으로 다음 실행할 프로세스를 선택

- 정책에 의해 Q로부터 프로세스를 선택

### Long-term scheduler = job scheduler

- 많은 job 중 일부를 선택하여 ready Q에 push
- job = 모든 processes

### Short-term scheduler = CPU scheduler

- ready Q에 있는 프로세스를 선택하여 CPU에 전달
  - 이때 알고리즘이 필요

### processes type

- I/O bound → I/O 작업 처리 시간이 더 긴 프로세스
- CPU bound → CPU 작업 처리 시간이 더 긴 프로세스
- Long-term scheduler는 I/O bound와 CPU bound의 균형이 좋은 job을 선택해야 한다
  - 균형이 맞지 않고 entirely하다면, CPU나 I/O device가 idle하는 경우가 발생, CPU는 항상 최대한 사용량을 높이는 것을 목표로 하기 때문에 올바르지 X

### scheduling criteria

- CPU utilization 증가
- avg waiting time 감소
- response time 감소
- fairness

# Context Switch (= process switch)

- Context : PCB에 저장되어 있는 프로세스 state = 프로세스의 현재 상태

### Context Switch (Saving & Restoring)

- 현 프로세스의 state를 저장하고, 다른 프로세스의 state를 불러오는 것
- running app 관점에서, 도움이 되는 행위가 아닌 management action일 뿐이기 때문에 무조건 빨라야 한다

### HW support로 context switch time을 줄일 수 있다

- CPU에 multiple register set이 존재한다면,
  원래는 memory에 프로세스의 register값을 모두 저장해야 하지만,
  단순히 pointer를 바꾸는 것으로 대체 가능
- 하지만 2 sets → 2 processes만 가능하므로, 다른 프로세스가 추가된다면
  결국 p1 또는 p2의 register set이 memory에 copy되어야 하기 때문에
  memory copy는 막지 못한다

# Operations on Processes

### Process creation (fork)

- parent/child → tree 구조

### PID : 식별자

### init process (pid = 1)

- first process

### PID가 다 차면 종료된 PID를 내보내고 새로 저장

### Resource

- parent가 fork()로 child 생성
- 이때 memory는 어떻게?

  - 새로 할당 → 프로세스 간 memory balance가 맞지 않는 문제
  - Parent resource 공유 → 정해진 수만큼의 child만 생성가능하기 때문에 성능 저하

  ⇒ 정답이 없고 policy를 따름

- child 프로세스를 생성
  - parent가 다른 일 처리를 위해 생성함
  - parent와 child는 병렬 동작
  - parent는 child의 종료를 기다려야 함

# Process creation in UNIX/Linux

### fork() system call

- 새 프로세스 생성, 새 프로세스의 PID를 return 해줌
  - 새 프로세스에 parent의 memory content를 copy
  - fork() 후에 parent와 child는 병렬적으로 실행됨 (process로서 동일한 취급)
  - fork()'s return value
    - parent → 생성된 child의 PID
    - child → 0

### exec() system call (execl(), execvp(), execlp())

- 원래 있던 프로세스의 정보가 모두 reset되고, 새로운 프로그램 정보가 memory를 차지

  - 새로운 binary file을 memory에 load & run

  ⇒ memory가 새 프로그램의 정보로 갈아엎어짐

  ⇒ control return X → 기존의 memory 정보가 사라지기 때문에 return control이 불가능

### wait() system call

- parent는 wait() 호출로 child의 종료를 기다려야 함

  - child가 종료되면 parent는 해당 작업에 대한 return 값을 받아야 함
    - wait() → parent는 stop

  ⇒ 이때, OS가 child의 종료됨을 parent에게 알려줌

fork() → child에서 exec() 를 호출하게 되면
원래는 memory copy to child이지만
exec() 는 어차피 **memory reset**해버림
⇒ memory copy는 쓸데 없는 time과 effort

# Process Termination

### 프로세스는 종료를 위해 exit() system call 호출

- parent에게 status value가 return → 0 : success, else : error
- resource가 해제 → exit()가 clean up

### parent가 child를 종료시키는 경우

- child가 더 이상 필요 없는 경우 (원하는 작업이 다 이루어진 경우)
- child가 resource를 너무 많이 사용하는 경우
- parent가 종료해야 하는 경우
  - parent가 종료되기 전, 모든 child가 종료되어야 함

### wait()

- parent가 child 프로세스의 종료를 기다리기 위해 사용

```c
pid_t pid;
int status;
pid = wait(&status);
```

- 이때 & 연산자를 사용하는 이유
  - child 종료 시, 종료값과 PID 모두 받기 위해 인자의 주소값을 전달
- parent가 wait() 호출 전까지 OS가 child의 exit status를 저장하고 있음
  - parent가 wait() 호출하지 않는 경우, OS에는 값이 계속 남아있게 되고
    child는 Zombie 프로세스가 됨
- 만약 wait() 호출이 계속 이뤄지지 않으면 Zombie의 수는 증가
  - 이를 방지하기 위해
    제일 첫번째 실행되는 프로세스인 init 프로세스가
    주기적으로 wait() 호출하여 Zombie 프로세스를 제거
