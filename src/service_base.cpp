//
// Created by pg on 17-12-22.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#include "service_base.h"
#include "utils.h"

service_base::service_base(unsigned long ip, int port)
{
    this->ip = ip;
    this->port = port;
    this->listen_num = SERVICE_DEF_CLIENT_NUM;
    this->init_flag = 0;
}

int service_base::init()
{
    int fd = -1;
    int ret = 0;
    struct sockaddr_in srv_addr;

    memset(&srv_addr, 0, sizeof(struct sockaddr_in));

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(this->ip);
    srv_addr.sin_port = htons(this->port);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        PMD("create socket failed\n");
        ret = RET_ERR;
        goto create_err;
    }

    ret = bind(fd, (struct sockaddr*)&srv_addr, sizeof(struct sockaddr));
    if (ret)
    {
        PMD("bind failed\n");
        ret = RET_ERR;
        goto bind_err;
    }

    if (RET_OK != set_fd_nonblocking(fd))
    {
        PMD("set socket flags failed\n");
        ret = RET_ERR;
        goto set_fd_nonblocking_err;
    }

    ret = listen(fd, this->listen_num);
    if (ret)
    {
        PMD("listen failed, %s(%d)\n", strerror(errno), errno);
        ret = RET_ERR;
        goto listen_err;
    }

    this->fd = fd;
    this->init_flag = 1;

    return RET_OK;

listen_err:
set_fd_nonblocking_err:
bind_err:
    CLOSE_FD(fd);

create_err:

    return ret;
}

int service_base::start()
{
    if (!this->init_flag)
    {
        PMD("service not init yet\n");
        return RET_ERR;
    }

    return RET_OK;
}

int service_base::set_listen_num(int listen_num)
{
    this->listen_num = listen_num < SERVICE_MAX_CLIENT_NUM ? listen_num : SERVICE_MAX_CLIENT_NUM;
    return RET_OK;
}

unsigned long service_base::get_ip() {
    return this->ip;
}
int service_base::get_port() {
    return this->port;
}
int service_base::get_fd() {
    return this->fd;
}