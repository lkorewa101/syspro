#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    char str[1024];
    char *command1_args[10], *command2_args[10];
    int fd[2];

    if (argc == 1) {
        printf("[shell]");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';
    } else {
        strcpy(str, argv[1]);
        for (int i = 2; i < argc; i++) {
            strcat(str, " ");
            strcat(str, argv[i]);
        }
    }

    char *command1 = strtok(str, "|");
    char *command2 = strtok(NULL, "|");

    int i = 0;
    command1_args[i] = strtok(command1, " ");
    while (command1_args[i] != NULL) {
        i++;
        command1_args[i] = strtok(NULL, " ");
    }

    i = 0;
    command2_args[i] = strtok(command2, " ");
    while (command2_args[i] != NULL) {
        i++;
        command2_args[i] = strtok(NULL, " ");
    }

    pipe(fd);

    if (fork() == 0) {
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        execvp(command1_args[0], command1_args);
        perror("pipe");
        exit(1);
    } else {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        execvp(command2_args[0], command2_args);
        perror("pipe");
        exit(1);
    }
}
