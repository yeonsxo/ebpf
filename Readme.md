# eBPF란 ?
eBPF는 Extended Berkeley Packet Filters로, 패킷 필터인 BPF 프로그램이 확장된 것이다. BPF는 Unix계열 OS의 Kernel Level에서 Bytecode에 따라 동작하는 경량화된 VM이다. eBPF를 사용하면 프로그램이 커널 수준에서 발생하는 모든 것을 관찰하고 이벤트를 고속으로 처리할 수 있으므로 보안에 적절하게 사용된다.


기존 BPF와의 차이점은 eBPF 맵을 이용해 사용자 공간 app과 BPF 프로그램이 데이터를 공유할 수 있고, 더 많은 종류의 bpf helper function과 bpf() 시스템 호출을 활용하여 프로그램을 구성할 수 있으며, ebpf verifier가 추가되어 프로그램이 더 안전하게 실행될 수 있도록 보장한다.



![그림 1](./picture/그림1.png)

[그림 1]과 같이 eBPF 프로그램은 filesystem과 network에 적용되어 악성 코드의 실행을 막는 등의 보안 측면은 물론이고 분석, monitoring, 추적, redirection, debugging 등에서도 다양하게 활용될 수 있다.



![그림 2](./picture/그림2.png)

[그림 2]를 참고해보자. eBPF 프로그램은 C 또는 Rust를 이용해 소스 코드를 작성하게 되고(최근에는 go로도 작성되는 것 같다), LLVM 이나 Clang을 이용해 bytecode로 compile된다.

eBPF bytecode는 Kernel Level에서 동작하므로 system 전체에 영향을 줄 수 있는 위험한 상황을 방지하기 위해 Verifier로 이상이 없는지 검사를 진행한다. 그 후, JIT Compiler를 통해 native code로 변환되어 Kernel에서 동작한다.

## 구조

![그림 3](./picture/그림3.png)

eBPF 프로그램의 attachment에는 kprobes, tracepoints, raw tracepoint, fentry/fexit probes 등이 있다. 예를 들면, execve() system call 진입 지점에 부착된 kprobe, do_execve() kernel 함수에 부착된 Kprobe, execve() system call 진입 지점에 위치한 tracepoint 등에 eBPF 프로그램이 연결 된다.

여기서 Kprobe는 Kernel probe라는 기능으로, 커널 코드의 명령에 트랩을 설정하는 것이다.
debugging이나 성능 측정 목적으로 함수를 작성하여 Kprobes에 연결할 수 있는데([그림 3] 참고), 2015년부터 eBPF 프로그램을 Kprobes에 부착할 수 있는 기능이 추가되었다.

Kprobe는 일반적으로 함수 진입 지점에 사용하고, Kretprobes는 함수 종료 지점에 사용하며, 특정 오프셋이 있는 명령에도 사용할 수 있다. Kprobe보다 조금 더 커널 버전 간에 안정적인 tracepoint도 있는데, 이는 커널 코드 내에서 표시된 특정 위치를 나타낸다.

Fentry는 Kprobe와 같이 함수 진입 지점에 사용되고, Fexit은 Kretprobe와 같이 함수 종료 지점에 사용되지만 Fexit은 Kreprobe와 달리 함수의 입력 매개변수에 엑세스할 수 있어 함수의 끝에서 이벤트를 생성하려는 경우 유용하게 사용할 수 있다.

eBPF 프로그램은 Linux Security Module(LSM) API에도 연결된다. LSM은 원래 커널 모듈이 보안 정책을 시행하는 데 사용하도록 고안된 커널 내의 안정된 인터페이스인데, 이를 이용해 여러 면에서 추적 프로그램처럼 처리한다.



### 네트워킹에서의 eBPF
eBPF 프로그램에서의 반환 코드를 사용하여 커널에게 네트워크 패킷을 처리할 방법(평소처럼 처리, 삭제, redirection 등)을 알려준다. 또, eBPF프로그램이 네트워크 패킷, 소켓 구성 매개변수 등을 수정할 수 있도록 한다.

![그림 4](./picture/그림4.png)

[그림 4]를 참고해보면, eBPF 프로그램이 Kprobes에 부착할 수 있는 기능이 추가되며 동시에 커널 네트워킹 스택 내에 훅이 추가되어 eBPF 프로그램이 네트워킹 기능의 다양한 측면도 처리할 수 있게 되었다. XDP는 리눅스 커널에서 high-performance programmable packet processing을 가능케 하는 BPF 프레임워크를 제공한다. 이는 네트워크 드라이버가 패킷을 수신하는 순간(소프트웨어에서 가장 빠른 시점), BPF 프로그램을 실행한다.
