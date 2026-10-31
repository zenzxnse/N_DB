cmake_minimum_required(VERSION 4.0)

project(N_ENGINE
    VERSION 1.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(executor
    src/engine.cxx
    src/db.cxx
    src/types.cxx
)

target_include_directories(executor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)




