# Chap 7 Deadlock

# Definition of Deadlock

### System Model

- resources는 유한함
    - types: CPU cycles, files, I/O devices, locks
    - 각 type마다 several instances를 가짐
        - 같은 type이면 결과는 동일 (ex. 모든 printer는 어쨌든 print를 수행)
- Process는 사용 전, request를 하고, 사용 후 release해야 함
    - e.g. open() & close(), malloc() & free(), wait() & signal()

### Deadlocked

- set 안의 모든 processes가 set 안의 또 다른 process에 의해 발생되는 event를 기다리는 있는 상황

---

# Deadlock Conditions (발생 조건)

### Mutual exclusion

- 적어도 하나의 resource는 nonsharable mode에 할당되어 있어야 함

### Hold and wait

- process는 적어도 하나의 resource를 할당하고 있어야 하고, 다른 processes에 잡혀있는 다른 resource를 waiting 해야 함

### No preemption

- resources는 자발적으로만 release 가능

### Circular wait

- P0 → P1의 resource wait, P1 → P2의 resource wait, P3 → ...
- Hold and wait가 circle 생성하게 되면 이와 같은 형태

---

# Resource Allocation Graph

### Directed graph

### Vertices

- P = { P1, P2, ... , Pn } → Process
- R = { R1, R2, ... , Rm } → Resource

### Edges

