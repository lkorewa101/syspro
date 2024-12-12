#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void intHandler();

int main() {
	signal(SIGINT, intHandler);
	while (1) {
		sleep(1);
		printf("Process [1] Execution\n");
	}
}

void intHandler(int signo) {
	printf("Interrupt to child\n");
	printf("child Killed\n");
	printf("parent Killed\n");
	exit(0);
}

