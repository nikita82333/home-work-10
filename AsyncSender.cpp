#include "AsyncSender.h"

AsyncSender::AsyncSender(std::size_t bulk_size) : _bulk_size(bulk_size) {
    _handle = async::connect(bulk_size);
}

AsyncSender::~AsyncSender() {
    async::disconnect(_handle);
}

void AsyncSender::send(char* data, std::size_t length) {
    async::receive(_handle, data, length);
}

std::size_t AsyncSender::get_bulk_size() const {
    return _bulk_size;
}

void AsyncSender::reconnect() {
    async::disconnect(_handle);
    _handle = async::connect(_bulk_size);
}
