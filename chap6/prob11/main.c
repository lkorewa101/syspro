#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int, int, int);

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int opt_i = 0, opt_p = 0, opt_Q = 0;

    int opt;
    while((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch(opt) {
            case 'i':
                opt_i = 1;
                break;
            case 'p':
                opt_p = 1;
                break;
            case 'Q':
                opt_Q = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-i] [-p] [-Q] [directory]\n", argv[0]);
                exit(1);
        }
    }

    if(optind == argc) {
        dir = ".";
    } else {
        dir = argv[optind];
    }

    if((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if(lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, d->d_name, &st, opt_i, opt_p, opt_Q);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int opt_i, int opt_p, int opt_Q) {
    if(opt_i) {
        printf("%ld ", st->st_ino);
    }
    printf("%5ld ", st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3ld ", st->st_nlink);
    printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld ", st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);

    if(opt_Q) {
        printf("\"%s\"", file);
    } else {
        printf("%s", file);
    }

    if(opt_p && S_ISDIR(st->st_mode)) {
        printf("/");
    }

    printf("\n");
}

char type(mode_t mode) {
    if(S_ISREG(mode))
        return('-');
    if(S_ISDIR(mode))
        return('d');
    if(S_ISCHR(mode))
        return('c');
    if(S_ISBLK(mode))
        return('b');
    if(S_ISLNK(mode))
        return('l');
    if(S_ISFIFO(mode))
        return('p');
    if(S_ISSOCK(mode))
        return('s');
    return('?');
}

char* perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    for(int i = 0; i < 3; i++) {
        if(mode & (S_IRUSR >> i * 3))
            perms[i * 3] = 'r';
        if(mode & (S_IWUSR >> i * 3))
            perms[i * 3 + 1] = 'w';
        if(mode & (S_IXUSR >> i * 3))
            perms[i * 3 + 2] = 'x';
    }
    return(perms);
}
