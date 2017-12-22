//
// Created by pg on 17-12-22.
//

#ifndef NETSER_SERVICE_BASE_H
#define NETSER_SERVICE_BASE_H

class service_base{
public:
    service_base(unsigned long ip, int port);
    int init();
    int start();
    int pause();
    int resume();
    int terminate();
    unsigned long get_ip();
    int get_port();
    int get_fd();
private:
    unsigned long ip;
    int port;
    int fd;
    int init_flag;
    void *pctx;
};

#endif //NETSER_SERVICE_BASE_H
