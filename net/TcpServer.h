#pragma once

#include <event.h>
#include <unordered_map>
#include "Singleton.h"

struct evconnlistener;
struct sockaddr;
class TcpConnection;

class TcpServer : public Singleton<TcpServer> {
public:
    TcpServer() = default;
	~TcpServer();
    void Start(short port);

    static void accept_conn_cb(evconnlistener *listener,evutil_socket_t fd,sockaddr *address, int socklen, void *arg);
	void OnNewConnection(evutil_socket_t fd);
	void CloseConnection(evutil_socket_t fd);
	void ShowConnections();
private:
	event_base* m_eBase;
	evconnlistener* m_listener;
    std::unordered_map<evutil_socket_t, TcpConnection*> m_connections;
};
