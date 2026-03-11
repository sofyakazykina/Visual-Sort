#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>

class QuickSort : public ISorter {
public:
    std::string getName() const override { return "Quick Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        quickSort(arr, 0, arr.size() - 1, stats, callback);
        return stats;
    }

private:
    void quickSort(std::vector<int>& arr, int low, int high, SortStats& stats, StepCallback callback) {
        if (low < high) {
            int pi = partition(arr, low, high, stats, callback);
            quickSort(arr, low, pi - 1, stats, callback);
            quickSort(arr, pi + 1, high, stats, callback);
        }
    }

    int partition(std::vector<int>& arr, int low, int high, SortStats& stats, StepCallback callback) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; ++j) {
            stats.comparisons++;
            if (callback) callback(arr, j, high);
            
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                stats.swaps++;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        stats.swaps++;
        return i + 1;
    }
};
