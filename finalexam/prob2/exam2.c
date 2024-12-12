#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
	int pid, child1, child2;
	pid = fork();
	if(pid == 0) {
		printf("Hello\n");
		if(pid == 0) {
			printf("Hello\n");
			exit(1);
		}
		exit(1);
	}
	pid = fork();
	printf("Hello\n");
	return 0;
}

