cmake_minimum_required(VERSION 3.16) # Проверка версии CMake.

set(CMAKE_CXX_STANDARD 23)
project(test)

file(GLOB CPP "*.cpp")
file(GLOB H "*.h")

add_executable(test ${CPP} ${H})
