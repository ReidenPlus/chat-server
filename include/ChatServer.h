#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <unordered_set>

class ClientSession;

class ChatServer {
public:
    ChatServer(boost::asio::io_context& io_context, unsigned short port);
    void start();

    void broadcastMessage(const std::string& message, std::shared_ptr<ClientSession> sender);

private:
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unordered_set<std::shared_ptr<ClientSession>> clients_;

    void acceptConnection();
};

#endif // CHAT_SERVER_H
