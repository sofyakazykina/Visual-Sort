#pragma once
#include "sorter.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <limits>

class CountingSort : public ISorter {
public:
    std::string getName() const override {
        return "Counting Sort";
    }

    SortResult sort(std::vector<int> arr) override {
        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        if (!arr.empty()) {
            int min_val = *std::min_element(arr.begin(), arr.end());
            int max_val = *std::max_element(arr.begin(), arr.end());

            int offset = (min_val < 0) ? -min_val : 0;
            int range = max_val - min_val + 1;

            std::vector<size_t> count(range, 0);

            for (int val : arr) {
                count[val + offset]++;
                result.comparisons++;
            }

            for (size_t i = 1; i < count.size(); i++) {
                count[i] += count[i - 1];
                result.comparisons++;
            }

            std::vector<int> output(arr.size());
            for (int64_t i = static_cast<int64_t>(arr.size()) - 1; i >= 0; --i) {
                int val = arr[i];
                output[count[val + offset] - 1] = val;
                count[val + offset]--;
                result.swaps++;
            }

            arr = std::move(output);
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        return result;
    }
};