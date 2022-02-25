# OS란 무엇인가?
: HW를 관리하는 일종의 SW(Program), Computer의 User와 HW 사이에서 동작하는 Program
- user ↔ OS ↔ HW

### OS의 목표
- user program을 실행하고, user problem을 쉽게 해결해줌
- 컴퓨터 시스템을 더 편리하게 해줌 → user interface와 관련
- Computer HW를 낭비 없이 사용하기 위함 → resources에 대한 관리

# Computer System의 관점

![Untitled](https://user-images.githubusercontent.com/33208303/115228172-6809ef00-a14c-11eb-99bc-1980c4e05d1f.png)

- HW, OS, App, Users
- Application이 직접적으로 HW에 접근하지 못하고, OS에 요청한다.
- 해당 요청을 받은 OS가 HW에 접근하여 요청 처리 후 return

# OS의 View Points

### User Views 
: 어떤 종류의 사용자인가에 따라 나뉘게 된다.
- Home PC user → Personal Thing 요구
  - 용이성을 추구
  - Resource utilization이 문제되지 X
- Mainframe, mini computer, workstation
  - 많은 프로그램 수행 목적
  - 1개의 program이 다른 program에 영향을 주면 X
  - Resource manage가 필요, easy of use 신경 X
- Mobile devices
  - 수행에 있어 빠르고 쉬워야 함
  - usability, user interface 고려

### System Views
- Resource allocator
  - Resource: 컴퓨터가 사용하는 모든 자원
    ⇒ 자원 충돌 문제의 해결이 필요
- Control Program
  - error와 computer의 부적절한 사용 방지
    ⇒ not safe → reject / safe → run

# OS의 정의 
→ 명확한 정의 X
- 다양한 HW와 목적이 존재 (kernel + system programs)

## Computer System Organization

![Untitled 1](https://user-images.githubusercontent.com/33208303/115228284-866fea80-a14c-11eb-90fe-6fba7cd35064.png)

- system bus: communication channel, 모든 요소들이 이를 이용하여 소통
- CPU와 device controller는 병렬적으로 동작을 수행

# Need for OS

### 한 PC에서 여러 User가 Program 실행 시

- OS가 실행 순서, Resource 관리 등을 수행
  - ex. isolation을 통한 다른 Program의 data에 영향 X

### Programmer가 Program 구현 시

- 서로 다른 HW에서도 동작할 수 있도록,
- 다양한 disk와 file system에서도 file 관리가 가능하도록,
- Network protocol을 사용하여 다른 PC와 의사소통할 수 있도록 함

### Owner가 바라는 것

- CPU와 Memory의 낭비 X
- 이미 동작 중인 Computer에 아무 일도 없는 듯이 새로운 disk add
- 유, 무선 네트워크 간의 전환

## Computer Operations

### Start-up

- Bootstrap program(Helper) : Computer 전원 on → 제일 먼저 실행됨
  - ROM or EEPROM에 저장되어있음 (firmware: 명령어들의 집합)
  - CPU register와 device controllers, Memory를 초기화
  - OS kernel을 load, 동작시킴
- System daemons
  - kernel이 돌아가는 entire time동안 계속 동작하는 프로그램
  - init은 첫번째로 동작하는 Process, 이는 많은 daemons를 실행시킴
  - init 또한 일종의 daemon이지만, init의 종료는 곧 OS의 종료를 의미