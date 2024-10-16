#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10       // 저장할 최대 라인 수
#define MAX_LENGTH 100     // 한 줄의 최대 길이

char savedText[MAX_LINES][MAX_LENGTH];
int totalLines = 0;

void readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Do not open File: %s\n", fileName);
        exit(1);
    }

    totalLines = 0;
    while (fgets(savedText[totalLines], MAX_LENGTH, file)) {
        savedText[totalLines][strcspn(savedText[totalLines], "\n")] = '\0';
        totalLines++;
        if (totalLines >= MAX_LINES) break;
    }
    fclose(file);
    printf("File read success\n");
    printf("You can choose 1 ~ %d Line\n", totalLines);
}

// 한 줄을 출력하는 함수
void printLine(int line) {
    if (line >= 1 && line <= totalLines) {
        printf("%s\n", savedText[line - 1]);
    } else {
        printf("invalid line number.\n");
    }
}

// 줄 범위 출력 함수
void printRange(int start, int end) {
    for (int i = start; i <= end && i <= totalLines; i++) {
        printLine(i);
    }
}

void printList(int lines[], int count) {
    for (int i = 0; i < count; i++) {
        printLine(lines[i]);
    }
}

void printAll() {
    for (int i = 1; i <= totalLines; i++) {
        printLine(i);
    }
}

void handleInput(char *input) {
    if (strcmp(input, "*") == 0) {
        printAll();
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        printRange(start, end);
    } else if (strchr(input, ',') != NULL) {
        int lines[MAX_LINES], count = 0;
        char *token = strtok(input, ",");
        while (token != NULL) {
            lines[count++] = atoi(token);
            token = strtok(NULL, ",");
        }
        printList(lines, count);
    } else {
        int line = atoi(input);
        printLine(line);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("How to use: %s <FileName>\n", argv[0]);
        return 1;
    }

    char *fileName = argv[1];
    char input[50];

    readFile(fileName);

    printf("Pls 'Enter' the line to select: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    handleInput(input);

    return 0;
}

