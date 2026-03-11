#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <algorithm>

class SelectionSort : public ISorter {
public:
    std::string getName() const override { return "Selection Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        int n = arr.size();
        
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                stats.comparisons++;
                if (callback) callback(arr, minIdx, j);
                if (arr[j] < arr[minIdx]) minIdx = j;
            }
            if (minIdx != i) {
                std::swap(arr[i], arr[minIdx]);
                stats.swaps++;
            }
        }
        
        return stats;
    }
};
