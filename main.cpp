#include <iostream>

#include "Server.h"

int main(int argc, char* argv[]) {

    try {
        if (argc != 3 && argc != 4) {
            std::cerr << "Usage: bulk_server <port> <bulk_size> [mode]" << std::endl;
            std::cerr << " - <port> - network port" << std::endl;
            std::cerr << " - <bulk_size> - command block size" << std::endl;
            std::cerr << " - [mode] - operation mode: line or symbolic (optional, line by default)" << std::endl;
            return 1;
        }

        Mode mode = Mode::Line;
        if (argc == 4 && std::string(argv[3]) == "symbolic") {
            mode = Mode::Symbolic;
        }

        boost::asio::io_context io_context;

        Server server(io_context, std::atoi(argv[1]), std::atoi(argv[2]), mode);

        io_context.run();
    }
    catch (const std::exception& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }

    return 0;

}
