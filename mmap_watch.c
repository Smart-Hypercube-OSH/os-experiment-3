#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "tools.h"

int main(int argc, char *argv[]) {
    if (argc < 2)
        error("Need the name of file\n");
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        error("Cannot open file\n");
    char *p = mmap(NULL, 1, PROT_READ, MAP_SHARED, fd, 0);
    char c;
    while (*p != c) {
        c = *p;
        sleep(2);
    }
    puts("Service is down");
    return 0;
}
