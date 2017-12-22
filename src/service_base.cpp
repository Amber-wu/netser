//
// Created by pg on 17-12-22.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "service_base.h"
#include "utils.h"

service_base::service_base(unsigned long ip, int port)
{
    this->ip = ip;
    this->port = port;
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

    this->fd = fd;
    this->init_flag = 1;

    return RET_OK;

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

unsigned long service_base::get_ip() {
    return this->ip;
}
int service_base::get_port() {
    return this->port;
}
int service_base::get_fd() {
    return this->fd;
}