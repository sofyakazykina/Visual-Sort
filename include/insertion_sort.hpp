#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>

class InsertionSort : public ISorter {
public:
    std::string getName() const override { return "Insertion Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        int n = arr.size();
        
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            
            while (j >= 0) {
                stats.comparisons++;
                if (callback) callback(arr, j, i);
                
                if (arr[j] > key) {
                    arr[j + 1] = arr[j];
                    stats.swaps++;
                    j--;
                } else {
                    break;
                }
            }
            arr[j + 1] = key;
        }
        
        return stats;
    }
};
