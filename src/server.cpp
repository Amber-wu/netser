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
	int ret = RET_OK;
	server_context *p_ctx = NULL;

	ret = serverInit(p_ctx);

	if (RET_OK == ret)
	{
		ret = serverRun(p_ctx);
	}

	if (RET_OK == ret)
	{
		ret = serverExit(p_ctx);
	}

	return ret;
}

int serverInit(server_context *ctx) {
	class service_base *sock_test = NULL;

	if (!ctx) {
		ctx = (server_context *)malloc(sizeof(server_context));
		if (!ctx) {
			PMD("malloc failed");
			goto malloc_failed;
		}
		memset(ctx, 0, sizeof(server_context));
	}

	ctx->listener = new listener(MAX_LISTEN_FD);
	if (!ctx->listener) {
		PMD("new listener failed\n");
		goto listener_create_failed;
	}

	sock_test = new service_base(INADDR_ANY, 5012);
	if (sock_test == NULL)
	{
		PMD("net service_base failed\n");
		goto service_sock_test_failed;
	}
	ctx->listener->add_service(sock_test);
    PMD("ADD sock test\n");

	return RET_OK;

service_sock_test_failed:
	delete ctx->listener;
	ctx->listener = NULL;

listener_create_failed:
	if (ctx)
	{
		free(ctx);
		ctx = NULL;
	}

malloc_failed:

	return RET_ERR;
}

int serverRun(server_context *srv_ctx)
{
	return RET_OK;
}

int serverExit(server_context *srv_ctx)
{

	return RET_OK;
}
