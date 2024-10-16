#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

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
}

void printReversed() {
    for (int i = totalLines - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("How to use: %s <FileName>\n", argv[0]);
        return 1;
    }

    char *fileName = argv[1];

    readFile(fileName);

    printReversed();

    return 0;
}

