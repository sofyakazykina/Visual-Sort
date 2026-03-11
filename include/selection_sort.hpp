#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class SelectionSort : public ISorter {
public:
    std::string getName() const override {
        return "Selection Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < arr.size() - 1; i++) {
            size_t min_idx = i;
            callback(arr, static_cast<int>(i), -1, "search");

            for (size_t j = i + 1; j < arr.size(); j++) {
                result.comparisons++;
                callback(arr, static_cast<int>(j), static_cast<int>(min_idx), "compare");
                
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                    callback(arr, static_cast<int>(min_idx), -1, "new_min");
                }
            }

            if (min_idx != i) {
                std::swap(arr[i], arr[min_idx]);
                result.swaps++;
                callback(arr, static_cast<int>(i), static_cast<int>(min_idx), "swap");
            }
            callback(arr, static_cast<int>(i), -1, "sorted");
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

    SortStats sortFast(std::vector<int> arr) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < arr.size() - 1; i++) {
            size_t min_idx = i;
            for (size_t j = i + 1; j < arr.size(); j++) {
                result.comparisons++;
                if (arr[j] < arr[min_idx]) min_idx = j;
            }
            if (min_idx != i) {
                std::swap(arr[i], arr[min_idx]);
                result.swaps++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }
};
