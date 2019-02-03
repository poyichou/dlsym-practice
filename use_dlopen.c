#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
int main() {
	void (*func)();
	void *handle = dlopen("./fakelib.so", RTLD_LAZY);
	if (!handle) {
		perror("dlopen");
		exit(1);
	}

	func = dlsym(handle, "load_real_malloc");
	if(!func) {
		perror("dlsym");
		exit(1);
	}
	func();

	if(dlclose(handle) != 0) {
		perror("dlclose");
		exit(1);
	}
	return 0;
}
