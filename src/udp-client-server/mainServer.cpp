#include "server.hpp"
#include <iostream>

int main() {
    try {
        ChatServer server;
        server.runServer();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}