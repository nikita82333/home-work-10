#include "CmdRouter.h"

CmdRouter::CmdRouter(std::shared_ptr<AsyncSender> sender) : _common_sender(std::move(sender)) {
    _bulk_size = _common_sender->get_bulk_size();
}

void CmdRouter::send(char* data, std::size_t length) {

    std::string dynamic_block;
    std::string static_block;
    bool is_dynamic_block = false;
    int brackets_count = 0;
    for (std::size_t i = 0; i < length; ++i) {
        if (data[i] == '{') {
            if (!is_dynamic_block) {
                dynamic_block = data[i];
                is_dynamic_block = true;
                if (!static_block.empty()) {
                    std::lock_guard<std::mutex> lock(_common_sender_mutex);
                    _common_sender->send(const_cast<char*>(static_block.c_str()), static_block.length());
                }
            }
            ++brackets_count;
        } else if (is_dynamic_block && data[i] == '}') {
            if (brackets_count > 0) {
                --brackets_count;
            }
            if (brackets_count == 0) {
                dynamic_block += data[i];
                AsyncSender sender(_bulk_size);
                sender.send(const_cast<char*>(dynamic_block.c_str()), dynamic_block.length());
                is_dynamic_block = false;
                static_block.clear();
            }
        } else if (is_dynamic_block) {
            dynamic_block += data[i];
        } else {
            static_block += data[i];
        }
    }
    if (brackets_count == 0 && !static_block.empty()) {
        std::lock_guard<std::mutex> lock(_common_sender_mutex);
        _common_sender->send(const_cast<char*>(static_block.c_str()), static_block.length());
    }
    std::lock_guard<std::mutex> lock(_common_sender_mutex);
    _common_sender->reconnect();//there may also be other ways
}
