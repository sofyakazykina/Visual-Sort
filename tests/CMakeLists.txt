cmake_minimum_required(VERSION 4.0)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project ../main.cpp
        ../src/main.cpp
        ../src/bubble_sort.cpp
        ../src/insertion_sort.cpp
        ../src/selection_sort.cpp
        ../src/console_ui.cpp
        ../src/logger.cpp)
