#include "AsyncSender.h"

AsyncSender::AsyncSender(std::size_t bulk_size) : _bulk_size(bulk_size) {
    _handle = async::connect(bulk_size);
}

AsyncSender::~AsyncSender() {
    async::disconnect(_handle);
}

std::size_t AsyncSender::get_bulk_size() const {
    return _bulk_size;
}

void AsyncSender::send(const std::string& data) {
    async::receive(_handle, data.c_str(), data.length());
}

void AsyncSender::reconnect() {
    async::disconnect(_handle);
    _handle = async::connect(_bulk_size);
}
