#ifndef ASYNCSENDER_H
#define ASYNCSENDER_H

#include "async.h"

/// <summary>
/// Class AsyncSender - asynchronously sends commands to processing.
/// </summary>
/// <param name="bulk_size">Command bulk size.</param>
class AsyncSender {
public:
    explicit AsyncSender(std::size_t bulk_size);
    ~AsyncSender();

    void send(char* data, std::size_t length);
    [[nodiscard]] std::size_t get_bulk_size() const;
    void reconnect();

private:
    async::handle_t _handle;
    std::size_t _bulk_size;
};


#endif //ASYNCSENDER_H
