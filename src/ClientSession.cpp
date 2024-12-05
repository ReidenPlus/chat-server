#include "ClientSession.h"
#include "ChatServer.h"
#include <iostream> // Для вывода сообщений в терминал

ClientSession::ClientSession(boost::asio::ip::tcp::socket socket, ChatServer& server)
    : socket_(std::move(socket)), server_(server) {}

void ClientSession::start() {
    readMessage();
}

void ClientSession::sendMessage(const std::string& message) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(message), [this, self](boost::system::error_code ec, std::size_t) {
        if (ec) {
            std::cerr << "Failed to send message: " << ec.message() << std::endl;
        }
    });
}

void ClientSession::readMessage() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(buffer_, sizeof(buffer_)), [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
        if (!ec) {
            handleRead(bytes_transferred);
        } else {
            std::cerr << "Error reading message: " << ec.message() << std::endl;
        }
    });
}

void ClientSession::handleRead(std::size_t bytes_transferred) {
    // Преобразуем буфер в строку
    std::string message(buffer_, bytes_transferred);

    // Выводим сообщение в консоль сервера
    std::cout << "Received message: " << message << std::endl;

    // Отправляем сообщение другим клиентам
    server_.broadcastMessage(message, shared_from_this());

    // Ждём следующее сообщение
    readMessage();
}
