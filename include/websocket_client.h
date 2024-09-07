#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <string>

class WebSocketClient {
public:
    WebSocketClient();
    ~WebSocketClient();

    bool connect(const std::string& url);
    bool send(const std::string& message);
    std::string receive();
    void close();

private:
    // Implementation details will be added later
};

#endif // WEBSOCKET_CLIENT_H