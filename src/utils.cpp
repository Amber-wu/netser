#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"

RET_T set_fd_blocking(int fd)
{
	int old_flags;

	if (-1 == (old_flags = fcntl(fd, F_GETFL, 0)))
	{
		PMD("get fd flags failed, %s(%d)\n", strerror(errno), errno);
		return RET_ERR;
	}

	if (-1 == fcntl(fd, F_SETFL, old_flags | ~O_NONBLOCK))
	{
		PMD("set fd flags failed, %s(%d)\n", strerror(errno), errno);
		return RET_ERR;
	}

	return RET_OK;
}

RET_T set_fd_nonblocking(int fd)
{
	int old_flags;

	if (-1 == (old_flags = fcntl(fd, F_GETFL, 0)))
	{
		PMD("get fd flags failed, %s(%d)\n", strerror(errno), errno);
		return RET_ERR;
	}

	if (-1 == fcntl(fd, F_SETFL, old_flags | O_NONBLOCK))
	{
		PMD("set fd flags failed, %s(%d)\n", strerror(errno), errno);
		return RET_ERR;
	}

	return RET_OK;
}
