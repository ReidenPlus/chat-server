#include "ChatServer.h"
#include <boost/asio.hpp>
#include <iostream>

int main() {
    try {
        boost::asio::io_context io_context;
        unsigned short port = 8080;

        ChatServer server(io_context, port);
        server.start();

        std::cout << "Chat server is running on port " << port << "..." << std::endl;
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
