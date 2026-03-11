#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class QuickSort : public ISorter {
public:
    std::string getName() const override {
        return "Quick Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();
        
        quickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, result, callback);
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

private:
    int partition(std::vector<int>& arr, int low, int high, SortStats& result, VisualCallback& callback) {
        int pivot = arr[high];
        int i = low - 1;
        
        callback(arr, high, -1, "pivot");

        for (int j = low; j < high; ++j) {
            result.comparisons++;
            callback(arr, j, high, "compare");
            
            if (arr[j] < pivot) {
                ++i;
                if (i != j) {
                    std::swap(arr[i], arr[j]);
                    result.swaps++;
                    callback(arr, i, j, "swap");
                }
            }
        }
        
        if (i + 1 != high) {
            std::swap(arr[i + 1], arr[high]);
            result.swaps++;
            callback(arr, i + 1, high, "pivot_place");
        }
        return i + 1;
    }

    void quickSortRecursive(std::vector<int>& arr, int low, int high, SortStats& result, VisualCallback& callback) {
        if (low < high) {
            callback(arr, low, high, "partition");
            int pi = partition(arr, low, high, result, callback);
            quickSortRecursive(arr, low, pi - 1, result, callback);
            quickSortRecursive(arr, pi + 1, high, result, callback);
        }
    }

public:
    SortStats sortFast(std::vector<int> arr) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();
        
        quickSortFast(arr, 0, static_cast<int>(arr.size()) - 1, result);
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

private:
    int partitionFast(std::vector<int>& arr, int low, int high, SortStats& result) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            result.comparisons++;
            if (arr[j] < pivot) {
                ++i;
                if (i != j) {
                    std::swap(arr[i], arr[j]);
                    result.swaps++;
                }
            }
        }
        if (i + 1 != high) {
            std::swap(arr[i + 1], arr[high]);
            result.swaps++;
        }
        return i + 1;
    }

    void quickSortFast(std::vector<int>& arr, int low, int high, SortStats& result) {
        if (low < high) {
            int pi = partitionFast(arr, low, high, result);
            quickSortFast(arr, low, pi - 1, result);
            quickSortFast(arr, pi + 1, high, result);
        }
    }
};
