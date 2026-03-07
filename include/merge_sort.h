#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

class MergeSort : public ISorter {
public:
    std::string getName() const override {
        return "Merge Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        if (!arr.empty()) {
            std::vector<int> temp(arr.size());
            mergeSortRecursive(arr, temp, 0, arr.size() - 1, result);
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        return result;
    }

private:
    void merge(std::vector<int>& vec, std::vector<int>& temp,
               size_t left, size_t mid, size_t right, SortResult& result) {
        size_t i = left;
        size_t j = mid + 1;
        size_t k = left;

        while (i <= mid && j <= right) {
            result.comparisons++;
            if (vec[i] <= vec[j]) {
                temp[k++] = vec[i++];
            } else {
                temp[k++] = vec[j++];
                result.swaps++;
            }
        }

        while (i <= mid) {
            temp[k++] = vec[i++];
        }

        while (j <= right) {
            temp[k++] = vec[j++];
        }

        for (size_t idx = left; idx <= right; ++idx) {
            vec[idx] = temp[idx];
        }
    }

    void mergeSortRecursive(std::vector<int>& vec, std::vector<int>& temp,
                            size_t left, size_t right, SortResult& result) {
        if (left >= right) return;

        size_t mid = left + (right - left) / 2;
        mergeSortRecursive(vec, temp, left, mid, result);
        mergeSortRecursive(vec, temp, mid + 1, right, result);
        merge(vec, temp, left, mid, right, result);
    }
};