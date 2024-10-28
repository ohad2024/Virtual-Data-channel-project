#include "client.hpp"
#include <iostream>

int main() {
    try {
        ChatClient client;
        client.runClient();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}