# Cilium

cilium 에서 제공하는 eBPF 프로그램의 예제에는,

- Kprobe : 임의의 커널 함수의 진입 또는 종료에 eBPF 프로그램을 연결한다.
> -> bpf2go를 사용한 Kprobe 예제

- Kprobepin : Kprobe 예제에서 고정된 맵을 재사용한다.

- Kprobe_percpu : BPF_MAP_TYPE_PERCPU_ARRAY 맵을 사용한다.

- ringbuffer : BPF_MAP_TYPE_RINGBUF 맵을 사용한다.

- Uprobe : 임의의 사용자 공간 이진 함수의 진입 또는 종료에 eBPF 프로그램을 연결한다.

- uretprobe : bpf2go를 사용한 uretprobe 예제

- Tracepoint : 미리 정의된 Kernel Tracepoint에 eBPF 프로그램을 연결한다.

- tracepoint_in_c : bpf2go를 사용한 tracepoint 예제

- Cgroup : 컨트롤 그룹(cgroups)에 eBPF 프로그램을 연결한다.

- Fentry : 커널 함수의 진입 지점에 eBPF 프로그램을 연결한다. Fentry는 Kprobe와 유사하지만 성능과 사용 편의성이 높다. (Fentry는 커널 version 5.5 이상에서 사용 가능)

- tcp_connect : 나가는 IPv4 TCP 연결을 추적한다.

- XDP : 네트워크 인터페이스에 eBPF 프로그램을 연결하여 들어오는 패킷을 처리한다.

#### bpf2go

eBPF 프로그램을 load, compile, debugging 할 수 있게 해주는 Go 라이브러리 이다.
> C 언어로 작성된 eBPF 프로그램을 eBPF bytecode로 컴파일하고 이후에 eBPF를 포함하는 Go 파일을 생성한다.

## Run

```
$ cd ebpf/examples/
$ go run -exec sudo [./kprobe, ./uretprobe, ./ringbuffer, ...]
```
