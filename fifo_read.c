#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tools.h"

static const int BUF_SIZE = 16;

int main(int argc, char *argv[]) {
    if (argc < 2)
        error("Need the name of fifo\n");
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        error("Cannot open fifo\n");
    char buf[BUF_SIZE];
    ssize_t l;
    while (l = read(fd, buf, BUF_SIZE))
        write(STDOUT_FILENO, buf, l);
    return 0;
}
