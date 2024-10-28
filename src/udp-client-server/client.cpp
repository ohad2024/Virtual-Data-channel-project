#include "client.hpp"
#include <iostream>
#include <thread>

ChatClient::ChatClient() : _clientSocket(_ioContext), _isRunning(true) {
    try {
        _clientSocket.open(boost::asio::ip::udp::v4());
        _serverEndpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(serverIp), serverPort);
    } catch (const boost::system::system_error& e) {
        std::cerr << "Error in ChatClient constructor: " << e.what() << std::endl;
        throw;
    }
}

void ChatClient::runClient() {
    std::thread t([this]() { _ioContext.run(); });

    std::string message;
    while (_isRunning) {
        std::cout << "Enter message to send (or 'exit' to quit): ";
        std::getline(std::cin, message);

        if (message == "exit") {
            _isRunning = false;
        } else {
            asyncWrite(message);
        }
    }

    _clientSocket.close();
    t.join();
}

void ChatClient::asyncWrite(const std::string& message) {
    _clientSocket.async_send_to(
        boost::asio::buffer(message), _serverEndpoint,
        [this](boost::system::error_code ec, std::size_t /*bytesSent*/) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
                _isRunning = false;
            }
        });
}