# Lsmtrace

LSM은 Linux Security Module로, 리눅스 커널에서 제공하는 보안 Framework로 커널 수준에서 보안 정책을 적용하는 데 사용된다. (LSM은 리눅스 커널 2.6 버전 이후로 기본 커널에 통합되었다.)

Lsmtrace는 eBPF 프로그램과 사용자 공간 프로그램 모두 C로 작성되어 있고, lsm 훅에서 eBPF 프로그램을 통해 추적한다.

Lsmtrace를 사용하려면
> BPF_SYSCALL
>
> BPF_LSM
>
> DEBUG_INFO
>
> DEBUG_INFO_BTF

위의 내용이 활성화 되어 있어야 한다.

<br></br>

# Run

```
$ sudo ./lsmtrace /usr/bin/ls -a /home  

Attaching hooks, don`t rush..

-> HOOK_CALL: -> cred_getsecid( const struct cred *c, u32 *secid )
-> HOOK_CALL: -> file_permission( struct file *file, int mask )
     file,f_mode = 32797
     file,f_path.dentry,d_flags = 64
     file,f_path.dentry,d_name.name = ls
     file,f_path.dentry,d_inode,i_ino = 3670696
...
```

<br></br>

# etc

lsm hook eBPF 프로그램 테스트 관련해, [deepfence/ebpfguard](https://github.com/deepfence/ebpfguard)도 lsm hook을 이용한다.
> deepfence/ebpfguard는 Rust로 작성된 eBPF 프로그램이다.
