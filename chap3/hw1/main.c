#include <stdio.h>
#include "copy.h"
#include <string.h>

#define MAXSTRINGS 5

char lines[MAXSTRINGS][MAXLINE];
int lengths[MAXSTRINGS];

int main() {
	char line[MAXLINE];
	int count = 0;

	while(count < MAXSTRINGS) {
		gets(line);
		int len = strlen(line);
		if(len > 0) {
			copy(line, lines[count]);
			lengths[count] = len;
			count++;
		}
	}

	for(int i = 0; i < count - 1; i++) {
		for(int j = 0; j < count - i - 1; j++) {
			if(lengths[j] < lengths[j + 1]) {
				int tempLen = lengths[j];
				lengths[j] = lengths[j + 1];
				lengths[j + 1] = tempLen;

				char tempStr[MAXLINE];
				copy(lines[j], tempStr);
				copy(lines[j + 1], lines[j]);
				copy(tempStr, lines[j + 1]);
			}
		}
	}

	for(int i = 0; i < count; i++) {
		printf("%s\n", lines[i]);
	}

	return 0;
}
