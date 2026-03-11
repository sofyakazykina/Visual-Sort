#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>

class BubbleSort : public ISorter {
public:
    std::string getName() const override {
        return "Bubble Sort";
    }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        int n = arr.size();
        
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                stats.comparisons++;
                
                // Callback для анимации
                if (callback) callback(arr, j, j + 1);
                
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    stats.swaps++;
                }
            }
        }
        
        return stats;
    }
};
