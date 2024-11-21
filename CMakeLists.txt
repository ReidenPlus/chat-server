cmake_minimum_required(VERSION 3.10)
project(ChatServer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

include_directories(include)
add_executable(chat main.cpp src/ChatServer.cpp src/ChatClient.cpp src/Encryption.cpp)

target_link_libraries(chat OpenSSL::SSL OpenSSL::Crypto)
