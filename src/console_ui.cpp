#include "console_ui.hpp"
#include <iostream>
#include <format>
#include <limits>
#include <thread>
#include <chrono>
#include <fstream>

namespace ui {

void ConsoleUI::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleUI::showMenu() const {
    std::cout << "|     VISUAL SORT - Main Menu            |\n";
    std::cout << "+----------------------------------------+\n";
    std::cout << "|  1. Bubble Sort                        |\n";
    std::cout << "|  2. Insertion Sort                     |\n";
    std::cout << "|  3. Selection Sort                     |\n";
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
    std::cout << "Select algorithm (0-3): ";

    if (std::cin >> choice) {
        if (choice >= 0 && choice <= 3) {
            return static_cast<MenuOption>(choice);
        }
    }

    std::cout << "Error: Invalid choice!\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::nullopt;
}

void ConsoleUI::showStats(const std::string& algoName, const SortStats& stats) const {
    std::cout << "|        Sorting Complete!               |\n";
    std::cout << "+----------------------------------------+\n";
    std::cout << "| Algorithm: " << std::left << algoName << std::string(29 - algoName.length(), ' ') << "|\n";
    std::cout << "| Comparisons: " << std::format("{:<27}", stats.comparisons) << "|\n";
    std::cout << "| Time: " << std::format("{:.4f} ms{:<20}", stats.duration_ms, "") << "|\n";
    std::cout << "| Complexity: O(n^2)                     |\n";
    std::cout << "+----------------------------------------+\n";
}

void ConsoleUI::saveResults(const std::string& filename, const std::string& algo,
                            int size, const SortStats& stats) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << std::format("{},{},{},{:.4f}\n",
                            algo, size, stats.comparisons, stats.duration_ms);
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
    std::cin.ignore();
    std::cin.get();
}

}
