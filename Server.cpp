#include "Server.h"

Server::Server(boost::asio::io_context& io_context, short port, std::size_t bulk_size, Mode mode)
        : _acceptor(io_context, tcp::endpoint(tcp::v4(), port)), _mode(mode) {
    _sender = std::make_shared<AsyncSender>(bulk_size);
    do_accept();
}

void Server::do_accept() {
    _acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), _sender, _mode)->start();
            }

            do_accept();
        });
}
