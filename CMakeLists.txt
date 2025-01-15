cmake_minimum_required(VERSION 3.16)

project(AoC2024 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB DAYS "src/*.cpp")
add_executable(AoC2024 main.cpp ${DAYS})

target_include_directories(AoC2024 PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(AoC2024 PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS AoC2024 DESTINATION bin)
