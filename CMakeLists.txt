cmake_minimum_required(VERSION 3.4)
project(transfer-text-files)

set(CMAKE_CXX_STANDARD 11)

add_executable(server src/server.cpp src/ttf_net.cpp src/ttf_server.cpp)
add_executable(client src/client.cpp src/ttf_net.cpp src/ttf_client.cpp)
