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
	if (fork() == 0) {
		execl("/bin/date", "date", NULL);
		fprintf(stderr, "Second try Fail");
		exit(2);
	}

	if (fork() == 0) {
		execl("/bin/ls", "ls", "-l", NULL);
		fprintf(stderr, "Third try Fail");
		exit(3);
	}
	printf("Parent Process end\n");
}
