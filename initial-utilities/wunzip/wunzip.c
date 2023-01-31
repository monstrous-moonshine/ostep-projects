#include <stdio.h>
#include <stdlib.h>

void unzip(FILE *fp) {
    char buf[5];
    while (fread(buf, 1, 5, fp) == 5) {
        int n = *(int *)buf;
        for (int i = 0; i < n; i++) {
            fputc(buf[4], stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        unzip(fp);
        fclose(fp);
    }
}
