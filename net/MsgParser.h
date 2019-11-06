#pragma once

#include "event.h"

class MsgParser {
public:
    static const int MSG_HEADER_SIZE = 6; // 4 + 2
public:
    static bool isFullMsg(evbuffer *buf, int dataLen);
};
