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
	write(1, "load malloc successfully\n", strlen("load malloc successfully\n"));
	return 0;
}

// only this symbol is visible to the users of this shared library.
__attribute__((__visibility__("default")))
void *malloc(size_t request_size) {
	write(1, "ha! you used my malloc\n", strlen("ha! you used my malloc\n"));
	if(load_real_malloc() != 0) {
		return NULL;
	}
	return real_malloc(request_size);
}
