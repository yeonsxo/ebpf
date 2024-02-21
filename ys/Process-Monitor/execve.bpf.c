#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>


struct data_t {
	int pid;
   	int uid;
   	char path[50];
   	char command[16];
   	char message[12];
};

char message_execve[12] = "Execve!";

struct {
	__uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
   	__uint(key_size, sizeof(u32));
    	__uint(value_size, sizeof(u32));
} output_execve SEC(".maps");

SEC("ksyscall/execve")
int BPF_KPROBE_SYSCALL(sys_execve, const char *filename) {

	struct data_t data = {};
	
	data.pid = bpf_get_current_pid_tgid() >> 32;
	data.uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
	
	bpf_probe_read_user_str(&data.path, sizeof(data.path), filename);
	
	bpf_get_current_comm(&data.command, sizeof(data.command));
	
	bpf_probe_read_kernel_str(&data.message, sizeof(data.message), message_execve);
		
	bpf_perf_event_output(ctx, &output_execve, BPF_F_CURRENT_CPU, &data, sizeof(data));

	return 0;

}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
