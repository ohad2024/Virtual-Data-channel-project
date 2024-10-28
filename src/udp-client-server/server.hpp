#pragma once
#include <boost/asio.hpp>
#include <vector>

class ChatServer {
    boost::asio::io_context _ioContext;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _senderEndpoint;
    
    static constexpr int serverPort = 54000; 
    static constexpr int bufferSize = 1024;

    void asyncReceive();

public:
    ChatServer();
    void runServer();
};