#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H

#include "websocket_client.h"

class ChatInterface {
public:
    ChatInterface();
    void run();

private:
    WebSocketClient client_;
};

#endif // CHAT_INTERFACE_H