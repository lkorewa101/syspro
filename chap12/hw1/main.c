#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char send_msg[50];
    char recv_msg[50];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);
        read(pipefd[0], recv_msg, sizeof(recv_msg));
        printf("Recv: [%d] %s\n", getpid(), recv_msg);
        close(pipefd[0]);
    } else {
        close(pipefd[0]);
        snprintf(send_msg, sizeof(send_msg), "Hello from PID %d", getpid());
        write(pipefd[1], send_msg, strlen(send_msg) + 1);
        printf("Send: [%d] %s\n", getpid(), send_msg);
        close(pipefd[1]);
    }

    return 0;
}
