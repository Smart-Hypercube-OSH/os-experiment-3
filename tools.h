#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>

void error(const char *msg) {
    fputs(msg, stderr);
    perror("most recent error");
    exit(EXIT_FAILURE);
}

#endif
