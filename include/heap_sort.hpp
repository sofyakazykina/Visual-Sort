#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>

class HeapSort : public ISorter {
public:
    std::string getName() const override {
        return "Heap Sort";
    }

    SortStats sort(std::vector<int>& arr, VisualCallback callback) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();
        
        if (!arr.empty()) {
            heapSortInternal(arr, result, callback);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

private:
    void heapify(std::vector<int>& arr, size_t n, size_t i, SortStats& result, VisualCallback& callback) {
        size_t largest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < n) {
            result.comparisons++;
            callback(arr, static_cast<int>(left), static_cast<int>(largest), "compare");
            if (arr[left] > arr[largest]) largest = left;
        }

        if (right < n) {
            result.comparisons++;
            callback(arr, static_cast<int>(right), static_cast<int>(largest), "compare");
            if (arr[right] > arr[largest]) largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            result.swaps++;
            callback(arr, static_cast<int>(i), static_cast<int>(largest), "swap");
            heapify(arr, n, largest, result, callback);
        }
    }

    void heapSortInternal(std::vector<int>& arr, SortStats& result, VisualCallback& callback) {
        size_t n = arr.size();

        callback(arr, -1, -1, "build_heap");
        for (int64_t i = static_cast<int64_t>(n) / 2 - 1; i >= 0; --i) {
            heapify(arr, n, static_cast<size_t>(i), result, callback);
        }

        for (size_t i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            result.swaps++;
            callback(arr, 0, static_cast<int>(i), "extract");
            heapify(arr, i, 0, result, callback);
        }
    }

public:
    SortStats sortFast(std::vector<int> arr) override {
        SortStats result;
        auto start = std::chrono::high_resolution_clock::now();
        
        if (!arr.empty()) heapSortFast(arr, result);
        
        auto end = std::chrono::high_resolution_clock::now();
        result.duration_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;
        return result;
    }

private:
    void heapifyFast(std::vector<int>& arr, size_t n, size_t i, SortStats& result) {
        size_t largest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < n) { result.comparisons++; if (arr[left] > arr[largest]) largest = left; }
        if (right < n) { result.comparisons++; if (arr[right] > arr[largest]) largest = right; }
        if (largest != i) { std::swap(arr[i], arr[largest]); result.swaps++; heapifyFast(arr, n, largest, result); }
    }

    void heapSortFast(std::vector<int>& arr, SortStats& result) {
        size_t n = arr.size();
        for (int64_t i = static_cast<int64_t>(n) / 2 - 1; i >= 0; --i) heapifyFast(arr, n, static_cast<size_t>(i), result);
        for (size_t i = n - 1; i > 0; --i) { std::swap(arr[0], arr[i]); result.swaps++; heapifyFast(arr, i, 0, result); }
    }
};
