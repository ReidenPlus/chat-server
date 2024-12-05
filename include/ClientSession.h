#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

#include <boost/asio.hpp>
#include <memory>
#include <string>

class ChatServer;

class ClientSession : public std::enable_shared_from_this<ClientSession> {
public:
    ClientSession(boost::asio::ip::tcp::socket socket, ChatServer& server);
    void start();
    void sendMessage(const std::string& message);

private:
    boost::asio::ip::tcp::socket socket_;
    ChatServer& server_;
    char buffer_[1024];

    void readMessage();
    void handleRead(std::size_t bytes_transferred);
};

#endif // CLIENT_SESSION_H
