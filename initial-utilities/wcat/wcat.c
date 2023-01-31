#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFLEN 4096

int main(int argc, char *argv[]) {
    char buf[BUFLEN];
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        for (;;) {
            ssize_t nr = read(fd, buf, BUFLEN);
            if (nr < 0) {
                perror("read");
                exit(1);
            } else if (nr == 0) {
                break;
            }
            ssize_t nw = write(1, buf, nr);
            if (nw < 0) {
                perror("write");
                exit(1);
            }
            // ignore partial writes
        }
        close(fd);
    }
}
