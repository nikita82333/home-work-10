#include <future>
#include <cstring>

#include "Controller.h"
#include "async.h"

namespace async {

    struct Context {
        std::unique_ptr<Controller> controller;
        std::vector<std::future<void>> futures;
        std::mutex futures_mutex;
        std::mutex parser_mutex;
    };

    handle_t connect(std::size_t bulk) {
        auto receiver = std::make_shared<Receiver>();
        auto controller = std::make_unique<Controller>(bulk, receiver);
        auto context = new Context{std::move(controller), {}, {}, {}};
        return reinterpret_cast<void *>(context);
    }

    void receive(handle_t handle, const char *data, std::size_t size) {
        auto context = reinterpret_cast<Context*>(handle);

        auto worker = [](Context* context, const char *data, std::size_t size) {
            std::string line;
            for (std::size_t i = 0; i < size; ++i) {
                if (data[i] != ' ' && data[i] != '\n') {
                    line += data[i];
                } else {
                    if (!line.empty()) {
                        std::lock_guard<std::mutex> lock(context->parser_mutex);
                        context->controller->parse_command(line);
                        line.clear();
                    }
                }
            }
            if (!line.empty()) {
                std::lock_guard<std::mutex> lock(context->parser_mutex);
                context->controller->parse_command(line);
            }
            delete[] data;
        };

        char* data_copy = new char[size];
        memcpy(data_copy, data, size);

        auto future = std::async(std::launch::async, worker, context, data_copy, size);
        std::lock_guard<std::mutex> lock(context->futures_mutex);
        context->futures.push_back(std::move(future));
    }

    void disconnect(handle_t handle) {
        auto context = reinterpret_cast<Context*>(handle);

        for (const auto& future : context->futures) {
            future.wait();
        }
        context->controller->parse_command("EOF");

        delete context;
    }
}
