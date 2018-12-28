cmake_minimum_required(VERSION 2.8)

project(Calculator)
set(CMAKE_CXX_STANDARD 17)

set(sources
    "main.cpp"
    "tokenstream.cpp"
    "token.cpp"
    "parseerror.cpp")

add_executable(${PROJECT_NAME} ${sources})
