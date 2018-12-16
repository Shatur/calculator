cmake_minimum_required(VERSION 2.8)

project(Calc)

set(sources
    "main.cpp"
    "token.cpp"
    "tokenstream.cpp")

add_executable(${PROJECT_NAME} ${sources})
