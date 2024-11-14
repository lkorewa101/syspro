#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int pid, child, status;
	printf("[%d] Parent Process start \n", getpid());
	pid = fork();
	if(pid == 0) {
		printf("[%d] Child Process start \n", getpid());
		exit(1);
	}
	child = wait(&status);
	printf("[%d] Child Process %d end \n", getpid(), child);
	printf("\tend code 1 %d\n", status>>8);
}
