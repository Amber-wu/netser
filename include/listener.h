#ifndef NETSER_LISTENER_H
#define NETSER_LISTENER_H

#include "service_base.h"

typedef struct listen_event_s
{
	int event_type;
	int fd;
	void *(*cb)(void *arg);
	void *arg;
	struct timeval timeout;
} listen_ev;

class listener {
public:
	listener(int max_fd);
	int add(int fd, void *(*cb)(void *arg), void *arg, struct timeval tv);
	int del(int fd);
	int add_service(class service_base *sv);
	int del_service(class service_base *sv);
	int wait(struct timeval *tv);
	int process();
	~listener();
private:
	int max_fd;
	int epoll_fd;
	struct epoll_event *epoll_ev;
	int epoll_active_ev_cnt;
	listen_ev *fd_heap;
	int _init(int max_fd);
};
#endif //NETSER_LISTENER_H
