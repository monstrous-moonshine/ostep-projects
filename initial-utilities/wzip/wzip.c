#include <stdio.h>
#include <stdlib.h>

void zip(FILE *fp, int *pcount, int *plast) {
    int c, count = *pcount, last = *plast;
    while ((c = fgetc(fp)) != EOF) {
        if (c == last)
            count++;
        else if (last >= 0) {
            fwrite(&count, 4, 1, stdout);
            fputc(last, stdout);
            last = c;
            count = 1;
        } else {
            last = c;
            count = 1;
        }
    }
    *pcount = count;
    *plast = last;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    int count = 0, last = -1;
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        zip(fp, &count, &last);
        fclose(fp);
    }
    if (last >= 0) {
        fwrite(&count, 4, 1, stdout);
        fputc(last, stdout);
    }
}
