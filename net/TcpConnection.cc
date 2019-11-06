#include <iostream>
#include "TcpConnection.h"
#include "TcpServer.h"
#include "MsgParser.h"

TcpConnection::TcpConnection(event_base *base, evutil_socket_t fd)
{
	evutil_make_socket_nonblocking(fd);
	m_bEvent = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(
		m_bEvent,
	    TcpConnection::read_event_cb,
        nullptr,
        TcpConnection::error_event_cb,
        this
	);
	bufferevent_enable(m_bEvent, EV_READ | EV_WRITE);
}

TcpConnection::~TcpConnection()
{
	bufferevent_free(m_bEvent);
}

void TcpConnection::read_event_cb(bufferevent *event, void *arg)
{
    auto *conn = reinterpret_cast<TcpConnection *>(arg);
	auto *input = bufferevent_get_input(event);
	size_t inputLen = evbuffer_get_length(input);
	std::cout << "receive: "<< inputLen <<std::endl;
	if (!MsgParser::isFullMsg(input, inputLen))
        return;
}

void TcpConnection::error_event_cb(bufferevent* event, short e, void *arg)
{
	if (e & BEV_EVENT_EOF)
	{
		std::cout<<"eof"<<std::endl;
		auto fd = bufferevent_getfd(event);
		TcpServer::getInstance()->CloseConnection(fd);
	}
}

void TcpConnection::SendData()
{
    char data[] = "hello";
    bufferevent_write(m_bEvent, data, sizeof(data));
}