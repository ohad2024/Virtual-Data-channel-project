#include "server.hpp"
#include <iostream>

ChatServer::ChatServer()
    : _socket(_ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), serverPort)) {
}

void ChatServer::runServer() {
    std::cout << "Server started on port " << serverPort << std::endl;
    asyncReceive();
    _ioContext.run();
}

void ChatServer::asyncReceive() {
    auto buffer = std::make_shared<std::vector<char>>(bufferSize);
    _socket.async_receive_from(
        boost::asio::buffer(*buffer), _senderEndpoint,
        [this, buffer](boost::system::error_code ec, std::size_t bytesReceived) {
            if (!ec && bytesReceived > 0) {
                std::string message(buffer->begin(), buffer->begin() + bytesReceived);
                std::cout << "Received message: " << message << std::endl;
            } else {
                std::cerr << "Receive error: " << ec.message() << std::endl;
            }
            asyncReceive();
        });
}