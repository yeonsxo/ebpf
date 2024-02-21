#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>


struct data_open {
   int uid;
   char path[50];
   char command[16];
   char message[12];
};

struct data_close {
   int uid;
   char command[16];
   char message[12];
};

char message_open[12] = "File Open!";
char message_close[12] = "File Close!";
char target_directory[] = "/home/shinys";
char tmp_path[256] = {0, };

struct {
    __uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
    __uint(key_size, sizeof(u32));
    __uint(value_size, sizeof(u32));
} output_open SEC(".maps");

struct {
    __uint(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
    __uint(key_size, sizeof(u32));
    __uint(value_size, sizeof(u32));
} output_close SEC(".maps");


SEC("ksyscall/openat")
int BPF_KPROBE_SYSCALL(file_open, int dfd, const char *pathname) {

	struct data_open data = {};
	int i = 0;
    int nCompareVal = 1;

	data.uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;

    bpf_probe_read_user_str(&tmp_path, sizeof(tmp_path), pathname);

    for (i = 0; i < sizeof(target_directory); i++)
        {
            if (tmp_path[i] != target_directory[i])
               {
                       nCompareVal = 0;
                       break;
               }
        }
	
	if (nCompareVal == 1) {
		bpf_probe_read_user_str(&data.path, sizeof(data.path), pathname);
	
		bpf_get_current_comm(&data.command, sizeof(data.command));
	
		bpf_probe_read_kernel_str(&data.message, sizeof(data.message), message_open);
		
		bpf_perf_event_output(ctx, &output_open, BPF_F_CURRENT_CPU, &data, sizeof(data));   
	}
	
	else {return 0;}

	return 0;

}

SEC("ksyscall/close")
int BPF_KPROBE_SYSCALL(file_close, int fd) {

	struct data_close data = {};

	data.uid = bpf_get_current_uid_gid() & 0xFFFFFFFF;
	
	bpf_get_current_comm(&data.command, sizeof(data.command));
	
	bpf_probe_read_kernel_str(&data.message, sizeof(data.message), message_close);
		
	bpf_perf_event_output(ctx, &output_close, BPF_F_CURRENT_CPU, &data, sizeof(data));

	return 0;

}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
