#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class InsertionSort : public ISorter {
public:
    std::string getName() const override {
        return "Insertion Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = static_cast<int>(i) - 1;

            callback(arr, static_cast<int>(i), -1, "pick");

            while (j >= 0) {
                result.comparisons++;
                callback(arr, j, static_cast<int>(i), "compare");
                
                if (arr[j] > key) {
                    arr[j + 1] = arr[j];
                    result.swaps++;
                    callback(arr, j, j + 1, "shift");
                    j--;
                } else {
                    break;
                }
            }
            arr[j + 1] = key;
            callback(arr, j + 1, -1, "insert");
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

    SortStats sortFast(std::vector<int> arr) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = static_cast<int>(i) - 1;
            while (j >= 0 && arr[j] > key) {
                result.comparisons++;
                arr[j + 1] = arr[j];
                result.swaps++;
                j--;
            }
            if (j >= 0) result.comparisons++;
            arr[j + 1] = key;
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }
};
