cmake_minimum_required(VERSION 3.10)
project(clido)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)

add_executable(clido
    src/main.cpp
    src/clido.cpp
    src/list.cpp
    src/item.cpp
    src/sqlHandler.cpp
    src/cliHandler.cpp
)
target_include_directories(clido PRIVATE
    include
    extern
)

target_link_libraries(clido ${SQLite3_LIBRARIES})
