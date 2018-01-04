//
// Created by pg on 17-12-22.
//

#ifndef NETSER_SERVICE_BASE_H
#define NETSER_SERVICE_BASE_H

#define SERVICE_MAX_CLIENT_NUM 1024
#define SERVICE_DEF_CLIENT_NUM 10

class service_base{
public:
    service_base(unsigned long ip, int port);
    int init();
    int start();
    int pause();
    int resume();
    int terminate();
    int accept_client();

    // set / get
    int set_listen_num(int listen_num);
    unsigned long get_ip();
    int get_port();
    int get_fd();
private:
    unsigned long ip;
    int port;
    int fd;
    int listen_num;
    int init_flag;
    void *pctx;
};

#endif //NETSER_SERVICE_BASE_H
