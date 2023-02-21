#include "Session.h"

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                if (length > 0) {
                    _router.send(_data, length);
                }
                do_read();
            }
        });
}
