#pragma once

#include <event.h>

class TcpConnection
{
private:
    static const int MSG_HEADER_SIZE = 6; // 4 + 2

public:
	TcpConnection(event_base* base, evutil_socket_t fd);
	~TcpConnection();

	void SendData();
	void HandleMsg(unsigned short msgId, char *data);
public:
	static void read_event_cb(bufferevent* event, void *arg);
	static void error_event_cb(bufferevent* event, short e, void *arg);
private:
    bufferevent* m_bEvent;
};
