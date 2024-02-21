<img src="../.picture/learning-ebpf-cover.png" height=500 />

> Learning-eBPF는 eBPF를 자세하고 쉽게 이해하기 좋은 교재로, 저자는 Liz Rice이다. (published by O'Reilly)
>
> ###### 이 책의 저자는 Ubuntu 22.04, kernel version 5.15를 사용한다.
> 
> 
>   > 다른 배포판이나 커널 버전을 사용하는 경우 여러 패키지와 종속성 간의 호환성 문제를 해결해야 한다.
>   >
>   > &nbsp; &nbsp; ex) 이 예제에는 Clang-14를 사용. Clang-15 이상을 사용하고 있다면 BCC 버전 0.27.0 이상이 필요하다.




##### 위 교재를 참고하여 eBPF를 접했다. chapter별로 간략하게 소개를 하자면,

- Chapter1 : What Is eBPF, and Why Is It Important?

   eBPF가 무엇인지, 어떻게 구성되어 있는지와 eBPF의 발전, 특징들을 설명한다.

- Chapter2 : eBPF’s “Hello World”

   C언어와 python을 통해 eBPF 프로그램의 간단한 예제를 작성한다.
   ```python
   #!/usr/bin/python3  
   from bcc import BPF

   program = r"""
   int hello(void *ctx) {
       bpf_trace_printk("Hello World!");
       return 0;
   }
   """

   b = BPF(text=program)
   syscall = b.get_syscall_fnname("execve")
   b.attach_kprobe(event=syscall, fn_name="hello")

   b.trace_print()
   ```

- Chapter3 : Anatomy of an eBPF Program

   C언어로 작성되어 있는 XDP 예제를 통해 소스 코드가 어떻게 eBPF bytecode로 변환되는지 살펴본다.

- Chapter4 : The bpf() System Call

   eBPF를 사용할 때 system call 수준에서 무엇이 일어나는지 설명하기 위한 BCC framework를 이용한 예제들이 있다.

- Chapter5 : CO-RE, BTF, and Libbpf

   CO-RE, BTF에 대한 설명과 eBPF 프로그램을 로드하고 관리하기 위한 C 기반 라이브러리인 libbpf에 대한 설명과 libbpf를 기반으로 한 C 예제 코드들이 있다.

- Chapter6 : The eBPF Verifier

   eBPF 프로그램이 커널에서 안전하게 돌아가는지 확인하는 검증기가 잘 돌아가는지 예제 코드를 약간 수정하여 검증기 오류들을 확인해본다.

- Chapter7 : eBPF Program and Attachment Types

   eBPF의 다양한 attachment와 eBPF 프로그램의 예제들이 있다.

- Chapter8 : eBPF for Networking

   네트워크 스택의 다양한 지점에 부착되는 eBPF 프로그램 예제들이 있다. (XDP 프로그램, TC 서브시스템, Kubernetes Networking 등을 소개한다.)

- Chapter9 : eBPF for Security

   LSM(Linux Security Module) 훅 지점에 eBPF를 연결하는 등의 보안 측면에서의 eBPF 프로그램을 소개한다.

- Chapter10 : eBPF Programming

   다양한 언어들에 대한 라이브러리 등을 소개한다. (eBPF 프로그램은 C 기반으로만 작성되는 것 아니기 때문)

- Chapter11 : The Future Evolution of eBPF

   eBPF의 앞으로의 발전에 대해 소개한다.


##### Learning-eBPF는 다른 여러 프로젝트를 분석할 때의 핵심 참고 자료이다.
