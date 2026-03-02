#pragma once
#include "sorter_interface.hpp"
#include "logger.hpp"
#include <vector>
#include <chrono>
#include <string>

class InsertionSort : public ISorter {
public:
    std::string getName() const override {
        return "Insertion Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        Logger logger("sorter.log");
        logger.log("=== Starting " + getName() + " ===");

        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        for (size_t i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0) {
                result.comparisons++;
                if (arr[j] > key) {
                    arr[j + 1] = arr[j];
                    result.swaps++;
                    j--;
                } else {
                    break;
                }
            }
            arr[j + 1] = key;
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        logger.logResult(getName(), result);
        logger.log("=== Finished " + getName() + " ===\n");

        return result;
    }
};