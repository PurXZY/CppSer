#include <iostream>
#include <event.h>
#include <event2/listener.h>
#include <arpa/inet.h>
#include "TcpServer.h"
#include "TcpConnection.h"
#include <iostream>

TcpServer::~TcpServer()
{
    event_base_free(m_eBase);
}

void TcpServer::Start(short port) {
	if (!m_eBase) {
		m_eBase = event_base_new();
	}

    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);

	m_listener = evconnlistener_new_bind(
		m_eBase,
		TcpServer::accept_conn_cb,
		nullptr,
		LEV_OPT_LEAVE_SOCKETS_BLOCKING | LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
		-1,
		reinterpret_cast<sockaddr *>(&sin),
		sizeof(sin)
	);
    auto methodName = event_base_get_method(m_eBase);
    std::cout << "libevent use: "<< methodName << std::endl;
	event_base_dispatch(m_eBase);
}

void TcpServer::accept_conn_cb(evconnlistener *listener,evutil_socket_t fd,sockaddr *address, int socklen, void *arg)
{
    char addr[INET_ADDRSTRLEN];
    auto *sin = reinterpret_cast<sockaddr_in *>(address);
    inet_ntop(AF_INET, &sin->sin_addr, addr, INET_ADDRSTRLEN);
    std::cout << "accept " << addr << std::endl;
	TcpServer::getInstance()->OnNewConnection(fd);
}

void TcpServer::OnNewConnection(evutil_socket_t fd)
{
    std::cout << "new connection " << fd << std::endl;
    auto *conn = new TcpConnection(m_eBase, fd);
    m_connections[fd] = conn;
    ShowConnections();
}

void TcpServer::CloseConnection(evutil_socket_t fd)
{
    auto *conn = m_connections[fd];
    delete(conn);
    m_connections.erase(fd);
    ShowConnections();
}

void TcpServer::ShowConnections()
{
    std::cout<< "-------------"<<std::endl<<"total connection size: " << m_connections.size() << std::endl;
    for (auto &v : m_connections)
    {
        std::cout<<"fd: "<<v.first<<std::endl;
    }
    std::cout<<"-------------"<<std::endl;
}
