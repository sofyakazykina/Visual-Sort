#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>

class HeapSort : public ISorter {
public:
    std::string getName() const override { return "Heap Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        int n = arr.size();
        
        for (int i = n / 2 - 1; i >= 0; --i)
            heapify(arr, n, i, stats, callback);
        
        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            stats.swaps++;
            heapify(arr, i, 0, stats, callback);
        }
        
        return stats;
    }

private:
    void heapify(std::vector<int>& arr, int n, int i, SortStats& stats, StepCallback callback) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        
        if (l < n) {
            stats.comparisons++;
            if (callback) callback(arr, i, l);
            if (arr[l] > arr[largest]) largest = l;
        }
        if (r < n) {
            stats.comparisons++;
            if (callback) callback(arr, i, r);
            if (arr[r] > arr[largest]) largest = r;
        }
        
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            stats.swaps++;
            heapify(arr, n, largest, stats, callback);
        }
    }
};
