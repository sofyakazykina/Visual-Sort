cmake_minimum_required(VERSION 3.20)
project(SortVisualizer LANGUAGES CXX)

# Стандарт C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/include)

# Библиотека с алгоритмами сортировки
add_library(sortlib STATIC
        src/bubble_sort.cpp
        src/insertion_sort.cpp
        src/selection_sort.cpp
        src/logger.cpp
)

# Исполняемый файл (основная программа)
add_executable(main_app
        src/main.cpp
        src/console_ui.cpp
)

# Связываем программу с библиотекой
target_link_libraries(main_app PRIVATE sortlib)

# Тесты
enable_testing()
add_subdirectory(tests)