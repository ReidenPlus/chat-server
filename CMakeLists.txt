cmake_minimum_required(VERSION 3.10)

project(ChatServer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Источники и заголовки
include_directories(include)
file(GLOB SOURCES src/*.cpp)

# Основной исполняемый файл
add_executable(chat-server main.cpp ${SOURCES})

# Подключение Boost
find_package(Boost REQUIRED COMPONENTS system)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(chat-server ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost library not found!")
endif()
