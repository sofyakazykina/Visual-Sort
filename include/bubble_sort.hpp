// include/bubble_sort.hpp
#pragma once
#include "sorter_interface.hpp"
#include "logger.hpp"
#include <vector>
#include <chrono>
#include <string>

class BubbleSort : public ISorter {
public:
    std::string getName() const override {
        return "Bubble Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        Logger logger("sorter.log");
        logger.log("=== Starting " + getName() + " ===");
        logger.log("Input array size: " + std::to_string(arr.size()));

        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        int n = arr.size();
        result.comparisons = 0;
        result.swaps = 0;

        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;

            for (int j = 0; j < n - i - 1; j++) {
                result.comparisons++;

                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    result.swaps++;
                    swapped = true;
                }
            }

            if (!swapped) break;
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        logger.logResult(getName(), result);
        logger.log("=== Finished " + getName() + " ===\n");

        return result;
    }
};