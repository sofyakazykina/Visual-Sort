#pragma once
#include "sorter.hpp"
#include "logger.hpp"
#include <vector>
#include <string>
#include <chrono>

class BubbleSort : public ISorter {
public:
    std::string getName() const override {
        return "Bubble Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        bool swapped = true;
        int n = arr.size();

        for (int i = 0; i < n - 1 && swapped; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                result.comparisons++;
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    result.swaps++;
                    swapped = true;
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        return result;
    }
};