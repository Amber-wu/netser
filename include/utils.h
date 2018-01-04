#ifndef NETSER_UTILS_H
#define NETSER_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef int RET_T;

enum return_v {
	RET_OK = 0,
	RET_ERR = -1,
};

#define PMD(...) printf(__VA_ARGS__)

#define CLOSE_FD(fd) do {\
	if (fd >= 0) {\
		close(fd);\
		fd = -1;\
	}\
} while(0);

#define SAFE_FREE(ptr) do {\
    if (ptr)\
    {\
        free(ptr);\
		ptr = NULL;\
    }\
} while(0);

RET_T set_fd_blocking(int fd);
RET_T set_fd_nonblocking(int fd);

#endif // NETSER_UTILS_H
