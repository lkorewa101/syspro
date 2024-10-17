#include <stdio.h>

int main(int argc, char *argv[]) {
    char c;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL) {
        fprintf(stderr, "File %s open error\n", argv[1]);
        return 2;
    }

    fp2 = fopen(argv[2], "a+");
    if (fp2 == NULL) {
        fprintf(stderr, "File %s open error\n", argv[2]);
        fclose(fp1);
        return 3;
    }

    fseek(fp2, -1, SEEK_END);
    if (fgetc(fp2) == '\n') {
        fseek(fp2, 0, SEEK_END); 
    } else {
        fseek(fp2, 0, SEEK_END); 
    }

    while ((c = fgetc(fp1)) != EOF) {
        fputc(c, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}

