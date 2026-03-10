#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "sorter.hpp"
#include "bubble_sort.hpp"
#include "insertion_sort.hpp"
#include "selection_sort.hpp"
#include "quick_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "shell_sort.hpp"
#include "counting_sort.hpp"

class ConsoleUI {
public:
    void showMenu() {
        int choice = -1;
        while (choice != 0) {
            std::cout << "\n=== Visual Sort ===" << std::endl;
            std::cout << "1. Bubble Sort" << std::endl;
            std::cout << "2. Insertion Sort" << std::endl;
            std::cout << "3. Selection Sort" << std::endl;
            std::cout << "4. Quick Sort" << std::endl;
            std::cout << "5. Merge Sort" << std::endl;
            std::cout << "6. Heap Sort" << std::endl;
            std::cout << "7. Shell Sort" << std::endl;
            std::cout << "8. Counting Sort" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "Choose algorithm: ";
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input!" << std::endl;
                continue;
            }
            
            if (choice >= 1 && choice <= 8) {
                runSort(choice);
            } else if (choice != 0) {
                std::cout << "Invalid choice!" << std::endl;
            }
        }
        std::cout << "Goodbye!" << std::endl;
    }
    
private:
    void runSort(int choice) {
        std::vector<int> data = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
        
        std::cout << "Original: ";
        for (int n : data) std::cout << n << " ";
        std::cout << std::endl;
        
        SortResult result;
        
        switch (choice) {
            case 1: result = BubbleSort().sort(data); break;
            case 2: result = InsertionSort().sort(data); break;
            case 3: result = SelectionSort().sort(data); break;
            case 4: result = QuickSort().sort(data); break;
            case 5: result = MergeSort().sort(data); break;
            case 6: result = HeapSort().sort(data); break;
            case 7: result = ShellSort().sort(data); break;
            case 8: result = CountingSort().sort(data); break;
        }
        
        std::cout << "Sorted:   ";
        for (int n : result.sorted_array) std::cout << n << " ";
        std::cout << std::endl;
        std::cout << "Comparisons: " << result.comparisons << std::endl;
        std::cout << "Swaps: " << result.swaps << std::endl;
        std::cout << "Time: " << result.execution_time_ms << " ms" << std::endl;
    }
};
