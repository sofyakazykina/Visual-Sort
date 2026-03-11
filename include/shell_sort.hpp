#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class ShellSort : public ISorter {
public:
    std::string getName() const override {
        return "Shell Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();

        int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            callback(arr, -1, -1, "gap_" + std::to_string(gap));
            
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;
                
                callback(arr, i, -1, "insert");

                while (j >= gap) {
                    result.comparisons++;
                    callback(arr, j - gap, j, "compare");
                    
                    if (arr[j - gap] > temp) {
                        arr[j] = arr[j - gap];
                        result.swaps++;
                        callback(arr, j - gap, j, "shift");
                        j -= gap;
                    } else {
                        break;
                    }
                }
                arr[j] = temp;
                callback(arr, j, -1, "place");
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
        
        int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp) {
                    result.comparisons++;
                    arr[j] = arr[j - gap];
                    result.swaps++;
                    j -= gap;
                }
                if (j >= gap) result.comparisons++;
                arr[j] = temp;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }
};
