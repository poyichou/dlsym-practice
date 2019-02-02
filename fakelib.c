#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

static void *(*real_malloc)(size_t) = NULL;

int load_real_malloc() {
	real_malloc = dlsym(RTLD_NEXT, "malloc");
	if (!real_malloc) {
		perror(NULL);
		return 1;
	}
	return 0;
}

void *malloc(size_t request_size) {
	write(1, "ha! you used my malloc\n", strlen("ha! you used my malloc\n"));
	if(load_real_malloc() != 0) {
		return NULL;
	}
	return real_malloc(request_size);
}
