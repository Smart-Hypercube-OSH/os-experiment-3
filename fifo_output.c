#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tools.h"

static const int BUF_SIZE = 16;

int main(int argc, char *argv[]) {
    if (argc < 2)
        error("Need the name of fifo\n");
    if (mkfifo(argv[1], 0777) != 0)
        error("Cannot create fifo\n");
    int fd;
    if ((fd = open(argv[1], O_WRONLY)) == -1)
        unlink(argv[1]), error("Cannot open fifo\n");
    char buf[BUF_SIZE];
    ssize_t l;
    while (l = read(STDIN_FILENO, buf, BUF_SIZE))
        write(fd, buf, l);
    unlink(argv[1]);
    return 0;
}
