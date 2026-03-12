#include "console_ui.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <stdexcept>

namespace ui {


    void ConsoleUI::clearScreen() const {
        std::cout << "\033[2J\033[H" << std::flush;
    }

    void ConsoleUI::showMenu() const {
        std::cout << "\n=== Visual Sort ===\n\n";
        std::cout << "1. Bubble Sort\n";
        std::cout << "2. Insertion Sort\n";
        std::cout << "3. Selection Sort\n";
        std::cout << "4. Quick Sort\n";
        std::cout << "5. Merge Sort\n";
        std::cout << "6. Heap Sort\n";
        std::cout << "7. Shell Sort\n";
        std::cout << "8. Counting Sort\n";
        std::cout << "0. Exit\n\n";
    }

    void ConsoleUI::renderArray(const std::vector<int>& array,
                                int highlightIdx1, int highlightIdx2) const {
        if (array.empty()) return;

        int maxVal = *std::max_element(array.begin(), array.end());
        if (maxVal == 0) maxVal = 1;

        std::cout << "\n";
        for (size_t i = 0; i < array.size() && i < MAX_DISPLAY_ELEMENTS; ++i) {
            if (static_cast<int>(i) == highlightIdx1 ||
                static_cast<int>(i) == highlightIdx2) {
                std::cout << "\033[1;31m";
            } else {
                std::cout << "\033[1;32m";
            }

            int barLen = (array[i] * 20) / maxVal;
            if (barLen < 1) barLen = 1;
            std::cout << std::string(barLen, '#');

            std::cout << "\033[0m ";
        }
        std::cout << "\n";

        for (size_t i = 0; i < array.size() && i < MAX_DISPLAY_ELEMENTS; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(ANIMATION_DELAY_MS));
    }

    std::optional<int> ConsoleUI::getArraySize() const {
        std::cout << "Enter array size (" << MIN_ARRAY_SIZE << "-"
                  << MAX_ARRAY_SIZE << "): ";

        int size;
        if (!(std::cin >> size)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::runtime_error("Invalid input: expected integer for array size");
        }

        if (size < MIN_ARRAY_SIZE || size > MAX_ARRAY_SIZE) {
            throw std::out_of_range("Array size must be between " +
                                    std::to_string(MIN_ARRAY_SIZE) + " and " +
                                    std::to_string(MAX_ARRAY_SIZE));
        }

        std::cin.ignore(10000, '\n');
        return size;
    }

    std::optional<MenuOption> ConsoleUI::getAlgorithmChoice() const {
        std::cout << "Choose algorithm (0-8): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw std::runtime_error("Invalid input: expected integer for algorithm choice");
        }

        if (choice < 0 || choice > 8) {
            throw std::out_of_range("Algorithm choice must be between 0 and 8");
        }

        std::cin.ignore(10000, '\n');
        return static_cast<MenuOption>(choice);
    }

    void ConsoleUI::showStats(const std::string& algoName, const SortStats& stats,
                              const std::vector<int>& original,
                              const std::vector<int>& sorted) const {
        std::cout << "\n=== Results ===\n";
        std::cout << "Algorithm: " << algoName << "\n";
        std::cout << "Array size: " << original.size() << "\n";
        std::cout << "Comparisons: " << stats.comparisons << "\n";
        std::cout << "Swaps: " << stats.swaps << "\n";
        std::cout << "Time: " << stats.duration_ms << " ms\n\n";

        std::cout << "Original: ";
        for (int n : original) std::cout << n << " ";
        std::cout << "\n";

        std::cout << "Sorted:   ";
        for (int n : sorted) std::cout << n << " ";
        std::cout << "\n\n";
    }

    void ConsoleUI::saveResults(const std::string& filename, const std::string& algo,
                                int size, const SortStats& stats) const {
        try {
            std::ofstream file(filename, std::ios::app);
            if (!file.is_open()) {
                throw std::runtime_error("Cannot open file: " + filename);
            }
            file << algo << "," << size << "," << stats.comparisons << ","
                 << stats.swaps << "," << stats.duration_ms << "\n";
            file.close();
        } catch (const std::exception& e) {
            std::cerr << "Warning: Could not save results: " << e.what() << "\n";
        }
    }

    void ConsoleUI::printMessage(const std::string& msg) const {
        std::cout << msg << std::endl;
    }

}
