# eBPF-firewall

eBPF를 활용한 간단한 방화벽으로, eBPF 프로그램이 root Cgroup에 연결되어 패킷이 허용되는지 여부를 제어하는 데 사용된다.

<br></br>


## Build (Ubuntu 기준)

```
$ sudo apt-get install -y clang llvm golang make
```

또한 cgroup2 파일 시스템이 마운트되어 있어야 한다.
/sys/fs/cgroup/unified 에서 찾고, 없다면
```
$ sudo mkdir /mnt/cgroup2
$ sudo mount -t cgroup2 none /mnt/cgroup2
```

그 후, ebpf-fw.go 파일을 이용해 경로를 바꿔준다.



## Run

eBPF 프로그램 load :
```
$ sudo ./ebpf-fw load
```

ebpf 프로그램 unload :
```
$ sudo ./ebpf-fw unload
```

특정 IP를 1.2.3.4 라고 했을 때, block the IP :
```
$ sudo ./ebpf-fw block 1.2.3.4
```

unblock the IP :
```
$ sudo ./ebpf-fw unblock 1.2.3.4
```


