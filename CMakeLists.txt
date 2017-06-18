cmake_minimum_required(VERSION 3.7)
project(TestServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
set(CLIENT_FILES client.cpp)
add_executable(TestServer ${SOURCE_FILES})
add_executable(client ${CLIENT_FILES})