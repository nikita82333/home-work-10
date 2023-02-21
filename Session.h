#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "CmdRouter.h"

using boost::asio::ip::tcp;

/// <summary>
/// Class Session - establishes a network connection.
/// </summary>
/// <param name="socket">Network socket.</param>
/// <param name="sender">Shared pointer to AsyncSender.</param>
class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, std::shared_ptr<AsyncSender> sender)
        : _socket(std::move(socket)), _sender(std::move(sender)) {}

    void start();

private:
    void do_read();

    tcp::socket _socket;
    enum { max_length = 1024 };
    char _data[max_length];

    std::shared_ptr<AsyncSender> _sender;
    CmdRouter _router {_sender};

};


#endif //SESSION_H
