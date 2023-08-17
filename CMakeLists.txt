cmake_minimum_required(VERSION 3.4)
project(transfer-text-files)


add_executable(server src/server.cpp src/ttf_net.cpp src/ttf_server.cpp src/crc.cpp)
add_executable(client src/client.cpp src/ttf_net.cpp src/ttf_client.cpp src/crc.cpp)
