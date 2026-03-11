#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class MergeSort : public ISorter {
public:
    std::string getName() const override {
        return "Merge Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();
        
        if (!arr.empty()) {
            std::vector<int> temp(arr.size());
            mergeSortRecursive(arr, temp, 0, arr.size() - 1, result, callback);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

private:
    void merge(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t mid, size_t right, SortStats& result, VisualCallback& callback) {
        size_t i = left, j = mid + 1, k = left;
        
        callback(arr, static_cast<int>(left), static_cast<int>(right), "merge_range");

        while (i <= mid && j <= right) {
            result.comparisons++;
            callback(arr, static_cast<int>(i), static_cast<int>(j), "compare");
            
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
                result.swaps++;
                callback(arr, static_cast<int>(k-1), static_cast<int>(j-1), "move");
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (size_t idx = left; idx <= right; ++idx) {
            if (arr[idx] != temp[idx]) {
                arr[idx] = temp[idx];
                callback(arr, static_cast<int>(idx), -1, "place");
            }
        }
    }

    void mergeSortRecursive(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t right, SortStats& result, VisualCallback& callback) {
        if (left >= right) return;
        
        callback(arr, static_cast<int>(left), static_cast<int>(right), "split");
        
        size_t mid = left + (right - left) / 2;
        mergeSortRecursive(arr, temp, left, mid, result, callback);
        mergeSortRecursive(arr, temp, mid + 1, right, result, callback);
        merge(arr, temp, left, mid, right, result, callback);
    }

public:
    SortStats sortFast(std::vector<int> arr) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();
        
        if (!arr.empty()) {
            std::vector<int> temp(arr.size());
            mergeSortFast(arr, temp, 0, arr.size() - 1, result);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

private:
    void mergeFast(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t mid, size_t right, SortStats& result) {
        size_t i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            result.comparisons++;
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else { temp[k++] = arr[j++]; result.swaps++; }
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];
        for (size_t idx = left; idx <= right; ++idx) arr[idx] = temp[idx];
    }

    void mergeSortFast(std::vector<int>& arr, std::vector<int>& temp, size_t left, size_t right, SortStats& result) {
        if (left >= right) return;
        size_t mid = left + (right - left) / 2;
        mergeSortFast(arr, temp, left, mid, result);
        mergeSortFast(arr, temp, mid + 1, right, result);
        mergeFast(arr, temp, left, mid, right, result);
    }
};
