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
	if (!p_ctx) {
		printf("malloc failed");
		goto err_exit;
	}
	memset(p_ctx, 0, sizeof(server_context));

	serverInit(p_ctx);
	serverRun(p_ctx);
	serverExit(p_ctx);

	return RET_OK;

err_exit:
	if (p_ctx)
	{
		free(p_ctx);
		p_ctx = NULL;
	}

	return RET_ERR;
}

int serverInit(server_context *ctx) {
	class service_base *sock_test = NULL;

	if (!ctx) {
		return RET_ERR;
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
