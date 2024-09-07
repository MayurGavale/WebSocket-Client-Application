#include "chat_interface.h"
#include <iostream>
#include <string>

ChatInterface::ChatInterface() {}

void ChatInterface::run() {
    std::cout << "WebSocket Chat Client" << std::endl;
    std::cout << "Connecting to server..." << std::endl;

    if (client_.connect("wss://echo.websocket.events/.ws")) {
        std::cout << "Connected successfully!" << std::endl;

        while (true) {
            std::string message;
            std::cout << "Enter a message (or 'quit' to exit): ";
            std::getline(std::cin, message);

            if (message == "quit") {
                break;
            }

            if (client_.send(message)) {
                std::string response = client_.receive();
                std::cout << "Server response: " << response << std::endl;
            } else {
                std::cout << "Failed to send message." << std::endl;
            }
        }

        client_.close();
    } else {
        std::cout << "Failed to connect to the server." << std::endl;
    }
}