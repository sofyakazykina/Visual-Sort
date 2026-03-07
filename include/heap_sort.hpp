#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

class HeapSort : public ISorter {
public:
    std::string getName() const override {
        return "Heap Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        if (!arr.empty()) {
            heapSortInternal(arr, result);
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        return result;
    }

private:
    void heapify(std::vector<int>& vec, size_t n, size_t i, SortResult& result) {
        size_t largest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < n) {
            result.comparisons++;
            if (vec[left] > vec[largest]) {
                largest = left;
            }
        }

        if (right < n) {
            result.comparisons++;
            if (vec[right] > vec[largest]) {
                largest = right;
            }
        }

        if (largest != i) {
            std::swap(vec[i], vec[largest]);
            result.swaps++;
            heapify(vec, n, largest, result);
        }
    }

    void heapSortInternal(std::vector<int>& vec, SortResult& result) {
        size_t n = vec.size();

        for (int64_t i = static_cast<int64_t>(n) / 2 - 1; i >= 0; --i) {
            heapify(vec, n, static_cast<size_t>(i), result);
        }

        for (size_t i = n - 1; i > 0; --i) {
            std::swap(vec[0], vec[i]);
            result.swaps++;
            heapify(vec, i, 0, result);
        }
    }
};