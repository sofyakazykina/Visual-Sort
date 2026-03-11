add_executable(sorter_test sorter_test.cpp)

target_link_libraries(sorter_test
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        sortlib
)

target_include_directories(sorter_test
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

add_test(NAME SorterTests COMMAND sorter_test)