#include "Session.h"

Session::~Session() {
    if (_sender.use_count() == 3)//why 3? because...
        _sender->reconnect();//if last active session closed -> processing remaining part of static block
}

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                if (_mode == Mode::Symbolic) {
                    if (_data[length - 1] != '\n') {
                        _line += std::string(_data, length);
                    } else {
                        if (_line.length() > 0) {
                            _router.send(const_cast<char *>(_line.c_str()), _line.length());
                            _line.clear();
                        }
                    }
                } else if (_mode == Mode::Line) {
                    _router.send(_data, length);
                }
                do_read();
            }
        });
}
