#include <iostream>

#include "Server.h"

int main(int argc, char* argv[]) {

    try {
        if (argc != 3) {
            std::cerr << "Usage: bulk_server <port> <bulk_size>" << std::endl;
            return 1;
        }

        boost::asio::io_context io_context;

        Server server(io_context, std::atoi(argv[1]), std::atoi(argv[2]));

        io_context.run();
    }
    catch (const std::exception& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }

    return 0;

}
