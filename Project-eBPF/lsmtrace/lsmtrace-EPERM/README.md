lumontec/lsmtrace eBPF 프로그램에서 EPERM return test를 하기 위해 원래 코드에서 수정한 코드이다.



특정 디렉토리를 rmdir(remove directory) 명령으로 지우려 할 때, permission denied가 뜰 수 있게 lsmtrace.bpf.c 코드를 수정했다.