- Request edge: Pi → Rj
- Assignment edge: Rj → Pi

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled.png](https://user-images.githubusercontent.com/33208303/137094525-4433e978-5a92-4c65-88f9-cc66a59a870e.png)

---

# Deadlock

### cycle → deadlock may exist ⇒ 가능성이 있는 것, 무조건 X

### No cycle → No deadlock

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%201.png](https://user-images.githubusercontent.com/33208303/137094471-631c3f79-2a05-48a6-9330-03d495d54d5d.png)

- Cycle이 존재 → Deadlock은 아님

---

# Not a Deadlock

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%202.png]([Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%202.png](https://user-images.githubusercontent.com/33208303/137094506-87913ed3-3fb2-4c4e-a127-e5b9bca3d5c2.png))

- Cycle은 존재하지만 deadlock이 아닌 경우

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%203.png](https://user-images.githubusercontent.com/33208303/137094509-3028fce8-429d-4394-b265-9b0e255d6e97.png)

- Deadlock이 존재하는 경우

---

# Handling Deadlocks

### strategies

- deadlock을 prevent or avoid하기 위해 protocol 사용
    - Deadlock prevention
    - Deadlock avoidance: 추가 info가 필요
- system이 deadlock enter를 허용, detect & recover it
- Ignore & hope that it never happens → most popular

---

# Deadlock Prevention

### Deadlock 발생이 가능하도록 하는 4가지 필요조건 존재
(하나라도 방지하면 Deadlock 발생 X)

### Mutual Exclusion → Multiple process가 resource를 share하도록 하면 방지가능

- make resource sharable (ex. read-only files → 많은 수의 process가 reading)
- 하지만 resource를 sharable하게 만드는 것이 어려움

### Hold and wait → Mutual Exclusion보다는 easy

- Force process to request all resources before execution
    - Low resource utilization이 문제
- Allow process to request resource only when it has none
    - starvation이 문제 (→ gain → release → regain → release → 반복)

### No preemption

- process가 resource를 hold하고 있고, 할당받을 수 없는 resource를 request하면 해당 process가 가지고 있는 모든 resource를 preempted (released)
- 어떤 process가 다른 추가적인 resources를 기다리고 있는 process에 할당되어 있는 resource를 요청하면, preempt it
- resource가 preemptible한 경우만 가능

### Circular Wait

- 모든 resources의 순서를 정하고, process가 순서에 맞게 resource를 request하도록 함

---

# Deadlock Avoidance

### key approach

- how resources are to be requested에 대한 추가정보를 요구
- For each request, decide if the request should wait or not
    - ex. process P requests printer and, then tape drive.
    process Q requests tape drive and, then printer
    - 이와는 다르게, Deadlock prevention은 deadlock의 4가지 조건 중 1개를 충족시키지 않으려 함

### 정보의 양과 type에 따라 다양한 알고리즘

- Simplest algorithm: max # of resource of each type

### Safe state

- system이 각 process에 deadlock을 피하면서 resources 할당 가능
    - 모든 request를 만족할 수 있는 safe sequence <P1, P2, P3, ... , Pn>이 존재하는 경우만 가능

### Unsafe state ≠ deadlock

- deadlocked state로 이어질 수도 있다.

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%204.png](https://user-images.githubusercontent.com/33208303/137094510-4f367502-deb9-4c69-9e6f-915d76e51a2b.png)

- resource allocation이 매번 변함

---

# Safe State Example

### 12 instances of a resource type

### 3 processes: P0, P1, P2

### Available: 3

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%205.png](https://user-images.githubusercontent.com/33208303/137094513-6583e5bf-818e-413d-ad9c-54699f53edfc.png)

- <P1, P0, P2> satisfies the request
    - order exist ⇒ safe state

---

# Unsafe State Example

### Available: 2

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%206.png](https://user-images.githubusercontent.com/33208303/137094516-0e691541-f1d2-481d-9c78-c5876530d529.png)

### After P1 is finished, the Available resource is 4

- P0, P2 중 어느 하나의 still needs를 충족시키지 못함

### Key idea of deadlock avoidance algorithm

- beginning에서는 safe state에 존재
- process가 resource request하면, system은 곧바로 resource allocation을 할지 말지 결정
- allocation leaves the system in a safe state인 경우에만 할당

---

# Resource-Allocation-Graph Algorithm 
(Cycle 생성 여부 파악)

### Claim edge

- Pi → Rj == Pi may request resource Rj in the future

### Pi가 Rj를 request하면, Claim edge → request edge로 바뀜

### Rj가 release하면, request edge → Claim edge로 바뀜

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%207.png](https://user-images.githubusercontent.com/33208303/137094518-c723dae2-0de3-4730-bbe3-aa3fc18bc16e.png)

- cycle 감지로 인해 R2 → P2를 **not allow**

### Deadlock avoidance를 위함

---

# Banker's Algorithm

### Resource-allocation-graph algorithm은 multi-resource problem에는 적용되지 않는다.

- **Cycle이 존재하더라도 multiple instance를 가진다면, deadlock이 무조건 발생하는 것이 아니기 때문**

## Banker's Algorithm 
→ Deadlock avoidance를 위해 assignment order를 check

### Algorithm sketch

- 새 process가 enter, 각 resource type의 instances의 max #을 명시해야 함
- request 생성 시, 요청된 allocation을 safe state에 있는 system에 put할지 결정
    - 할당하거나, wait하거나

### Data Structures

- Available: vector, number of available resource instances for each type
- Max: matrix, max demand of each process → additional info
- Allocation: matrix, currently allocated resource
- Need: matrix, remaining resource need
    - **Need[i][j] = Max[i][j] - Allocation[i][j]**

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%208.png](https://user-images.githubusercontent.com/33208303/137094521-2fa1967f-12d2-4dba-a14e-95089dda604c.png)

### Notation

- X, Y: vector of length n
- X ≤ Y == X의 모든 요소가 상대되는 Y의 각 요소보다 작거나 같음

# Safety Algorithm: Check if it is safe or not
(assign이 가능한지 check)

### Work: vector of length m → resource 수

### Finish: vector of length n → process 수

1. 초기, work = available, Finish[i] False for all i
2. Finish[i] == False && Need(i) ≤ Work 인 i를 find
(이러한 i가 존재하지 않는다면 4단계로 이동)
3. Work = Work + Allocation(i) → Pi는 gone ⇒ resource return
Finish[i] = true → Pi is finish
2단계로 이동 → 다른 process 찾기 위해
4. Finish[i] == true for all i, system is in a safe state

### Resource-Request Algorithm

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%209.png](https://user-images.githubusercontent.com/33208303/137094523-07248ee1-327b-416f-baaa-8e9c6179b20d.png)

- Request(i): request vector for process Pi
(Request(i)[j]=k: process Pi가 Rj의 k instance를 요청)
1. Request(i) ≤ Need(i), 2단계로 이동, 그렇지 않으면 error
2. Request(i) ≤ Available, 3단계로 이동, 그렇지 않으면 Pi는 must wait
(Request가 너무 큰 경우, process는 wait해야 함)
3. Pretend to have this state
Available = Available - Request
Allocation(i) = Allocation(i) + Request(i)
Need(i) = Need(i) - Request(i)
→ state가 safe하면 allocate resource, 그렇지 않으면 restore the state

---

# Example of Banker's Algorithm

### 5 Processes, 3 Resource types

![Chap%207%20Deadlock%206b057d198acc4d369b187c791ba02199/Untitled%2010.png](https://user-images.githubusercontent.com/33208303/137094524-65371eb5-3a2f-42ce-999b-c01943cbd85a.png)

- Allocation이 Available에 더해지는 이유:
safe sequence를 찾는 중이기 때문에 Available을 가지고 충족 가능한 process를 find
이때 P1이 가능 → P1 다 처리해주고 다시 할당해준 것을 받아옴