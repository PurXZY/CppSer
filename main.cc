#include "net/TcpServer.h"

int main()
{
	TcpServer::getInstance()->Start(8888);
}
