#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include "sorter.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "shell_sort.hpp"
#include "counting_sort.hpp"

// Вспомогательные функции

// Проверка, что массив отсортирован по неубыванию
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}
