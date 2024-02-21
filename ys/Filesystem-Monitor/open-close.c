#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <bpf/libbpf.h>
#include "open-close.skel.h"

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


static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args)
{
	if (level >= LIBBPF_DEBUG)
		return 0;

	return vfprintf(stderr, format, args);
}

void handle_event_open(void *ctx, int cpu, void *data, unsigned int data_sz)
{
	struct data_open *m = data;

	printf("%-6d %-50s %-16s %s\n", m->uid, m->path, m->command, m->message);
}

void handle_event_close(void *ctx, int cpu, void *data, unsigned int data_sz)
{
	struct data_close *m = data;

	printf("%-6d %-50s %-16s %s\n", m->uid, "", m->command, m->message);
}


void lost_event(void *ctx, int cpu, long long unsigned int data_sz)
{
	printf("lost event\n");
}

int main()
{
    struct open_close_bpf *skel;
    int err;
	struct perf_buffer *pb_open = NULL;
	struct perf_buffer *pb_close = NULL;

	libbpf_set_print(libbpf_print_fn);

	skel = open_close_bpf__open_and_load();
	if (!skel) {
		printf("Failed to open BPF object\n");
		return 1;
	}

	err = open_close_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "Failed to attach BPF skeleton: %d\n", err);
		open_close_bpf__destroy(skel);
        return 1;
	}

	pb_open = perf_buffer__new(bpf_map__fd(skel->maps.output_open), 8, handle_event_open, lost_event, NULL, NULL);
	pb_close = perf_buffer__new(bpf_map__fd(skel->maps.output_close), 8, handle_event_close, lost_event, NULL, NULL);

	if (!pb_open) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		open_close_bpf__destroy(skel);
        return 1;
	}

	if (!pb_close) {
		err = -1;
		fprintf(stderr, "Failed to create ring buffer\n");
		open_close_bpf__destroy(skel);
        return 1;
	}

	while (true) {
		err = perf_buffer__poll(pb_open, 100 /* timeout, ms */);

		// Ctrl-C gives -EINTR
		if (err == -EINTR) {
			err = 0;
			break;
		}

		if (err < 0) {
			printf("Error polling perf buffer: %d\n", err);
			break;
		}

		err = perf_buffer__poll(pb_close, 100);

		if (err == -EINTR) {
			err = 0;
			break;
		}

		if (err < 0) {
			printf("Error polling perf buffer: %d\n", err);
			break;
		}
	}

	perf_buffer__free(pb_open);
	perf_buffer__free(pb_close);
	open_close_bpf__destroy(skel);
	return -err;
}
