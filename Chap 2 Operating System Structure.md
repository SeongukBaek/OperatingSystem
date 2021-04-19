# `Chap 2 Operating System Structure`

# OS Services → for users, for efficient operation

- OS는 프로그램의 수행을 위한 환경 제공, 프로그램과 프로그램의 User에게 특정 Service를 제공 ⇒ interface를 통해

![Untitled](https://user-images.githubusercontent.com/33208303/115228712-12821200-a14d-11eb-95da-5aac09d482a7.png)

- OS에서 제공하는 Services 다양하고, App이 OS의 Service를 이용하기 위해서는 System call을 거쳐야만 가능

# OS Services for User Support

### User interface

- CLI(Command-Line Interface): 리눅스 개발환경, cmd → GUI보다 빠르고 강력
- GUI(Graphic-User Interface)
- batch interface: 명령어들의 sequence를 실행

### Program Execution

- 메모리에 load, run and end execution

### I/O operations

- device가 PC에 연결되도록 allow

### File-system manipulation (I/O operation의 일종)

- 프로그램이 직접적으로 접근하는 것 X, OS를 거쳐서 이때 System call이 필요

### Communications (= Networking) → 프로그램 간 또는 Computer 간

- MSG를 전달하는 방식
  - 직접 전달하는 방식인 msg passing → Connection이 필요
  - 공유된 memory를 이용하여 전달하는 방식인 shared memory → Connection이 필요 X, sharing을 위해서 System call이 반드시 필요, msg 전달에 있어 delay 발생

### Error Detection

- HW-Level의 error와 SW-Level의 error 존재
  - memory error, Power failure, parity, connection failure, ...
  - bit flip
    - Bit 반전, 프로그램 수행 중, 데이터의 bit가 원치않게 flip될 수 있음
  - 감지가 어려운 error: silent error
    - memory leak: 어떤 프로그램이 memory를 계속 조금씩 조금씩 차지 ⇒ 나중에는 메모리가 남지 않게 됨.
      - 이때, 종료한 후 다시 실행하면 해결되지만 종료할 수 없는 서버의 경우는 문제

# OS Services for Efficient Operation → User에게 보여지지 않음

### Resource Allocation: resource 할당 해결

### Resource Accounting

- 어떤 프로세스가 resource를 얼마나 사용하는지 추적
  - 너무 많이 사용하는 프로세스에서 resource를 분배, 관리

### Protection and Security

- Multi user 환경에서 여러 프로그램들이 resource에 접근 → 이에 대한 Control이 필요
- 서로 다른 프로세스에 대한 간섭, 방해를 막아야 함 → Isolation이 해결책

⇒ "A system is as strong as its weakest link"

아무리 보안성이 좋아도 하나의 약한 부분으로 인해 약해진다 → balanced security의 중요성

# System Calls → library화 되어있음 (package화)

## System call : OS kernel이 제공하는 서비스에 Application이 접근하기 위해 사용하는 interface

### file copy의 예 ⇒ 많은 system call이 필요

![Untitled 1](https://user-images.githubusercontent.com/33208303/115228698-0eee8b00-a14d-11eb-9cd3-6b8f4d3abaf4.png)

1. copy를 위해서 OS는 목적 파일 이름과 원본 파일 이름을 요구
2. 파일이 없거나, 파일에 대한 권한이 없는 경우, error 발생하고 그렇지 않으면 copy할 준비
3. read와 write가 반복적 수행 → copy 프로그램이 수행
4. 완료 시, 두 파일을 close하고 완료 msg를 return

⇒ OS가 모든 일을 수행하고, User는 App를 이용하여 OS에 request

### Simple task에도 system call은 사용됨

### 프로그래머들은 API (=set of functions)를 통해 간접적으로 system call 호출

- Windows API, POSIX API, Java API
- Java API는 다른 API와는 다르게 상위 계층에 존재

  JAVA API → libc → system call 관계

![Untitled 2](https://user-images.githubusercontent.com/33208303/115228700-101fb800-a14d-11eb-9fe2-37fe1eaf85b4.png)

- 하나의 libc function이 하나 이상의 system call을 호출할 수도 있고,
- 하나의 system call이 하나 이상의 libc function으로부터 호출될 수도 있다.
- 모든 libc functions이 system call을 호출하는 것은 아님
- Why use APIs rather than System Calls directly?
  - 인자나 buffering 문제 해결이 어렵기 때문에 직접적으로 호출하지 않음
  - Portablity문제(code를 다른 환경(system call setup이 다른 = different mapping)에서 compile가능 = portable)
  - libc system call을 사용하기 위해 필요한 인자를 채워주는 역할

# System Call Interface

### Set of library functions that links to the system calls

![Untitled 3](https://user-images.githubusercontent.com/33208303/115228702-10b84e80-a14d-11eb-91a4-c4a83d4ec363.png)

- user application에서 libc 호출 → system call interface를 통해 kernel mode로 접근 → OS에 정의된 system call을 실행하고 return되는 int값을 가지고 다시 user mode로 switch → user application에 값 return

```c
int main() {
	...
	...
	f1();
	f2();
	--> regular function -> 함수 선언이 프로그램 내에 존재.
}

int f1() {
	...
	...
	open();
--> system call -> 함수 선언이 kernel space, 즉 OS에 존재 => CPU가 처리방법을 define
}
```

- regular function의 경우
  - 실행 위치만 옮겨서 해당 function을 수행
- System call의 경우

  - user mode → kernel mode로 switch한 후, 해당 요청 처리하고 다시 mode switch하고 return value

  ⇒ mode switching이 시간을 소모

![Untitled 4](https://user-images.githubusercontent.com/33208303/115228704-10b84e80-a14d-11eb-9ea7-5451b992a99f.png)

- eax ← system call #
- ebx ← fd
- ecx ← flag
- edx ← count
- 해당 레지스터 값을 채운 뒤 system call 호출 ⇒ libc function이 수행

# System Call Types

### Process Control

- fork, exec, exit, ...

### File manipulation

- create, open, close, read, write, lseek

### Device manipulation

- open, close, read, write, ioctl

### Information maintenance

- time, date, pid

### Communications

- open, close, connect, accept, read, write, send, recv, pipe, ...

### Protection

- Chmod, umask, chown, ...

⇒ open, close, read, write → 같은 object로 취급하여 모두 사용 가능 (리눅스는 모두 file로 취급)

# System Call Types: Process Control

- program file → execute → process (state를 가짐 ⇒ control이 가능)

### Error handling

- 종료 → memory dump를 생성 → msg 출력 → 다음 명령어 수행

### Loading and executing another Program

- 새로운 프로세스가 종료된 후 프로그램 흐름을 어디로 return 해야 할 지
- 동시에 실행할 지 않을지

# System Call Types: Communications ⇒ IPC

### Message Passing(Synchronous)

- Connection이 가장 먼저 open되어야 함 → 서로 준비되어야 함
- Connection 생성에도 system call이 필요이 필요

### Shared-Memory model(Asynchronous)

- memory에 msg를 저장, msg를 pick-up하는 형태 → 의사소통에 delay가 발생
- Connection이 필요 X
- Sharing을 위한 system call이 무조건 필요, shared memory 지역에서의 integrity of data를 조심

# OS Design and Implementation

### Design goal

- User goals : 쉽고 신뢰성 있고, 빨라야 함
- System goals : 개발의 용이, 유지 보수의 용이, ... ⇒ OS가 모두 만족하기 어려움

⇒ 막연한 요구사항과 명확하지 못한 해결책

### Guideline: Mechanism and Policy

- 메커니즘과 정책을 분리
  - 메커니즘 : 어떤 일을 어떻게 할 것인가를 결정하는 일
  - 정책 : 무엇을 할 것인가를 결정하는 일
  - 분리하는 이유
    - 정책은 장소가 바뀌거나 시간의 흐름에 따라 변경될 수 있는데, 정책의 변경이 메커니즘의 변경을 요구하는 경우 그렇지 않은 경우보다 바람직하지 못함

# OS Implementation

- assembly 언어로 구현 → 오류 발생 ↑, 어려움, port 어려움
- 고수준의 언어로 구현 (C, ...)
  - 장점
    - 구현 시간이 빠르다
    - 간결하고 이해와 디버깅이 쉽다
    - 컴파일러의 발전이 코드 생성을 향상시킬 것
  - 단점
    - 성능: 항상 차선의 코드 생성
    - 고수준의 언어로 쓰인 small critical code가 나중에는 다른 최적의 코드로 대체

# Operating System Structure

### Monolithic structure vs. componentized, modularied approach

- monolithic structure

  - 간단한 동작
  - 하나의 큰 조각, 서로 의존 ⇒ 하나를 변경하거나 대체하기 어려운 문제

  ⇒ 확장성이 좋지 않다

  ![Untitled 5](https://user-images.githubusercontent.com/33208303/115228706-1150e500-a14d-11eb-811d-3a9a0be7018d.png)

  - kernel에 여러 기능들이 합쳐져서 존재 (tightly coupled)

# OS Structure: Layered Approach

### Layered approach

![Untitled 6](https://user-images.githubusercontent.com/33208303/115228708-11e97b80-a14d-11eb-8c49-9ec9b6778302.png)

- Layer 0: HW, Layer M: user interface
- 각 Layer는 오직 상위 또는 하위 1개의 계층과만 소통 가능
- Layer M은 Layer M-1의 operation을 유발 (request)
- Layer M-1은 Layer M에게 요청받은 서비스 제공 (response)
- 장점
  - 간단한 구조 ⇒ 디버그의 용이
  - 층이 분리되어 있으므로 Layer가 대체되어도 interface는 변경 X
    - Layer 1 → Layer 1`로 변경, Layer 2가 Layer 1에 요구한 요청에 대한 reponse가 틀린 경우, Layer 1만 Debug하면 완료
- 단점
  - Layer를 정의하는 것 자체가 어려움 (functionality 사이의 충돌)
  - Layer를 오가는 것이 많은 overhead를 발생시킴
    - function call로 인한 계층 이동 → mode change가 포함될 수 있음
  - Layer 수의 증가 ⇒ 실행 시간의 증가

# Microkernels → 그저 approach 중 하나

### idea

- 중요한 기능만 kernel에 remain
- 나머지는 user-level에 위치 → kernel의 크기 감소 ⇒ mode switch를 줄임

### 장점

- OS kernel의 확정성 증가
- kernel의 크기가 작아지므로 port가 용이
- 안전하고 신뢰성 증가 (작은 게 더 안전, smaller attack surface)

### 단점

- 성능 저하

  - message passing 방식으로 인한 overhead가 발생

  ![Untitled 7](https://user-images.githubusercontent.com/33208303/115228709-12821200-a14d-11eb-8ccc-c4a3127a78e2.png)

  - App의 Request를 받아서 user model에 있는 function으로 redirect, 이때 msg 전달
