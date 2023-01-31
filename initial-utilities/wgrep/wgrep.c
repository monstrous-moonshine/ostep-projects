#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(const char *needle, FILE *haystack) {
    for (;;) {
        char *line = NULL;
        size_t n = 0;
        ssize_t nr = getline(&line, &n, haystack);
        if (nr < 0) {
            free(line);
            break;
        }
        if (strstr(line, needle))
            fputs(line, stdout);
        free(line);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    if (argc < 3) {
        grep(argv[1], stdin);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (!fp) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            grep(argv[1], fp);
            fclose(fp);
        }
    }
}
