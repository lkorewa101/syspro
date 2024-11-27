#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARG 100
#define MAXLINE 1024

int main() {
    char line[MAXLINE];
    char *args[MAXARG];
    char *token;
    char *saveptr;
    pid_t pid;
    int background;

    while (1) {
        printf("Pls input cmd : ");
        fflush(stdout);

        if (fgets(line, MAXLINE, stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        background = 0;
        int i = 0;

        token = strtok_r(line, " ", &saveptr);
        while (token != NULL) {
            args[i++] = token;
            token = strtok_r(NULL, " ", &saveptr);
        }
        args[i] = NULL;

        if (i == 0) continue;

        if (strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            if (execvp(args[0], args) < 0) {
                perror("exec failed");
                exit(1);
            }
        } else {
            printf("[%d] Parent process start\n", getpid());
            if (!background) {
                waitpid(pid, NULL, 0);
                printf("SUCCESS\n");
            }
        }

        if (pid != 0) {
            if (waitpid(pid, NULL, 0) == -1) {
                printf("Parent process end\n");
            }
        }
    }

	printf("Exit\n");
    return 0;
}
