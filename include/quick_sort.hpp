#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

class QuickSort : public ISorter {
public:
    std::string getName() const override {
        return "Quick Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;
        quickSortRecursive(arr, 0, arr.size() - 1, result);

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        return result;
    }

private:
    int64_t partition(std::vector<int>& vec, int64_t low, int64_t high, SortResult& result) {
        int pivot = vec[high];
        int64_t i = low - 1;

        for (int64_t j = low; j < high; ++j) {
            result.comparisons++;
            if (vec[j] < pivot) {
                ++i;
                std::swap(vec[i], vec[j]);
                result.swaps++;
            }
        }
        std::swap(vec[i + 1], vec[high]);
        result.swaps++;
        return i + 1;
    }

    void quickSortRecursive(std::vector<int>& vec, int64_t low, int64_t high, SortResult& result) {
        if (low < high) {
            int64_t pi = partition(vec, low, high, result);
            quickSortRecursive(vec, low, pi - 1, result);
            quickSortRecursive(vec, pi + 1, high, result);
        }
    }
};