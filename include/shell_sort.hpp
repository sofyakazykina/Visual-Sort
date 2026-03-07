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

    SortResult sort(std::vector<int> arr) override {
        SortResult result;
        auto start = std::chrono::high_resolution_clock::now();

        result.comparisons = 0;
        result.swaps = 0;

        // Shell Sort с последовательностью gap = n/2, n/4, ..., 1
        int n = arr.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Insertion Sort с шагом gap
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;

                // Сдвигаем элементы, пока не найдём правильное место
                while (j >= gap) {
                    result.comparisons++;
                    if (arr[j - gap] > temp) {
                        arr[j] = arr[j - gap];
                        result.swaps++;
                        j -= gap;
                    } else {
                        break;
                    }
                }
                arr[j] = temp;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        return result;
    }
};
