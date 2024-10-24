#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 50

int main(int argc, char *argv[]) {
	FILE *fp;
	int c;
	int i = 1;
	char buffer[MAXLINE];

	if(argc != 2) {
		exit(1);
	}

	if((fp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error Open File\n");
		exit(2);
	}

	while(fgets(buffer, MAXLINE, fp) != NULL) {
		i++;
		printf("%s", buffer);
		if(i > 2) {
			exit(0);
		}
	}
}
