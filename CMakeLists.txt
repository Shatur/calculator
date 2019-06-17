cmake_minimum_required(VERSION 2.8)

project(Calculator)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/tokenstream.cpp
    src/token.cpp
    src/parseerror.cpp
    )
