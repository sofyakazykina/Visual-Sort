#include "console_ui.hpp"
#include <iostream>
#include <format>
#include <limits>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>

namespace ui {

void ConsoleUI::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleUI::showMenu() const {
    std::cout << "+----------------------------------------+\n";
    std::cout << "|     VISUAL SORT - Main Menu            |\n";
    std::cout << "+----------------------------------------+\n";
    std::cout << "|  1. Bubble Sort                        |\n";
    std::cout << "|  2. Insertion Sort                     |\n";
    std::cout << "|  3. Selection Sort                     |\n";
    std::cout << "|  4. Quick Sort                         |\n";
    std::cout << "|  5. Merge Sort                         |\n";
    std::cout << "|  6. Heap Sort                          |\n";
    std::cout << "|  7. Shell Sort                         |\n";
    std::cout << "|  8. Counting Sort                      |\n";
    std::cout << "|  0. Exit                               |\n";
    std::cout << "+----------------------------------------+\n";
}

void ConsoleUI::renderArray(const std::vector<int>& array,
                            int highlightIdx1, int highlightIdx2) const {
    size_t limit = std::min(array.size(), static_cast<size_t>(MAX_DISPLAY_ELEMENTS));

    std::cout << "\n";
    for (size_t i = 0; i < limit; ++i) {
        std::string bar(array[i], '#');
        if (bar.empty()) bar = ".";

        if (static_cast<int>(i) == highlightIdx1 ||
            static_cast<int>(i) == highlightIdx2) {
            std::cout << "\033[1;31m" << bar << "\033[0m";
        } else {
            std::cout << "\033[1;32m" << bar << "\033[0m";
        }
        std::cout << " [" << array[i] << "]\n";
    }

    if (array.size() > MAX_DISPLAY_ELEMENTS) {
        std::cout << "... (" << array.size() - MAX_DISPLAY_ELEMENTS
                  << " elements hidden)\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(ANIMATION_DELAY_MS));
}

std::optional<int> ConsoleUI::getArraySize() const {
    int size;
    std::cout << "\nEnter array size (" << MIN_ARRAY_SIZE << "-" << MAX_ARRAY_SIZE << "): ";

    if (std::cin >> size) {
        if (size >= MIN_ARRAY_SIZE && size <= MAX_ARRAY_SIZE) {
            return size;
        }
        std::cout << "Error: Size must be between " << MIN_ARRAY_SIZE
                  << " and " << MAX_ARRAY_SIZE << "!\n";
    } else {
        std::cout << "Error: Invalid input!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return std::nullopt;
}

std::optional<MenuOption> ConsoleUI::getAlgorithmChoice() const {
    int choice;
    std::cout << "Select algorithm (0-8): ";

    if (std::cin >> choice) {
        if (choice >= 0 && choice <= 8) {
            return static_cast<MenuOption>(choice);
        }
    }

    std::cout << "Error: Invalid choice!\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::nullopt;
}

void ConsoleUI::showStats(const std::string& algoName, const SortStats& stats,
                          const std::vector<int>& original, const std::vector<int>& sorted) const {
    std::cout << "\nChoose algorithm: " << algoName << "\n";

    std::cout << "Original:";
    for (int val : original) {
        std::cout << " " << val;
    }
    std::cout << "\n";

    std::cout << "Sorted:  ";
    for (int val : sorted) {
        std::cout << " " << val;
    }
    std::cout << "\n";

    std::cout << std::format("Comparisons: {}\n", stats.comparisons);
    std::cout << std::format("Swaps: {}\n", stats.swaps);
    std::cout << std::format("Time: {:.6} ms\n", stats.duration_ms);
}

void ConsoleUI::saveResults(const std::string& filename, const std::string& algo,
                            int size, const SortStats& stats) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << std::format("{},{},{},{},{:.4f}\n",
                            algo, size, stats.comparisons, stats.swaps, stats.duration_ms);
        std::cout << "Results saved to " << filename << "\n";
    } else {
        std::cout << "Error: Could not save to file!\n";
    }
}

void ConsoleUI::printMessage(const std::string& msg) const {
    std::cout << msg << std::endl;
}

void ConsoleUI::waitForEnter() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

}