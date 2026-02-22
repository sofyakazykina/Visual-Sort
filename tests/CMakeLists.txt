# Добавляем Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Создаём исполняемый файл для тестов (ТОЛЬКО тесты!)
add_executable(sorter_test
        sorter_test.cpp
)

# Связываем с библиотекой и Google Test
target_link_libraries(sorter_test
        PRIVATE
        sortlib
        GTest::gtest_main
)

# Добавляем тест в CTest
add_test(
        NAME SorterTests
        COMMAND sorter_test
)