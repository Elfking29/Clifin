cmake_minimum_required(VERSION 3.10.0)
project(Clifin VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCES
    main.cpp
    src/network.cpp
    src/secrets.cpp
)
add_executable(Clifin ${SOURCES})
target_include_directories(Clifin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)