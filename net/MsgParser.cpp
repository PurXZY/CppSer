#include "MsgParser.h"
#include "cstdlib"
#include <iostream>

bool MsgParser::isFullMsg(evbuffer *buf, int dataLen)
{
    if (dataLen < MsgParser::MSG_HEADER_SIZE)
        return false;
    char header_len_buf[4] = {0};
    evbuffer_copyout(buf, header_len_buf, 4);
    int header_len = atoi(header_len_buf);
    std::cout << "header_len: " << header_len << std::endl;
    return true;
}