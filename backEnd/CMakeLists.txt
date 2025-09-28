cmake_minimum_required(VERSION 3.10)
project(backend)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)

# Onde estão os headers
include_directories(include)

# Pega todos os .cpp da pasta src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Gera o executável "backend"
add_executable(backend main.cpp ${SOURCES})
