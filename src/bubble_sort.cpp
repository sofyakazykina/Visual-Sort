#include <iostream>
#include <vector>
#include "C:/Users/User/CLionProjects/untitled/Visual-Sort/include/bubble_sort.hpp"
int main() {
    int number_of_elements;

    std::cout << "Enter a number of elements: ";

    std::cin >> number_of_elements;

    std::vector<int> array_of_elements(number_of_elements);

    std::cout << "Enter an array of elements (separated by a space): ";

    for (int i = 0; i < number_of_elements; ++i) {
        std::cin >> array_of_elements[i];
    }

    bubble_sort(array_of_elements);

    std::cout << "Sorted by bubble elements: ";

    for (int i = 0; i < number_of_elements; ++i) {
        std::cout << array_of_elements[i] << " ";
    }
}