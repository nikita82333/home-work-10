#ifndef SERVER_H
#define SERVER_H

#include "Session.h"

/// <summary>
/// Class Server - asynchronous server (by boost).
/// </summary>
/// <param name="io_context">Provides the core I/O functionality.</param>
/// <param name="port">Network port.</param>
/// <param name="bulk_size">Command bulk size.</param>
/// <param name="mode">Server operation mode (line or symbolic).</param>
class Server {
public:
    Server(boost::asio::io_context& io_context, short port, std::size_t bulk_size, Mode mode);

private:
    void do_accept();

    tcp::acceptor _acceptor;
    std::shared_ptr<AsyncSender> _sender;
    Mode _mode;

};


#endif //SERVER_H
