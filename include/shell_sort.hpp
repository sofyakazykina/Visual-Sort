#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>

class ShellSort : public ISorter {
public:
    std::string getName() const override { return "Shell Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        int n = arr.size();
        
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                int temp = arr[i];
                int j = i;
                while (j >= gap) {
                    stats.comparisons++;
                    if (callback) callback(arr, j, j - gap);
                    
                    if (arr[j - gap] > temp) {
                        arr[j] = arr[j - gap];
                        stats.swaps++;
                        j -= gap;
                    } else {
                        break;
                    }
                }
                arr[j] = temp;
            }
        }
        
        return stats;
    }
};
