#include "websocket_client.h"
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_tls_client> client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;

class WebSocketClientImpl {
public:
    WebSocketClientImpl() : endpoint_(), connection_() {
        endpoint_.set_access_channels(websocketpp::log::alevel::none);
        endpoint_.set_error_channels(websocketpp::log::elevel::fatal);
        endpoint_.init_asio();
        endpoint_.set_tls_init_handler([](websocketpp::connection_hdl) {
            return websocketpp::lib::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tlsv12);
        });
    }

    bool connect(const std::string& url) {
        websocketpp::lib::error_code ec;
        connection_ = endpoint_.get_connection(url, ec);
        if (ec) {
            std::cout << "Connection error: " << ec.message() << std::endl;
            return false;
        }

        endpoint_.connect(connection_);
        endpoint_.run();
        return true;
    }

    bool send(const std::string& message) {
        websocketpp::lib::error_code ec;
        endpoint_.send(connection_->get_handle(), message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cout << "Send error: " << ec.message() << std::endl;
            return false;
        }
        return true;
    }

    std::string receive() {
        // In a real application, you'd implement a proper message queue and callback system
        // This is a simplified version for demonstration purposes
        return "Echo: " + last_message_;
    }

    void close() {
        websocketpp::lib::error_code ec;
        endpoint_.close(connection_->get_handle(), websocketpp::close::status::normal, "Closing connection", ec);
        if (ec) {
            std::cout << "Close error: " << ec.message() << std::endl;
        }
    }

private:
    client endpoint_;
    client::connection_ptr connection_;
    std::string last_message_;
};

WebSocketClient::WebSocketClient() : impl_(new WebSocketClientImpl()) {}
WebSocketClient::~WebSocketClient() { delete impl_; }

bool WebSocketClient::connect(const std::string& url) { return impl_->connect(url); }
bool WebSocketClient::send(const std::string& message) { return impl_->send(message); }
std::string WebSocketClient::receive() { return impl_->receive(); }
void WebSocketClient::close() { impl_->close(); }