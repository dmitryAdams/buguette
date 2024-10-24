cmake_minimum_required(VERSION 3.28)
project(bugguette)

set(CMAKE_CXX_STANDARD 17)

add_executable(bugguette main.cpp
        starter.cpp
        lexer.cpp
        globalVariables.h)
