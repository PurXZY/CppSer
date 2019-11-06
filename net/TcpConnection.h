#pragma once

#include <event.h>

class TcpConnection
{
public:
	TcpConnection(event_base* base, evutil_socket_t fd);
	~TcpConnection();

	void SendData();
public:
	static void read_event_cb(bufferevent* event, void *arg);
	static void error_event_cb(bufferevent* event, short e, void *arg);
private:
    bufferevent* m_bEvent;
};
