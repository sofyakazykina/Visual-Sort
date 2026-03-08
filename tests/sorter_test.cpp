#include <gtest/gtest.h>
#include "../include/bubble_sort.hpp"
#include "../include/insertion_sort.hpp"
#include "../include/selection_sort.hpp"
#include <vector>
#include <algorithm>
#include "../include/quick_sort.hpp"
#include "../include/merge_sort.hpp"
#include "../include/heap_sort.hpp"
#include "../include/shell_sort.hpp"
#include "../include/counting_sort.hpp"

class SortTest : public ::testing::Test {
protected:
    std::vector<int> unsorted;
    std::vector<int> expected;

    void SetUp() override {
        unsorted = {5, 2, 8, 1, 9, 3};
        expected = {1, 2, 3, 5, 8, 9};
    }
};

// Bubble Sort тест
TEST_F(SortTest, BubbleSort_SortsCorrectly) {
BubbleSort sorter;
auto result = sorter.sort(unsorted);
EXPECT_EQ(result.sorted_array, expected);
}

// Insertion Sort тест
TEST_F(SortTest, InsertionSort_SortsCorrectly) {
InsertionSort sorter;
auto result = sorter.sort(unsorted);
EXPECT_EQ(result.sorted_array, expected);
}

// Selection Sort тест
TEST_F(SortTest, SelectionSort_SortsCorrectly) {
SelectionSort sorter;
auto result = sorter.sort(unsorted);
EXPECT_EQ(result.sorted_array, expected);
}

// Пустой массив
TEST_F(SortTest, EmptyArray_DoesNotCrash) {
BubbleSort sorter;
std::vector<int> empty;
auto result = sorter.sort(empty);
EXPECT_TRUE(result.sorted_array.empty());
}

// Один элемент
TEST_F(SortTest, SingleElement_DoesNotCrash) {
BubbleSort sorter;
std::vector<int> single = {42};
auto result = sorter.sort(single);
EXPECT_EQ(result.sorted_array.size(), 1);
}

// Уже отсортированный массив
TEST_F(SortTest, AlreadySorted_WorksCorrectly) {
BubbleSort sorter;
std::vector<int> sorted = {1, 2, 3, 4, 5};
auto result = sorter.sort(sorted);
EXPECT_EQ(result.sorted_array, sorted);
}

// Обратный порядок
TEST_F(SortTest, ReverseOrder_SortsCorrectly) {
BubbleSort sorter;
std::vector<int> reverse = {5, 4, 3, 2, 1};
std::vector<int> expected = {1, 2, 3, 4, 5};
auto result = sorter.sort(reverse);
EXPECT_EQ(result.sorted_array, expected);
}

// Проверка статистики (сравнения > 0)
TEST_F(SortTest, BubbleSort_CountsComparisons) {
BubbleSort sorter;
auto result = sorter.sort(unsorted);
EXPECT_GT(result.comparisons, 0);
}

// Проверка статистики (перестановки >= 0)
TEST_F(SortTest, BubbleSort_CountsSwaps) {
BubbleSort sorter;
auto result = sorter.sort(unsorted);
EXPECT_GE(result.swaps, 0);
}

// Проверка времени (время > 0)
TEST_F(SortTest, BubbleSort_MeasuresTime) {
BubbleSort sorter;
auto result = sorter.sort(unsorted);
EXPECT_GE(result.execution_time_ms, 0);
}

// Quick Sort тесты
TEST_F(SortTest, QuickSort_SortsCorrectly) {
    QuickSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_EQ(result.sorted_array, expected);
}

TEST_F(SortTest, QuickSort_CountsComparisons) {
    QuickSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GT(result.comparisons, 0);
}

TEST_F(SortTest, QuickSort_CountsSwaps) {
    QuickSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.swaps, 0);
}

TEST_F(SortTest, QuickSort_MeasuresTime) {
    QuickSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.execution_time_ms, 0);
}

// Merge Sort тесты

TEST_F(SortTest, MergeSort_SortsCorrectly) {
    MergeSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_EQ(result.sorted_array, expected);
}

TEST_F(SortTest, MergeSort_CountsComparisons) {
    MergeSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GT(result.comparisons, 0);
}

TEST_F(SortTest, MergeSort_CountsSwaps) {
    MergeSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.swaps, 0);
}

TEST_F(SortTest, MergeSort_MeasuresTime) {
    MergeSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.execution_time_ms, 0);
}

// Heap Sort тесты

TEST_F(SortTest, HeapSort_SortsCorrectly) {
    HeapSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_EQ(result.sorted_array, expected);
}

TEST_F(SortTest, HeapSort_CountsComparisons) {
    HeapSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GT(result.comparisons, 0);
}

TEST_F(SortTest, HeapSort_CountsSwaps) {
    HeapSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.swaps, 0);
}

TEST_F(SortTest, HeapSort_MeasuresTime) {
    HeapSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.execution_time_ms, 0);
}

// Shell Sort тесты

TEST_F(SortTest, ShellSort_SortsCorrectly) {
    ShellSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_EQ(result.sorted_array, expected);
}

TEST_F(SortTest, ShellSort_CountsComparisons) {
    ShellSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GT(result.comparisons, 0);
}

TEST_F(SortTest, ShellSort_CountsSwaps) {
    ShellSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.swaps, 0);
}

TEST_F(SortTest, ShellSort_MeasuresTime) {
    ShellSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.execution_time_ms, 0);
}

// Counting Sort тесты

TEST_F(SortTest, CountingSort_SortsCorrectly) {
    CountingSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_EQ(result.sorted_array, expected);
}

TEST_F(SortTest, CountingSort_CountsComparisons) {
    CountingSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GT(result.comparisons, 0);
}

TEST_F(SortTest, CountingSort_CountsSwaps) {
    CountingSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.swaps, 0);
}

TEST_F(SortTest, CountingSort_MeasuresTime) {
    CountingSort sorter;
    auto result = sorter.sort(unsorted);
    EXPECT_GE(result.execution_time_ms, 0);
}
