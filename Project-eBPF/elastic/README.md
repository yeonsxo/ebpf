# elastic-eBPF

elastic/ebpf 에는 File, Process, Network 관련해 추적하는 eBPF 프로그램들이 있다.

<img src="../../.picture/elastic-man.PNG" />

몇 가지 출력값을 살펴보자.

```
$ sudo ./EventsTrace --net-conn-attempt
```
<img src="../../.picture/elastic--net-conn-attempt-출력화면.PNG" />



```
$ sudo ./EventsTrace --process-exec
```
<img src="../../.picture/elastic--process-exec-출력화면.PNG" />



```
$ sudo ./EventsTrace --file-rename
```
<img src="../../.picture/elastic-file-rename-출력화면.PNG" />
