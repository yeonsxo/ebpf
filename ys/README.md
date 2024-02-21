간단한 eBPF 프로그램을 작성했다. C를 이용했다.


# Filesystem Monitor
<img src="../.picture/ys-open-close-출력화면.png"/>



# Process Monitor
<img src="../.picture/ys-execve-출력화면.PNG"/>



## 두 프로그램 실행 후 확인

```
$ sudo bpftool prog list
```

<img src="../.picture/ys-bpftool-prog-list-출력화면.png"/>
