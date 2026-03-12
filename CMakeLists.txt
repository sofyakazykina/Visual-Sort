cmake_minimum_required(VERSION 3.20)
project(VisualSort VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

target_include_directories(sortlib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(main_app
        src/main.cpp
)

target_link_libraries(main_app
        PRIVATE
        sortlib
)

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()