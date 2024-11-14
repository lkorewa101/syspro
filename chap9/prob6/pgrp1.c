#include <stdio.h>
#include <unistd.h>

main() {
	int pid, gid;
	printf("PAREN: PID = %d GID = %d\n", getpid(), getpgrp());
	pid = fork();
	if (pid == 0) {
		printf("CHILD: PID = %d GID = %d\n", getpid(), getpgrp());
	}
}
