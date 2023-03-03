#ifndef CMDROUTER_H
#define CMDROUTER_H

#include <memory>
#include <string>

#include "AsyncSender.h"

/// <summary>
/// Class CmdRouter - separates static and dynamic command blocks.
/// </summary>
/// <param name="receiver">Shared pointer to AsyncSender.</param>
class CmdRouter {
public:
    explicit CmdRouter(std::shared_ptr<AsyncSender> sender);

    void send(char* data, std::size_t length);

private:
    std::size_t _bulk_size;

    std::shared_ptr<AsyncSender> _common_sender;

};


#endif //CMDROUTER_H
