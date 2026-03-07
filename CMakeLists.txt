cmake_minimum_required(VERSION 3.24)
project(VisualSort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ✅ ПУТИ К ЗАГОЛОВКАМ (ОБЯЗАТЕЛЬНО!)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(sortlib STATIC
        src/bubble_sort.cpp
        src/insertion_sort.cpp
        src/selection_sort.cpp
        src/quick_sort.cpp
        src/merge_sort.cpp
        src/heap_sort.cpp
        src/shell_sort.cpp
        src/counting_sort.cpp
        src/logger.cpp
        src/console_ui.cpp
)

add_executable(main_app
        src/main.cpp
)

# Связываем программу с библиотекой
target_link_libraries(main_app PRIVATE sortlib)

enable_testing()
add_subdirectory(tests)