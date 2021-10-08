# Chap 6 Synchronization

# Bounded Buffer Problem 
(Bounded: limited # of buffers)

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled.png](https://user-images.githubusercontent.com/33208303/136527500-a6259139-ec47-4a5b-8551-bc3753048eea.png)

---

# Race Condition on Shared Variable

### Counter(: shared value, 메모리 변수)의 초기값: 5

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%201.png](https://user-images.githubusercontent.com/33208303/136527294-2923f4d9-b01b-4999-b4a8-69755ef912f3.png)

- 위와 같은 각 3단계의 과정이 실제로는 여러 경우로 합쳐질 수 있음

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%202.png](https://user-images.githubusercontent.com/33208303/136527316-366db3f3-bd73-4fe0-9aa9-c90e06f3434c.png)

### Counter = 4 → incorrect value

- operation이 not atomic하기에 발생
    - not atomic → 즉, 중간에 다른 명령어가 끼어들 수 있음

### Race Condition

- 결과가 particular order of access에 의존
    - correct하거나 incorrect함 → **synchronization**이 필요함

---

# Synchronization is Needed

### Multi-threaded applicaiton

- threads는 process안에서 memory를 공유함 (stack은 공유하지 않음)
- shared variables에 대한 control이 없으면, 문제가 발생할 수도, 하지 않을 수도 있음
    - 문제: data corruption
    - 특히, Silent corruption
        - 초기에는 문제가 없어보이지만 시간이 지날 수록 문제화됨 → debugging의 어려움

### Kernel mode

- kernel data structure는 list of processes, list of open files, page table, ...을 update
    - 한번에 두 개 이상의 process로부터 수정되면 안됨
- Preemptive kernel vs. Nonpreemptive kernel
    - preemptive → force something to stop
    - nonpreemptive → wait for done
- Nonpreemptive kernel → no race condition
    - 이유는 중단하지 않기 때문, real time computing에서는 좋지 않음
- Preemptive kernel을 사용하는 이유
    - response time의 향상, data update에서의 collapse 발생 가능

### Multithreads가 sys_call사용 → control하지 않으면 kernel data structure가 collapse

---

# Critical-Section Problem

### Critical Section → important part, update or write at Shared variables

- 한 process가 들어와있다면, 다른 process는 enter불가

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%203.png](https://user-images.githubusercontent.com/33208303/136527323-4f29423d-f1de-4d5b-b33d-9bb64e6fce06.png)

- section의 code가 있을 수도, 없을 수도 있음 ⇒ general한 형식
- 한번 remainder section에 들어간 process는 계속 이 안에서만 execute

### CS 문제해결을 위한 solution의 3가지 조건 (모두 충족해야 좋은 Solution)

- Mutual exclusion
    - 한 시점의 CS에는 오직 1개의 process
    - Multiple processes가 CS에 enter 요구해도 1개만 가능, 나머지는 entry section에서 대기
- Progress
    - CS에 아무 process가 없고, P가 enter를 원하면, remainder section에 있지 않은 P가 selection process에 들어갈 수 있으며, selection은 곧바로 이루어져서 CS로 전달됨
- Bounded waiting
    - processes가 CS에 enter한 횟수는 bounded되어야 함
    - P1, P2, ... → [ CS ] enter요구
        - P1은 한번도 enter 못할 수도 있음
        → waiting의 횟수 제한 ⇒ ex. 10번 동안 waiting하면 CS로 전달

---

# Strict Alternation

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%204.png](https://user-images.githubusercontent.com/33208303/136527329-d3aa7290-68f8-451a-b2c4-261922576099.png)

### Process j가 remainder section에 갇히고,
Process i가 entry section에 갇힌 경우,
Process i가 continue될 수 없음

⇒ 다른 process의 상태에 의존

### Problem

- strict alternation
- 'progress' requirement 만족 X (다른 프로세스의 상태에 의존하기 때문)
    - mutual exclusion은 만족

⇒ 하나의 turn 변수로 해결 불가

---

# Peterson's Algorithm

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%205.png](https://user-images.githubusercontent.com/33208303/136527340-99df3723-78d2-45f0-9a7b-0b80f535df0e.png)

### Shared variables between Pi & Pj

- int turn; → 누가 CS에 enter할 차례인지
- boolean flag[2]; → Process가 CS에 enter할 준비가 되었는지

### Two process solution (2개에 한해서만 가능)

### SW-Only Solution

- bounded waiting도 해결 (Pi는 겨우 1번 waiting)

### 각각 turn, flag 중 하나만 사용하는 경우

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%206.png](https://user-images.githubusercontent.com/33208303/136527356-cb7b995a-73e0-487c-a753-e70cfaf922a6.png)

- Process 중 어느 하나도 CS에 도달할 수 없음 → solution X

---

# Correctness of Peterson's Algorithm

### Mutual exclusion → 만족

- Pi는 flag[j] == false or turn == i인 경우만 CS에 enter 가능
- 두 process가 동시에 CS에 있으려면
flag[i] == flag[j] == true & turn == i & turn == j이여야 함

### Progress → 만족

- Pi는 flag[j] == true & turn == j인 경우 stuck
    - Pj도 같은 위치라고 했을 때, selection은 즉시 발생

### Bounded Waiting → 만족

- Pj가 연속으로 CS enter 불가능

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%207.png](https://user-images.githubusercontent.com/33208303/136527371-d62850ec-75ab-4f9a-a0cb-834d47b9d99a.png)

---

# Synchronization HW Support 
(SW만 사용 → slow, HW도 사용 → fast)

### Single-processor의 CS problem 해결책

- timer interrupt를 제거 → P1이 CS에서 나오면 다시 set
    - Scheduling을 막을 수 있음
- Multiprocessor에서는 동작 X
    - 한 core에서 CS enter한 경우, 
    다른 모든 core에 이를 알리고, CS entering하는 것을 막기 위해 message passing
    ⇒ 성능에 영향을 미침

### HW instruction

- 'test_and_set(), compare_and_swap()' instructions allow (⇒ atomic operation)

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%208.png](https://user-images.githubusercontent.com/33208303/136527398-2526d402-acb3-4994-a510-43781007c63b.png)

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%209.png](https://user-images.githubusercontent.com/33208303/136527401-5b54d2b0-3563-4556-b7be-f5e79b97a50e.png)

---

# Using test_and_set() → instruction O, C Code X

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2010.png](https://user-images.githubusercontent.com/33208303/136528015-5e3ce4a5-eeb8-47d8-b118-0b5b25b721fa.png)

### Mutual-exclusion implementation

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2011.png](https://user-images.githubusercontent.com/33208303/136527413-cdca48b6-ed8a-47eb-bd9a-3fb33e39e5fb.png)

---

# Using compare_and_swap() 
→ test_and_set()과 동일효과

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2012.png](https://user-images.githubusercontent.com/33208303/136527421-5449565a-6e7d-429f-a8c0-03cbbcc1852f.png)

### Mutual-exclusion implementation

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2013.png](https://user-images.githubusercontent.com/33208303/136527431-9ba53671-2f61-4018-81a4-22e40a08d4c5.png)

---

# Bounded-waiting using test_and_set()

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2014.png](https://user-images.githubusercontent.com/33208303/136527435-20a09b5a-f023-4eac-89fa-ea0dcb447c90.png)

### Mutual exclusion만 만족

---

# Mutex Locks (Mutex: Mutual Exclusion)

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2015.png](https://user-images.githubusercontent.com/33208303/136527440-608eae27-cf06-4dbe-8771-09ef33d85c27.png)

### Busy waiting: other processes wait in a loop

- Spin lock
- wastes CPU cycles
⇒ running on CPU이지만 아무것도 하지않음 → CPU cycle의 낭비
- good for short lived locks (no context switch가 없기 때문) → lock ⇒ long time hell X

---

# Semaphores → Mutex보다 강력

### Semaphore S

- integer variable
- wait()와 signal()을 통해서만 접근 가능
    - wait() = P, signal() = V

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2016.png](https://user-images.githubusercontent.com/33208303/136527449-f13ea275-dbf9-44bc-b14e-5e0100b11cdd.png)

- wait()와 signal()은 atomic해야함

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2017.png](https://user-images.githubusercontent.com/33208303/136527453-4573428c-6291-4d70-afb2-e0ce6eb28173.png)

- Mutual exclusion만 만족
- initial V가 4
    - → CS에 enter가능한 process의 수 의미
        - 즉 CS에 공존할 수 있는 process의 수가 제한됨
        ⇒ **mutex보다 더 강력한 이유**
    - CS enter: s=3, s=2, ... s=0으로 감소

---

# Semaphore Usage

### Semaphore 2 types

- Counting semaphore: unrestricted value → 어떤 것도 가능
- binary semaphore: Only 0 & 1 → mutex locks와 비슷

⇒ semaphore가 mutex를 포함

### Counting semaphore

- finite number of resources를 제어하기 위해 사용 → process 수 control
    - 사용가능한 resource instances의 수로 초기화
    - resource 사용 → wait() 수행, resource release → signal() 수행
    - 0이 되면, 다른 모든 process는 wait
- Controlling the execution order (실행 순서 제어 가능) ⇒ flow control이 가능
    - synch = 0
    - P2는 P1이 signal(synch)를 호출한 후에만 (synch가 0 → 1) S2를 수행 가능

⇒ P2가 먼저 schedule 되어도, wait해야하고, P1이 실행되어야 wait에서 탈출

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2018.png](https://user-images.githubusercontent.com/33208303/136527460-2eb688aa-4f09-46d2-83be-732a44932bbf.png)

---

# Semaphore Implementation

### Semaphore는 busy waiting이 문제

### busy waiting을 피하기 위해 blocking 사용

- On wait(), process는 스스로 block
    - Semaphore의 waiting Queue에 process를 put → **spinlock 대신**
        - 그리고 Semaphore는 각각의 waiting Queue를 가짐
    - process를 wait state로 전환
    - CPU scheduler가 실행할 다른 process를 선택 → waiting Queue에 있는 process는 select X
- On signal()
    - process는 wakeup()에 의해 재시작됨
        - process는 wait state → ready state로 switch됨
        - process는 ready Queue에 put

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2019.png](https://user-images.githubusercontent.com/33208303/136527464-5ee0ceb6-d496-4d3a-86ca-d2db61beac84.png)

- busy waiting의 해결을 위함

### Semaphore 값은 negative될 수 있음

- decrement operation이 먼저 온 이유 ? 다른 위치에 오게 되면?

---

# Deadlock and starvation on semaphore

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2020.png](https://user-images.githubusercontent.com/33208303/136527473-d9f4c0d3-8dac-45e8-9f1d-4700a9301c75.png)

### P0, P1은 영원히 갇히게 됨 → Deadlock

### starvation (indefinite blocking)

- semaphore의 wait Queue에서 process wait → Aging이 해결

---

# Bounded-buffer Problem 
→ Multiple semaphore가 필요

### int n;
semaphore mutex = 1; → binary semaphore, CS를 보호를 하기 위함
semaphore empty = n;
semaphore full = 0;

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2021.png](https://user-images.githubusercontent.com/33208303/136527479-b5fd2771-2c2a-4c5d-88f9-2209c4054742.png)

---

# Reader-writer Problem (producer-consumer와 비슷)

### Reader는 writers가 data를 update하는 동안에만 read 가능

- 여러 명의 readers가 동시 read 가능
- writers와 readers는 동시에 data 접근 X (reader가 부정확한 data read할 가능성 존재)

### Writers는 shared data에 대한 독립적인 접근이 필요
→ data consistency가 지켜지지 않을 수 있기 때문

### Problem(strategy)

- the first reader_writer problem
    - writer가 waiting하고 있으면 reader는 다른 reader를 wait할 필요가 없음
        
        ⇒ **writer에게 starvation**, reader priority
        

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2022.png](https://user-images.githubusercontent.com/33208303/136527488-05efce37-a319-48ce-a38c-8d11d81baef3.png)

- the second reader_writer problem
    - writer가 waiting이면, 새로운 reader는 reading 시작 불가
        
        ⇒ writer가 계속 오면, **reader에게 starvation**, writer priority
        

---

# Reader-writer problem solution

### 1st problem의 solution

- semaphore rw_mutex = 1; → reader를 lock하기 위함
semaphore mutex = 1; → shared value인 read_count에 대한 lock을 위함
int read_count = 0;

### Reader의 경우

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2023.png](https://user-images.githubusercontent.com/33208303/136527489-77081800-9903-41bf-8ae7-e89e2470012e.png)

- read_count가 1인 경우에만 wait(rw_mutex) 수행
- 여러 reader가 CS로 enter한 경우, 마지막 reader가 signal(rw_mutex) 수행

### Writer의 경우

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2024.png](https://user-images.githubusercontent.com/33208303/136527493-363f5589-86da-4985-adff-529ab4f34fd9.png)

- 1 writer at a time

---

# Dining-Philosophers Problem

![Chap%206%20Synchronization%20e45f5bab452a4e4ca33acd8c79ec3d0a/Untitled%2025.png](https://user-images.githubusercontent.com/33208303/136527496-74b7f6a1-4bea-40aa-adbf-1f70b898e2bf.png)

### Resolving deadlock

- 4 philosophers인 경우
- both chopsticks이 가능한 경우
- Asymmetric pick-up
    - odd-numbered philosophers: left & right, even의 경우: right & left
    - No deadlock, only waiting time