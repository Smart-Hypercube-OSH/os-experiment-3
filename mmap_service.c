#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include "tools.h"

int main(int argc, char *argv[]) {
    if (argc < 2)
        error("Need the name of file\n");
    int fd;
    if ((fd = open(argv[1], O_RDWR | O_CREAT)) == -1)
        error("Cannot open file\n");
    char *p = mmap(NULL, 1, PROT_WRITE, MAP_SHARED, fd, 0);
    if (p) {
        printf("%d\n", errno);
        error("Cannot mmap\n");
    }
    char c = 0;
    while (1) {
        *p = c++;
        sleep(1);
    }
    return 0;
}
