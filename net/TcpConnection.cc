#include <iostream>
#include "TcpConnection.h"
#include "TcpServer.h"
#include "../build/protoData/base.pb.h"

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
    size_t recvLen = evbuffer_get_length(input);
    // 接收缓冲区所有数据
    std::cout << "receive buffer size: "<< recvLen <<std::endl;

    // 小于一个包头
    if (recvLen < TcpConnection::MSG_HEADER_SIZE)
    {
        bufferevent_setwatermark(event, EV_READ, TcpConnection::MSG_HEADER_SIZE, 0);
        return;
    }

    char header_len_buf[4];
    memset(header_len_buf, 0, 4);
    evbuffer_copyout(input, header_len_buf, 4);
    size_t pkgSize = header_len_buf[3];
    pkgSize |= header_len_buf[2] << 8;
    pkgSize |= header_len_buf[1] << 16;
    pkgSize |= header_len_buf[0] << 24;
    std::cout << "pkgSize: " << pkgSize << std::endl;

    // 小于完整包
    if (recvLen < pkgSize)
    {
        bufferevent_setwatermark(event, EV_READ, pkgSize, 0);
        return;
    }

    char *msgData = (char *) malloc(pkgSize);
    evbuffer_remove(input, msgData, pkgSize);
    unsigned short msgId = msgData[5];
    msgId |= msgData[4] << 8;
    conn->HandleMsg(msgId, msgData + TcpConnection::MSG_HEADER_SIZE);
    free(msgData);

    // 还有数据
    recvLen =  evbuffer_get_length(input);
    if (recvLen > 0)
    {
        read_event_cb(event, arg);
    }
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

void TcpConnection::HandleMsg(unsigned short msgId, char *data)
{
    std::cout << "msgId: " << msgId << std::endl;
    if (msgId == usercmd::LoginReq)
    {
        usercmd::LoginC2SMsg msg;
        msg.ParseFromString(data);
        std::cout << "msg name: " << msg.name() << std::endl;
    }
}