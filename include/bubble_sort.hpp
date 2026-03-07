// include/bubble_sort.hpp
#pragma once
#include "sorter.hpp"
#include "logger.hpp"
#include <vector>
inline void bubble_sort(std::vector<int>& array_of_elements) {
    int number_of_elements = array_of_elements.size();
    bool swapped;
    for (int i = 0; i < number_of_elements - 1; ++i) {
        swapped = false;
        for (int j = 0; j < number_of_elements - i - 1; ++j) {
            if (array_of_elements[j] > array_of_elements[j + 1]) {
                int temp = array_of_elements[j];
                array_of_elements[j] = array_of_elements[j + 1];
                array_of_elements[j + 1] = temp;
                swapped = true;ls -la src/main.cpp
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.execution_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
        result.sorted_array = arr;

        // // logger.logResult(getName(), result);
        logger.log("=== Finished " + getName() + " ===\n");

        return result;
    }
}
#endif