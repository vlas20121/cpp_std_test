cmake_minimum_required(VERSION 3.16) # Проверка версии CMake.

set(CMAKE_CXX_STANDARD 20)
project(test)

file(GLOB H "*.h")
file(GLOB CPP "*.cpp")

add_executable(test ${CPP} ${H})
