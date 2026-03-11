#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <algorithm>

class CountingSort : public ISorter {
public:
    std::string getName() const override { return "Counting Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        if (arr.empty()) return stats;
        
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;
        
        std::vector<int> count(range, 0);
        std::vector<int> output(arr.size());
        
        for (int i = 0; i < arr.size(); ++i) {
            count[arr[i] - minVal]++;
            stats.comparisons++;
        }
        
        for (int i = 1; i < range; ++i)
            count[i] += count[i - 1];
        
        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
            stats.swaps++;
            if (callback) callback(arr, i, -1);
        }
        
        arr = output;
        return stats;
    }
};
