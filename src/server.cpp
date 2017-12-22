#include <stdio.h>
#include <errno.h>	// errno
#include <string.h>	// strerror
#include <stdlib.h>	// malloc free
#include <netinet/in.h>	// IPPROTO_IP
#include <sys/socket.h>	// AF_INET, SOCK_STREAM, IPPROTO_IP, sock
#include <sys/epoll.h>

#include "server.h"
#include "listener.h"
#include "utils.h"

int main(int argc, char *argv[])
{
	server_context *p_ctx = NULL;
	p_ctx = (server_context *)malloc(sizeof(server_context));
	if (!p_ctx)
	{
		printf("malloc failed");
	}

	serverInit(p_ctx);
	serverRun(p_ctx);
	serverExit(p_ctx);

exit:
	if (p_ctx)
	{
		free(p_ctx);
		p_ctx = NULL;
	}

	return RET_OK;
}

int serverInit(server_context *ctx)
{
    class service_base *sock_test = NULL;

	if (!ctx)
	{
		return RET_ERR;
	}

	ctx->listener = new listener(MAX_LISTEN_FD);

    // sock test
	sock_test = new class service_base(INADDR_ANY, 5012);
	ctx->listener->add_service(sock_test);
    PMD("ADD sock test\n");

	return RET_OK;
}

int serverRun(server_context *srv_ctx)
{
	return RET_OK;
}

int serverExit(server_context *srv_ctx)
{
	return RET_OK;
}
