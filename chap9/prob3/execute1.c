#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("Parent Process start\n");
	if (fork() == 0) {
		execl("/bin/echo", "echo", "hello", NULL);
		fprintf(stderr, "First try fail");
		exit(1);
	}
	printf("Parent Process end\n");
}
