cmake_minimum_required(VERSION 3.9)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk_server_cli VERSION ${PROJECT_VERSION})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

find_package(Boost COMPONENTS system REQUIRED)
find_package(Threads)
#find_package(Boost COMPONENTS REQUIRED)

add_executable(bulk_server_cli main.cpp Server.cpp Session.cpp CmdRouter.cpp AsyncSender.cpp
        async.cpp Command.cpp Controller.cpp Receiver.cpp)
include_directories(${Boost_INCLUDE_DIRS})

if (WIN32)
    target_link_libraries(bulk_server_cli -lws2_32 -lwsock32)
endif()

set_target_properties(bulk_server_cli PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

if (MSVC)
    target_compile_options(bulk_server_cli PRIVATE
            /W4
            )
else ()
    target_compile_options(bulk_server_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()

install(TARGETS bulk_server_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
