#include <unistd.h>
#include <sys/types.h>
#include "tools.h"

static const int BUF_SIZE = 16;

int main() {
    int fds[2];
    if (pipe(fds) != 0)
        error("Cannot create pipes\n");
    pid_t pid;
    if ((pid = fork()) == -1)
        error("Connot fork\n");
    int fd_cls, fd_src, fd_dst;
    if (pid) {
        fd_cls = fds[1];
        fd_src = fds[0];
        fd_dst = STDOUT_FILENO;
    }
    else {
        fd_cls = fds[0];
        fd_src = STDIN_FILENO;
        fd_dst = fds[1];
    }
    close(fd_cls);
    char buf[BUF_SIZE];
    ssize_t l;
    while (l = read(fd_src, buf, BUF_SIZE))
        write(fd_dst, buf, l);
    return 0;
}
