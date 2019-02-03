#include <stdlib.h>
int main() {
	int *ptr = malloc(10);
	free(ptr);
	return 0;
}
