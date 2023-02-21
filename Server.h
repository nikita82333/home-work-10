#ifndef SERVER_H
#define SERVER_H

#include "Session.h"

/// <summary>
/// Class Server - asynchronous server (by boost).
/// </summary>
/// <param name="io_context">Provides the core I/O functionality.</param>
/// <param name="port">Network port.</param>
/// <param name="bulk_size">Command bulk size.</param>
class Server {
public:
    Server(boost::asio::io_context& io_context, short port, std::size_t bulk_size);

private:
    void do_accept();

    tcp::acceptor _acceptor;
    std::shared_ptr<AsyncSender> _sender;

};


#endif //SERVER_H
