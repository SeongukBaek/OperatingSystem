# Chap 4 `Threads`

# Thread

### What is thread?

- execution의 가장 작은 단위
- thread별로 각자의 stack, registers and PC를 가진다
  - 모든 threads는 서로 다른 code와 function을 실행 → different execution state

![Untitled](https://user-images.githubusercontent.com/33208303/115229443-02b6fd80-a14e-11eb-8ae3-40cb9e1d064c.png)

- stack → function, return value, address, ...

# Why use thread?

### Higher parallelism으로 성능 증가

- execution을 parallel하게 동작
  - one task - one process → task 증가 - process 증가 ⇒ time 많이 사용
- thread = light-weight process
  - 프로세스를 생성하는 것보다 thread를 생성하는 데 overhead가 덜 발생
  - 프로세스 : fork() → memory copy, exec() → memory reset & reload ⇒ time-consuming
  - thread : pthread_create() → clone() system call 호출 ⇒ memory copy X ⇒ faster
- resource를 효율적으로 사용
  - process creation : resource-intensive ⇒ heavy amount of resource
- Data의 공유가 쉬움
  - 프로세스의 경우, OS의 도움이 필요한 IPC를 사용해야 공유가 가능
  - 하지만 thread는 data의 공유에 있어 time control이 문제가 되기도 함 (Synchronization problem), race condition이 발생할 수 있음
- benefits
  - responsiveness(very quick), resource sharing, economy, scalability(얼마나 많은 user에게 서비스 가능?)

# Multicore Programming

### thread가 많아도 core 수가 적다면, thread간 switching이 필요

### core 수와 성능의 증가량은 완벽하게 비례하지 않음 (성능의 증가량이 점점 감소)

# Concurrency vs. Parallelism

### Parallelism ⇒ timing

- 한 시점에 두 개가 동시에 running

### Concurrency ⇒ timing X

- task가 progress를 생성, loop를 돌면서 tasks 수행

⇒ **Concurrent 하면 Parallel X
Parallel 하면 Concurrent O**

### Concurrent → sequential

![Untitled 1](https://user-images.githubusercontent.com/33208303/115229419-fd59b300-a14d-11eb-9321-90475dc93747.png)

### Parallel

![Untitled 2](https://user-images.githubusercontent.com/33208303/115229422-fe8ae000-a14d-11eb-9168-605b57a770e8.png)

- T1, T3 → Concurrent
- 2 cores ↔ highest degree of parallelism

### Hyper-threading

- OS에게 2 CPU가 있다는 착각을 주는 것
- 1개의 추가적인 fake CPU

![Untitled 3](https://user-images.githubusercontent.com/33208303/115229423-fe8ae000-a14d-11eb-9489-e9d503549907.png)

- 특정 상황에서만 성능 향상을 보여주지, 항상 성능의 향상을 보여주는 것 X

# New Challenges from Multicore

### Identifying tasks

- 어떤 part를 parallel하게 수행할 것인지를 식별하는 어려움

### Balance

- 각 core에 할당된 task가 균등한지 → task의 분배 문제

### Data splitting

- data의 크기가 같아도 해당 data의 value에 따라 처리속도가 달라지는 문제 → data의 분배 문제

### Data dependency

- 하나의 task가 다른 task로부터의 data에 의존할 수 있어 생기는 문제 → **Degree of Parallelism 결정**
- 피보나치의 경우
  - 1 ~ 50 → core 1, 51 ~ 100 → core 2
  - core 1의 수행이 끝나야 core 2의 수행이 가능 ⇒ parallel 불가능

# Types of Parallelism

### Data parallelism → 데이터를 분할하여 같은 task 수행

- ex. sum
  single core : sum[0] ~ sum[N - 1] → sequential run
  dual core : sum[0] ~ sum[N/2 - 1], sum[N/2] ~ sum[N - 1]를 parallel하게 수행
  ⇒ degree of parallelism : 2 (dual)

### Task parallelism → 여러 task 병렬 수행

- ex. Avg, sum
  core 1: averaging 수행
  core 2: sum all elements 수행

⇒ Hybrid technique 이 필요

# Multithreading Models

- PCB → Process, TCB → Thread

### User(-level) thread vs. Kernel(-level) thread

- User thread
  - TCB와 operations이 user level library에 의해 관리
  - OS kernel은 user threads가 얼마나 동작되는지 모름
  - OS의 도움 X → OS의 scheduling X, 사용자의 함수, user-memory-area
- Kernel thread : System call을 이용해서만 가능
  - OS kernel이 thread가 어느 프로세스에서 동작하는지 확인 가능
  - True schedulable entity → kernel이 인지 O → kernel이 직접 scheduling 가능

⇒ 누가 Thread table을 관리하느냐가 주된 차이

![Untitled 4](https://user-images.githubusercontent.com/33208303/115229424-ff237680-a14d-11eb-892d-59873fa86b71.png)

![Untitled 5](https://user-images.githubusercontent.com/33208303/115229426-ff237680-a14d-11eb-9bc4-aae063588fd8.png)

![Untitled 6](https://user-images.githubusercontent.com/33208303/115229429-ffbc0d00-a14d-11eb-911c-3c4c278752c4.png)

- 서로 상대적인 장단점
- kernel이 각 thread에 CPU를 어떻게 분배할지는 policy에 의존
- User Thread에서, Kernel은 user thread의 존재를 모르고 하나의 process로만 인식하기에
  해당 process가 scheduling되지 않으면, 모든 threads는 block됨

### Multiplexing User Threads → 여러 User threads 중 1개를 CPU로 전달

![Untitled 7](https://user-images.githubusercontent.com/33208303/115229431-0054a380-a14e-11eb-9bdb-a7d49aaa280d.png)

- N-to-one model
  - user thread가 CPU로 접근 X → 이로 인한 장점과 단점
- 1-1 model → most popular model
  - kernel의 도움으로 user thread 생성
- Many-to-many model (N ≥ M)
  - 가장 최적의 threads 사용
  - user thread - kernel thread의 mapping은 OS가 관리하며, 계속 변함 → Complexity

# Thread Library

### Thread library

- thread 생성과 관리를 위한 API (Set of functions : create, destroy, sync, ...)

### Implement

- In user space (user thread)
  - no kernel support ⇒ no system call
  - user space에 모든 code와 data structure (TCB?) 존재
  - API 호출이 system call 생성 X
- kernel-level library (kernel thread)
  - API 호출이 system call invoke

# Existing Thread libraries

### main thread libraries

- POSIX pthread → none windows 환경에서 유일하게 사용 가능한 library
- Windows thread API
- Java thread API

### implement

- pthread : kernel-level 사용
- windows thread : kernel-level 사용

⇒ invoke system call

- java thread

  - higher-level library → 다른 lib보다 상위
  - Java는 OS 위에 Virtual Machine을 두고 동작하기 때문에,
    리눅스 환경에서 java API는 pthread API를 호출하게 됨
  - Java thread는 pthread or Windows thread lib를 호출

    - ex. create_thread function call (java)
      → pthread_create call
      → clone() system call

    ![Untitled 8](https://user-images.githubusercontent.com/33208303/115229434-00ed3a00-a14e-11eb-9f47-3fe002bdf209.png)

  # Pthread Overview

  ### Pthread API - more than 100 subroutines (APIs)

  - Thread management : create, exit, join, detach, ...
  - Mutexes : lock, unlock
  - Condition variables : init, signal, wait, destory, ...

  ![Untitled 9](https://user-images.githubusercontent.com/33208303/115229436-0185d080-a14e-11eb-8d04-b8a4f776ef95.png)

  - 위 상황에서 thread 2개가 생성되고 나면, 총 thread는 3개
  - pthread_exit()로 thread를 종료하는 부분에서,
    프로세스의 종료 → memory 지우고, ... 할일이 많음
    thread의 종료 → destroy → kernel에서 delete ⇒ 프로세스에 비해 간단

  # Pthread example code

  ![Untitled 10](https://user-images.githubusercontent.com/33208303/115229438-0185d080-a14e-11eb-8d1a-086d46a3970c.png)

  - pthread_create 함수로 새로운 thread를 생성하고, 해당 thread에서는 전역변수인 sum을 이용하여 동작
  - pthread_join으로 thread의 종료를 기다림 → sum의 최신화

  # Java thread

  ![Untitled 11](https://user-images.githubusercontent.com/33208303/115229439-021e6700-a14e-11eb-9314-f496930699dc.png)

  ### Java에서 thread 생성하는 방법 2가지

  - Thread class를 상속하는 class 생성
  - Runnable intreface를 implement

# Thread Pool

### model of execution using thread

- new request comes in
  → create new thread, handle the request
  → destroy the thread when done

### 위와 같은 접근의 문제

- thread의 수가 많아지는 경우, create와 destroy 에 대한 overhead 발생
  - 물론 프로세스의 fork 보다는 pthread_create가 더 빠름

### Thread Pool

- Computer 또는 Program의 시작부분에서 고정된 수의 threads를 생성
  → new request가 들어오면, thread pool에서 free or not working인 thread를 선택, 요청 처리
  → 처리가 종료되면, 해당 thread를 다시 thread pool로 return - 이때, 만약 thread pool에 available한 thread가 없는 경우 wait
- request가 많은 경우 delayed execution of requests가 문제

![Untitled 12](https://user-images.githubusercontent.com/33208303/115229441-021e6700-a14e-11eb-9ff4-0ae4e9d68de0.png)

- free from Server Crash

# Threading Issues

### fork() & exec()

- one thread가 fork() 호출 시
  - 모든 threads를 복제
  - fork() 호출한 thread만 복제
- fork() 후 exec()가 바로 호출되면, 왜 모든 threads를 복제하는가
  - fork() 후 exec()가 바로 호출하는 경우, fork()를 호출한 thread만 내용 복제

### Signal Handling → IPC

- timer, ctrl-c, div-by-zero → signal 발생
- signal handler가 존재
- multi-threaded process에서, 어느 thread에 signal을 전달할 것인가?
  - signal을 적용할 thread에
  - 모든 thread에
  - 특정 thrad에
  - signal handling thread에

### Thread Cancellation (ex. thread가 더 이상 필요없는 경우/kill하는 경우)

- Asynchronous Cancellation → Communication 없이 갑자기 kill
- Deferred Cancellation → Clean up actions 할 기회를 주고 kill
- 문제가 야기되는 부분
  - data update를 하는 thread의 경우 또는 resource를 가진 thread의 경우, Asynchronous Cancellation이 문제가 될 수 있음
- default → Deferred Cancellation (safe)
  - Thread는 'cancellation point'에서 cancel됨
  - phtread_testcancel()이 'cancellation point' 생성
