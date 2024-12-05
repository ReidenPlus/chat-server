#include "ChatServer.h"
#include "ClientSession.h"

ChatServer::ChatServer(boost::asio::io_context& io_context, unsigned short port)
    : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

void ChatServer::start() {
    acceptConnection();
}

void ChatServer::broadcastMessage(const std::string& message, std::shared_ptr<ClientSession> sender) {
    for (auto& client : clients_) {
        if (client != sender) {
            client->sendMessage(message);
        }
    }
}

void ChatServer::acceptConnection() {
    acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
        if (!ec) {
            auto client = std::make_shared<ClientSession>(std::move(socket), *this);
            clients_.insert(client);
            client->start();
        }
        acceptConnection();
    });
}
