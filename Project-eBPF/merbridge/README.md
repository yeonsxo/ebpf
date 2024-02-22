# merbridge

merbridge는 eBPF 프로그램을 통해 네트워킹에서의 연결을 리다이렉션 및 포워딩하여 envoy를 거쳤다가 

<img src="../../.picture/merbridge.png" />

eBPF 프로그램은 C로, 사용자 공간 프로그램은 go로 작성되어있다.

<br></br>

# build

현재 사용중이던 Ubuntu 22.04로 진행하니 아래와 같은 에러가 발생한다.

<img src="../../.picture/merbridge-libbpf-version-error.PNG" />

libbpf version이 맞지 않는 것으로 추정된다. merbridge github에서는 k 구성한 환경대로 Ubuntu 20.04에서 진행하였다.
