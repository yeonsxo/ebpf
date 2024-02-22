# elastic-eBPF

elastic/ebpf 에는 File, Process, Network 관련해 추적하는 eBPF 프로그램들이 있다.

eBPF 프로그램과 사용자 공간 프로그램 모두 C로 작성되어 있다.

<br></br>

## Run

<img src="../../.picture/elastic-man.PNG" />

<br></br>

몇 가지 출력값을 살펴보자.

```
$ sudo ./EventsTrace --net-conn-attempt
```
<img src="../../.picture/elastic--net-conn-attempt-출력화면.PNG" />

<br></br>

```
$ sudo ./EventsTrace --process-exec
```
<img src="../../.picture/elastic--process-exec-출력화면.PNG" />

<br></br>

```
$ sudo ./EventsTrace --file-rename
```
<img src="../../.picture/elastic-file-rename-출력화면.PNG" />
