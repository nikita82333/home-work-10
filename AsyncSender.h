#ifndef ASYNCSENDER_H
#define ASYNCSENDER_H

#include <string>

#include "async.h"

/// <summary>
/// Class AsyncSender - asynchronously sends commands to processing.
/// </summary>
/// <param name="bulk_size">Command bulk size.</param>
class AsyncSender {
public:
    explicit AsyncSender(std::size_t bulk_size);
    ~AsyncSender();

    [[nodiscard]] std::size_t get_bulk_size() const;
    void send(const std::string& data);
    void reconnect();

private:
    std::size_t _bulk_size;
    async::handle_t _handle;

};


#endif //ASYNCSENDER_H
