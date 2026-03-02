#pragma once
#include "sorter_interface.hpp"
#include "logger.hpp"
#include <vector>
#include <chrono>
#include <string>

class SelectionSort : public ISorter {
public:
    std::string getName() const override {
        return "Selection Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        Logger logger("sorter.log");
        logger.log("=== Starting " + getName() + " ===");

        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        for (size_t i = 0; i < arr.size() - 1; i++) {
            size_t min_idx = i;

            for (size_t j = i + 1; j < arr.size(); j++) {
                result.comparisons++;
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }

            if (min_idx != i) {
                std::swap(arr[i], arr[min_idx]);
                result.swaps++;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        logger.logResult(getName(), result);
        logger.log("=== Finished " + getName() + " ===\n");

        return result;
    }
};