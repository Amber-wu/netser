#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>
#include <errno.h>

#include "listener.h"
#include "utils.h"

/*
class listener_op {
public:
	string name;
	void *(*init)(void *arg);
	int *(*add)(int fd, int events, struct timeval tv);
	int *(*del)(int fd);
	int *(*wait)();
}
*/

listener::listener(int max_fd)
{
	int ret = 0;

	ret = this->_init(max_fd);
	if (ret != RET_OK)
	{
		PMD("init failed\n");
	}
}

int listener::add(int fd, void *(*cb)(void *arg), void *arg, struct timeval tv)
{
	int ret = 0;
	struct epoll_event ev;

	ev.data.fd = fd;
	ev.events = EPOLLIN | EPOLLOUT;

	ret = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, fd, &ev);
	if (ret)
	{
		perror("epoll_ctl");
		return RET_ERR;
	}

	return RET_OK;
}

int listener::del(int fd)
{
	int ret = 0;
	struct epoll_event ev;

	ret = epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, fd, &ev);
	if (ret)
	{
		perror("epoll_ctl delete");
		return RET_ERR;
	}

	// TODO add to min-heap

	return RET_OK;
}


int listener::add_service(class service_base *sv)
{
	int ret = 0;
	struct epoll_event ev;

	if (!sv)
	{
		PMD("service NULL\n");
		return RET_ERR;
	}

	memset(&ev, 0, sizeof(ev));

	ev.data.ptr = (void *)sv;
	ev.events = EPOLLIN | EPOLLOUT;

	ret = epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, sv->get_fd(), &ev);
	if (ret)
	{
		perror("epoll_ctl");
		return RET_ERR;
	}

	// TODO add to min-heap

	return RET_OK;
}

int listener::del_service(class service_base *sv)
{
	if (!sv)
	{
		PMD("service NULL\n");
		return RET_ERR;
	}

	int ret = 0;
	struct epoll_event ev;

	ret = epoll_ctl(this->epoll_fd, EPOLL_CTL_DEL, sv->get_fd(), &ev);
	if (ret)
	{
		perror("epoll_ctl delete");
		return RET_ERR;
	}

	return RET_OK;
}
int listener::wait(struct timeval *tv)
{
	int milliseconds = 0;

	if (!this->epoll_ev)
	{
		PMD("epoll_ev not malloc yet\n");
		return RET_ERR;
	}

	memset(this->epoll_ev, 0, sizeof(struct epoll_event) * this->max_fd);
	milliseconds = tv ? (tv->tv_sec * 1000 + tv->tv_usec / 1000) : -1;
	// TODO latest timeout
	this->epoll_active_ev_cnt = epoll_wait(this->epoll_fd, this->epoll_ev, this->max_fd, milliseconds);
	if (this->epoll_active_ev_cnt < 0)
	{
		PMD("epoll_wait failed, %s(%d)", strerror(errno), errno);
		return RET_ERR;
	}
	else
	{
		PMD("%d events become actived in %d milliseconds", this->epoll_active_ev_cnt, milliseconds);
	}

	return RET_OK;
}

int listener::process()
{
	// TODO active list, timeout list

	int i = 0;
	struct epoll_event *p_cur = NULL;
	service_base *p_service = NULL;

	for (i = 0; i < this->epoll_active_ev_cnt; i++)
	{
		p_cur = &(this->epoll_ev[i]);
		p_service = (service_base *)p_cur->data.ptr;


	}
	return RET_OK;
}

listener::~listener()
{
	if (this->fd_heap)
	{
		free(this->fd_heap);
		this->fd_heap = NULL;
	}

	if (this->epoll_ev)
	{
		free(this->epoll_ev);
		this->epoll_ev = NULL;
	}
}

int listener::_init(int max_fd)
{
	this->max_fd = max_fd;
	this->epoll_active_ev_cnt = 0;

	this->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	if (this->epoll_fd < 0)
	{
		perror("epoll_create1");
		return RET_ERR;
	}

	this->epoll_ev = (struct epoll_event *)malloc(sizeof(struct epoll_event) * this->max_fd);
	if (!this->epoll_ev)
	{
		PMD("malloc epoll events failed\n");
		return RET_ERR;
	}

	this->fd_heap = (listen_ev *)calloc(max_fd, sizeof(listen_ev));
	if (!this->fd_heap)
	{
		PMD("calloc failed\n");
		return RET_ERR;
	}

	return RET_OK;
}
