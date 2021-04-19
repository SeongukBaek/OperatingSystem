# Chap 5 Process Scheduling

# Process Schduling

### CPU scheduling : Switching the CPU among Processes ⇒ Which one come next?

### 실제 scheduling 대상은 thread (in Linux)

### Process Scheduling이 필요한 이유?

- **CPU Utilization의 최대화**를 위함
- Fairness, interactivity, ...

# CPU - I/O Burst Cycle

### Process execution

- CPU execution과 I/O wait의 alternating cycle ⇒ 서로 상반되는 관계 X
  - CPU burst → I/O burst → CPU burst → I/O burst → 반복
  - burst : duration, Some time span

![Untitled](https://user-images.githubusercontent.com/33208303/115229648-40b42180-a14e-11eb-9ce9-a224db44976b.png)

### I/O : Input/Output → CPU 밖으로 나가는 모든 task

- ex. dist I/O (long time, long way), network I/O, mouse, keyboard

# CPU Burst duration

![Untitled 1](https://user-images.githubusercontent.com/33208303/115229629-3db93100-a14e-11eb-9e07-4fec7fc18a07.png)

- Program마다 다른 그래프
- Large number of short CPU bursts (초반부)
- Small number of long CPU bursts (후반부)

![Untitled 2](https://user-images.githubusercontent.com/33208303/115229635-3eea5e00-a14e-11eb-9aec-0e26df32cfe0.png)

# CPU Scheduler → When to do Scheduling

### CPU가 idle하게 되면, OS는 ready Q로부터 프로세스 1개를 select

- short-term scheduler = CPU scheduler

### When to make a scheduling decision

1. Process : running state → waiting state ⇒ ready Q → wait Q
   - I/O request(data가 필요한 경우) or an invocation of wait()로 인해 발생
2. Process : running state → ready state ⇒ CPU → ready Q
   - (timer) interrupt occurs
3. Process : waiting state → ready state ⇒ wait Q → ready Q
   - I/O 작업 완료
4. Process : terminate ⇒ CPU가 available → next process select

**⇒ 1, 4 → Scheduling decision이 반드시 필요**

# Preemptive vs. Nonpreemptive

### Nonpreemptive Scheduler

- 1번과 4번의 경우만 Scheduling

### 그 반대의 경우, 즉 모든 경우에 Scheduling ⇒ Preemptive Scheduler

### Can OS force the rescheduling of an actively running process?

- Yes : OS kernel can take away process ⇒ Preemptive (2, 3 경우)
- No : Nonpreemptive (1, 4 경우)

### Nonpreemptive Scheduling의 경우

- 프로세스가 스스로 종료되거나 CPU에서 해제되지 않는 이상 계속 동작

# Preemptive Scheduling

### Issues

- Potential cause of race condition
  - data update 중 preemption 발생 → 다른 프로세스가 받는 data에 문제
  - ex. P1이 running 중 lock으로 데이터 보호 → preemption으로 인해 lock된 채로 release
    → P2가 ready Q에 있다가 running 하려 하지만 P1의 lock이 unlock되지 않아 running 불가
- Complication to the kernel design
  - preemption during system call handling
    - kernel의 data structure에 문제
  - one option
    - 프로세스가 kernel mode에 있을때, release되지 않도록 함
    - 하지만 real-time computing의 경우,
      빨리 처리해야 하는 프로세스가 system call 사용한다면 preemption 불가
      ⇒ 문제 발생

# Dispatcher

### selected process에 CPU의 control을 전해주는 Component

- Responsibilities
  - Switching Context = Switching PCB (in kernel mode)
  - Switching to user mode
  - user program의 위치로 돌아와 동작 continue
- Dispatch latency ( ⇒ management overhead이므로 최대한 짧게)

  - stop one process & start another process 하는데 드는 time

  ![Untitled 3](https://user-images.githubusercontent.com/33208303/115229639-3f82f480-a14e-11eb-8edd-681c8fdf6a76.png)

  - 위 그림에서 Dispatch latency는 P1의 kernel mode에서 드는 시간
  - Restore state from PCB2하고 나서 PC에 실행할 명령어를 저장하게 된다
  - 그리고 P2가 Executing

# Scheduling Criteria (Metric)

### CPU utilization

- CPU의 사용률을 100%로 요구하지만,
  사실상 이는 불가능 (실제로는 30~40%) 하고
  100%에 근접하게 되면 다른 criteria를 해치게 됨

### Throughput

- 하나의 unit time에 처리하는 jobs의 수를 최대화

### Turnaround time

- 프로세스의 작업이 끝날 때까지 걸리는 시간 = start ~ end (throughput과 반비례)

### Waiting time

- ready Q에서 프로세스가 wait하는데 드는 시간의 합

### Response time

- 프로세스의 first response가 전해질 때까지의 시간
- 프로세스는 계속 동작 중인 상태
- task가 얼마나 걸리는 지는 신경쓰지 않고 첫 response만 생각

### Fairness

- 각 프로세스가 CPU를 공평하게 분배받는 것

⇒ Turnaround time, Waiting time, Response time은 minimize할수록 good

# Using the Scheduling Criteria

### Maximize

- CPU utilization, throughput, Fairness

### Minimize

- Turnaround time, Waiting time, Response time

### Optimize for → 어떤 Criteria인가에 따라 달라짐

- average
- minimum or maximum

### For interactive systems → 사용자의 입력을 받아야 하는 경우

- response time에 있어서 average를 최소화하는 것보다
  variance를 최소화하는 것이 good - ex. 사용자 입력을 받는 프로그램의 경우
  어떤 경우는 빠르게 받고, 어떤 경우는 느리게 받는 것보다
  전체적으로 차이가 없는 것이 낫다고 생각

# FCFS Scheduling

### First-Come, First-Served Scheduling algorithm

- 도착한 순서대로 Serve
- Nonpreemptive → 줄 서 있으면 그 순서가 바뀌지 않음
- Simple and easy to implement
  - 프로세스 → ready Q에 push → ready Q의 tail에 PCB가 link됨
  - 프로세스의 head가 CPU에 할당됨
- Downside : average waiting time 증가

![Untitled 4](https://user-images.githubusercontent.com/33208303/115229642-3f82f480-a14e-11eb-80bf-b6f6c036354a.png)

- P1으로 인해 P2와 P3의 waiting time이 증가하는 문제

# FCFS Scheduling : Reducing The Waiting Time

- P2, P3, P1의 순서로 왔을 경우

![Untitled 5](https://user-images.githubusercontent.com/33208303/115229643-401b8b00-a14e-11eb-8943-05011c060606.png)

- Average Waiting Time : (0 + 3 + 6)/3 = 3ms ⇒ 매우 감소
- FCFS에서는, average waiting time을 향상시킬 기회 존재
- **Convoy effect**가 발생할 수 있음

  - : 하나의 오래 걸리는 프로세스로 인해 전체적인 처리 시간이 매우 증가

  ![Untitled 6](https://user-images.githubusercontent.com/33208303/115229645-401b8b00-a14e-11eb-8c7d-1935bd885118.png)

  - P5는 한참 걸리고, P1~P4는 금방 finish
  - Grouping effect

# SJF : Shortest-Job-First Scheduling

### idea

- shortest-burst time job을 먼저 처리

![Untitled 7](https://user-images.githubusercontent.com/33208303/115229646-40b42180-a14e-11eb-9ff4-4c0225dda9a2.png)

- Average Waiting Time : (3 + 16 + 9 + 0)/4 = 7
- AWT for FCFS : (0 + 6 + 14 +21)/4 = 10

### SJF는 optimal minimum average waiting time을 가져옴

### 하지만 CPU burst time은 프로세스 running 전에 알기 매우 어려움
