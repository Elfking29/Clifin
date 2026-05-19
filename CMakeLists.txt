cmake_minimum_required(VERSION 3.20)

project(clifin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(clifin
    src/main.cpp
    src/network.cpp
    src/ui.cpp
)

target_include_directories(clifin PRIVATE include)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(clifin PRIVATE
    cpr::cpr
    nlohmann_json::nlohmann_json
    )