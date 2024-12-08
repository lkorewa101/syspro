#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd1[2];
    int pipefd2[2];
    pid_t pid1, pid2;

    printf("parent process start\n");

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd1[0]);
        char input[BUFFER_SIZE];
        
        printf("input string: ");
        fgets(input, BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';
        
        write(pipefd1[1], input, strlen(input) + 1);
        close(pipefd1[1]);
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipefd1[1]);
        close(pipefd2[0]);

        char received[BUFFER_SIZE];
        read(pipefd1[0], received, BUFFER_SIZE);

        for (int i = 0; received[i]; i++) {
            received[i] = toupper(received[i]);
        }

        write(pipefd2[1], received, strlen(received) + 1);
        close(pipefd1[0]);
        close(pipefd2[1]);
        exit(0);
    }

    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[1]);

    char output[BUFFER_SIZE];
    read(pipefd2[0], output, BUFFER_SIZE);

    printf("%s\n", output);

    close(pipefd2[0]);
    
    wait(NULL);
    wait(NULL);

    return 0;
}

