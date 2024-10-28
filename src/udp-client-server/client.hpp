#pragma once
#include <boost/asio.hpp>
#include <string>

class ChatClient {
    boost::asio::io_context _ioContext;
    boost::asio::ip::udp::socket _clientSocket;
    boost::asio::ip::udp::endpoint _serverEndpoint;
    bool _isRunning;

    static constexpr int bufferSize = 1024;
    static constexpr char serverIp[] = "127.0.0.1";
    static constexpr int serverPort = 54000;

    void asyncWrite(const std::string& message);

public:
    ChatClient();
    void runClient();
};