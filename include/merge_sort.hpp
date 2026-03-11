#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>

class MergeSort : public ISorter {
public:
    std::string getName() const override { return "Merge Sort"; }

    SortStats sort(std::vector<int>& arr, StepCallback callback) override {
        SortStats stats;
        if (!arr.empty()) mergeSort(arr, 0, arr.size() - 1, stats, callback);
        return stats;
    }

private:
    void mergeSort(std::vector<int>& arr, int left, int right, SortStats& stats, StepCallback callback) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, stats, callback);
            mergeSort(arr, mid + 1, right, stats, callback);
            merge(arr, left, mid, right, stats, callback);
        }
    }

    void merge(std::vector<int>& arr, int left, int mid, int right, SortStats& stats, StepCallback callback) {
        std::vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
        std::vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
        
        int i = 0, j = 0, k = left;
        while (i < L.size() && j < R.size()) {
            stats.comparisons++;
            if (callback) callback(arr, left + i, mid + 1 + j);
            
            if (L[i] <= R[j]) arr[k++] = L[i++];
            else arr[k++] = R[j++];
            stats.swaps++;
        }
        while (i < L.size()) arr[k++] = L[i++];
        while (j < R.size()) arr[k++] = R[j++];
    }
};
