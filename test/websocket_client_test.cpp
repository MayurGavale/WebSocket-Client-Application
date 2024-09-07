#include "websocket_client.h"
#include <cassert>
#include <iostream>

void test_websocket_client() {
    WebSocketClient client;
    
    // Test connection
    bool connected = client.connect("wss://echo.websocket.events/.ws");
    assert(connected && "Failed to connect to WebSocket server");

    // Test sending and receiving a message
    std::string test_message = "Hello, WebSocket!";
    bool sent = client.send(test_message);
    assert(sent && "Failed to send message");

    std::string response = client.receive();
    assert(response == "Echo: " + test_message && "Received unexpected response");

    // Test closing the connection
    client.close();

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_websocket_client();
    return 0;
}