#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("usage: ./hack <exec file>\n");
		return 1;
	}
	char current[512];
	getcwd(current, 512);

	char preload[strlen("LD_PRELOAD=") + strlen(current) + strlen("/fakelib.so") + 1];
	snprintf(preload, sizeof(preload), "LD_PRELOAD=%s/fakelib.so", current);

	char *env[] = {preload, NULL};
	execvpe(argv[1], argv + 1, env);

	perror(argv[1]);
	return 1;
}
