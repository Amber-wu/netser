#ifndef NETSER_SERVER_H
#define NETSER_SERVER_H

#include "listener.h"

typedef struct server_context_s
{
	int epoll_fd;
	int fd;
	long ip;
	uint16_t port;
	class listener *listener;
} server_context;

#define MAX_LISTEN_FD 1024

int serverInit(server_context *srv_ctx);
int serverRun(server_context *srv_ctx);
int serverExit(server_context *srv_ctx);
#endif // NETER_SERVER_H
