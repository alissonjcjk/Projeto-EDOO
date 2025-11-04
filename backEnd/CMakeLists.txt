cmake_minimum_required(VERSION 3.10)
project(backend)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)

# Onde estão os headers
include_directories(include)

# Baixar e configurar dependências
include(FetchContent)

# cpp-httplib
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.12.1
)

# nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(httplib json)

# Incluir diretórios das dependências
include_directories(${httplib_SOURCE_DIR})
include_directories(${json_SOURCE_DIR}/include)

# Pega todos os .cpp da pasta src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Gera o executável "backend"
add_executable(backend main.cpp ${SOURCES})