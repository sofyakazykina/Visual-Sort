#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP
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
                swapped = true;
            }
        }
        if (not swapped) {
            break;
        }
    }
}
#endif