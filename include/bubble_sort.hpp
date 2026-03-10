#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class BubbleSort : public ISorter {
public:
    std::string getName() const override {
        return "Bubble Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

        bool swapped = true;
        int n = arr.size();

        for (int i = 0; i < n - 1 && swapped; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                result.comparisons++;
                callback(arr, j, j + 1, "compare");
                
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    result.swaps++;
                    callback(arr, j, j + 1, "swap");
                    swapped = true;
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

    SortStats sortFast(std::vector<int> arr) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

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
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }
};
