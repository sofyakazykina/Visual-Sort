#include <gtest/gtest.h>
#include "bubble_sort.hpp"
#include "quick_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "selection_sort.hpp"
#include "heap_sort.hpp"
#include "shell_sort.hpp"
#include "counting_sort.hpp"
#include <vector>
#include <algorithm>

// Bubble Sort Tests
TEST(BubbleSortTest, EmptyArray) {
    BubbleSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(result.comparisons, 0);
    EXPECT_EQ(result.swaps, 0);
}

TEST(BubbleSortTest, SortedArray) {
    BubbleSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_EQ(result.comparisons, 10);  // n*(n-1)/2
}

TEST(BubbleSortTest, ReverseArray) {
    BubbleSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_GT(result.swaps, 0);
}

TEST(BubbleSortTest, SingleElement) {
    BubbleSort sorter;
    std::vector<int> data = {42};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{42}));
}

TEST(BubbleSortTest, WithDuplicates) {
    BubbleSort sorter;
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    std::vector<int> expected = {1, 1, 2, 3, 4, 5, 5, 6, 9};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(BubbleSortTest, NegativeNumbers) {
    BubbleSort sorter;
    std::vector<int> data = {-5, 10, -3, 0, 7, -1};
    std::vector<int> expected = {-5, -3, -1, 0, 7, 10};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// Quick Sort Tests
TEST(QuickSortTest, EmptyArray) {
    QuickSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
}

TEST(QuickSortTest, RandomArray) {
    QuickSort sorter;
    std::vector<int> data = {64, 34, 25, 12, 22};
    auto result = sorter.sort(data, nullptr);
    std::vector<int> expected = {12, 22, 25, 34, 64};
    EXPECT_EQ(data, expected);
}

TEST(QuickSortTest, AlreadySorted) {
    QuickSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, ReverseArray) {
    QuickSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(QuickSortTest, WithDuplicates) {
    QuickSort sorter;
    std::vector<int> data = {3, 1, 4, 1, 5};
    std::vector<int> expected = {1, 1, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(QuickSortTest, NegativeNumbers) {
    QuickSort sorter;
    std::vector<int> data = {-10, 5, -3, 0, 8};
    std::vector<int> expected = {-10, -3, 0, 5, 8};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}


// Insertion Sort Tests
TEST(InsertionSortTest, EmptyArray) {
    InsertionSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
}

TEST(InsertionSortTest, SmallArray) {
    InsertionSort sorter;
    std::vector<int> data = {3, 1, 2};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3}));
}

TEST(InsertionSortTest, AlreadySorted) {
    InsertionSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(InsertionSortTest, ReverseArray) {
    InsertionSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(InsertionSortTest, WithDuplicates) {
    InsertionSort sorter;
    std::vector<int> data = {2, 2, 1, 1};
    std::vector<int> expected = {1, 1, 2, 2};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(InsertionSortTest, NegativeNumbers) {
    InsertionSort sorter;
    std::vector<int> data = {-5, 10, -3, 0, 7};
    std::vector<int> expected = {-5, -3, 0, 7, 10};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// Merge Sort Tests
TEST(MergeSortTest, EmptyArray) {
    MergeSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
}

TEST(MergeSortTest, RandomArray) {
    MergeSort sorter;
    std::vector<int> data = {38, 27, 43, 3, 9, 82, 10};
    auto result = sorter.sort(data, nullptr);
    std::vector<int> expected = {3, 9, 10, 27, 38, 43, 82};
    EXPECT_EQ(data, expected);
}

TEST(MergeSortTest, AlreadySorted) {
    MergeSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(MergeSortTest, ReverseArray) {
    MergeSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(MergeSortTest, WithDuplicates) {
    MergeSort sorter;
    std::vector<int> data = {4, 2, 4, 1, 2};
    std::vector<int> expected = {1, 2, 2, 4, 4};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(MergeSortTest, NegativeNumbers) {
    MergeSort sorter;
    std::vector<int> data = {-8, 15, -3, 0, 22};
    std::vector<int> expected = {-8, -3, 0, 15, 22};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// Selection Sort Tests

TEST(SelectionSortTest, EmptyArray) {
    SelectionSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(result.comparisons, 0);
}

TEST(SelectionSortTest, SingleElement) {
    SelectionSort sorter;
    std::vector<int> data = {42};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{42}));
}

TEST(SelectionSortTest, SortedArray) {
    SelectionSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(SelectionSortTest, ReverseArray) {
    SelectionSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
    EXPECT_GT(result.swaps, 0);
}

TEST(SelectionSortTest, WithDuplicates) {
    SelectionSort sorter;
    std::vector<int> data = {3, 1, 4, 1, 5};
    std::vector<int> expected = {1, 1, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(SelectionSortTest, NegativeNumbers) {
    SelectionSort sorter;
    std::vector<int> data = {-5, 10, -3, 0, 7};
    std::vector<int> expected = {-5, -3, 0, 7, 10};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// Heap Sort Tests

TEST(HeapSortTest, EmptyArray) {
    HeapSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
}

TEST(HeapSortTest, SingleElement) {
    HeapSort sorter;
    std::vector<int> data = {42};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{42}));
}

TEST(HeapSortTest, SortedArray) {
    HeapSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(HeapSortTest, ReverseArray) {
    HeapSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(HeapSortTest, WithDuplicates) {
    HeapSort sorter;
    std::vector<int> data = {7, 3, 7, 1, 3};
    std::vector<int> expected = {1, 3, 3, 7, 7};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(HeapSortTest, NegativeNumbers) {
    HeapSort sorter;
    std::vector<int> data = {-10, 5, -3, 0, 8};
    std::vector<int> expected = {-10, -3, 0, 5, 8};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// Shell Sort Tests

TEST(ShellSortTest, EmptyArray) {
    ShellSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
}

TEST(ShellSortTest, SingleElement) {
    ShellSort sorter;
    std::vector<int> data = {42};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{42}));
}

TEST(ShellSortTest, SortedArray) {
    ShellSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(ShellSortTest, ReverseArray) {
    ShellSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(ShellSortTest, WithDuplicates) {
    ShellSort sorter;
    std::vector<int> data = {4, 2, 4, 1, 2};
    std::vector<int> expected = {1, 2, 2, 4, 4};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(ShellSortTest, NegativeNumbers) {
    ShellSort sorter;
    std::vector<int> data = {-8, 15, -3, 0, 22};
    std::vector<int> expected = {-8, -3, 0, 15, 22};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// Counting Sort Tests

TEST(CountingSortTest, EmptyArray) {
    CountingSort sorter;
    std::vector<int> data = {};
    auto result = sorter.sort(data, nullptr);
    EXPECT_TRUE(data.empty());
}

TEST(CountingSortTest, SingleElement) {
    CountingSort sorter;
    std::vector<int> data = {42};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{42}));
}

TEST(CountingSortTest, SortedArray) {
    CountingSort sorter;
    std::vector<int> data = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(CountingSortTest, ReverseArray) {
    CountingSort sorter;
    std::vector<int> data = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(CountingSortTest, WithDuplicates) {
    CountingSort sorter;
    std::vector<int> data = {3, 1, 4, 1, 5, 3};
    std::vector<int> expected = {1, 1, 3, 3, 4, 5};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(CountingSortTest, NegativeNumbers) {
    CountingSort sorter;
    std::vector<int> data = {-10, 5, -3, 0, 8, -5};
    std::vector<int> expected = {-10, -5, -3, 0, 5, 8};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

TEST(CountingSortTest, LargeRange) {
    CountingSort sorter;
    std::vector<int> data = {100, -100, 50, -50, 0};
    std::vector<int> expected = {-100, -50, 0, 50, 100};
    auto result = sorter.sort(data, nullptr);
    EXPECT_EQ(data, expected);
}

// General Tests
TEST(GeneralTest, AllSortersProduceSortedOutput) {
    std::vector<int> original = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    BubbleSort bubble;
    QuickSort quick;
    InsertionSort insertion;
    MergeSort merge;
    SelectionSort selection;
    HeapSort heap;
    ShellSort shell;
    CountingSort counting;
    
    std::vector<int> d1 = original; bubble.sort(d1, nullptr);
    std::vector<int> d2 = original; quick.sort(d2, nullptr);
    std::vector<int> d3 = original; insertion.sort(d3, nullptr);
    std::vector<int> d4 = original; merge.sort(d4, nullptr);
    std::vector<int> d5 = original; selection.sort(d5, nullptr);
    std::vector<int> d6 = original; heap.sort(d6, nullptr);
    std::vector<int> d7 = original; shell.sort(d7, nullptr);
    std::vector<int> d8 = original; counting.sort(d8, nullptr);
    
    EXPECT_EQ(d1, expected); EXPECT_EQ(d2, expected);
    EXPECT_EQ(d3, expected); EXPECT_EQ(d4, expected);
    EXPECT_EQ(d5, expected); EXPECT_EQ(d6, expected);
    EXPECT_EQ(d7, expected); EXPECT_EQ(d8, expected);
}

TEST(GeneralTest, MetricsAreNonNegative) {
    std::vector<int> data = {5, 2, 8, 1, 9};
    
    BubbleSort bubble;
    auto r1 = bubble.sort(data, nullptr);
    EXPECT_GE(r1.comparisons, 0);
    EXPECT_GE(r1.swaps, 0);
    EXPECT_GE(r1.execution_time_ms, 0.0);
    
    QuickSort quick;
    auto r2 = quick.sort(data, nullptr);
    EXPECT_GE(r2.comparisons, 0);
    EXPECT_GE(r2.swaps, 0);
}

TEST(GeneralTest, OutputSizeMatchesInput) {
    std::vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};
    size_t originalSize = data.size();
    
    MergeSort sorter;
    sorter.sort(data, nullptr);
    
    EXPECT_EQ(data.size(), originalSize);
}
