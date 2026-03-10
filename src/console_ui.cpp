#include "console_ui.hpp"
#include <iostream>
#include <format>
#include <limits>
#include <thread>
#include <chrono>
#include <fstream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

namespace ui {

void ConsoleUI::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif
}

void ConsoleUI::setColor(Color c) const {
    switch (c) {
        case Color::Green:  std::cout << "\033[1;32m"; break;
        case Color::Red:    std::cout << "\033[1;31m"; break;
        case Color::Yellow: std::cout << "\033[1;33m"; break;
        case Color::Blue:   std::cout << "\033[1;34m"; break;
        case Color::White:  std::cout << "\033[1;37m"; break;
    }
}

void ConsoleUI::resetColor() const {
    std::cout << "\033[0m";
}

std::string ConsoleUI::getBar(int value, int maxVal) const {
    if (maxVal <= 0) return ".";
    int len = (value * 35) / maxVal;
    return len > 0 ? std::string(len, '█') : ".";
}

void ConsoleUI::showMenu() const {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "║     VISUAL SORT - Main Menu        ║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << "║  1. Bubble Sort    5. Merge Sort   ║\n";
    std::cout << "║  2. Insertion Sort 6. Heap Sort    ║\n";
    std::cout << "║  3. Selection Sort 7. Shell Sort   ║\n";
    std::cout << "║  4. Quick Sort     8. Counting Sort║\n";
    std::cout << "║  0. Exit                           ║\n";
    std::cout << "╚════════════════════════════════════╝\n";
}

void ConsoleUI::renderArray(const std::vector<int>& array,
                            int highlightIdx1, int highlightIdx2,
                            const std::string& action) const {
    clearScreen();

    if (!action.empty()) {
        setColor(Color::Blue);
        std::cout << "► " << action << "\n";
        resetColor();
    }
    std::cout << "\n";

    if (array.empty()) return;

    int maxVal = *std::max_element(array.begin(), array.end());
    size_t limit = std::min(array.size(), static_cast<size_t>(MAX_DISPLAY_ELEMENTS));

    for (size_t i = 0; i < limit; ++i) {
        std::string bar = getBar(array[i], maxVal);

        if (static_cast<int>(i) == highlightIdx1 || static_cast<int>(i) == highlightIdx2) {
            setColor(Color::Red);
        } else {
            setColor(Color::Green);
        }

        std::cout << std::format("{:3} ", array[i]) << bar;
        resetColor();
        std::cout << "\n";
    }

    if (array.size() > MAX_DISPLAY_ELEMENTS) {
        std::cout << "... (" << array.size() - MAX_DISPLAY_ELEMENTS << " hidden)\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(ANIMATION_DELAY_MS));
}

std::optional<int> ConsoleUI::getArraySize() const {
    int size;
    std::cout << "\nEnter array size (" << MIN_ARRAY_SIZE << "-" << MAX_ARRAY_SIZE << "): ";

    if (std::cin >> size && size >= MIN_ARRAY_SIZE && size <= MAX_ARRAY_SIZE) {
        return size;
    }

    std::cout << "Error: Invalid size!\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::nullopt;
}

std::optional<MenuOption> ConsoleUI::getAlgorithmChoice() const {
    int choice;
    std::cout << "Select algorithm (0-8): ";

    if (std::cin >> choice && choice >= 0 && choice <= 8) {
        return static_cast<MenuOption>(choice);
    }

    std::cout << "Error: Invalid choice!\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return std::nullopt;
}

void ConsoleUI::showStats(const std::string& algoName, const SortStats& stats,
                          const std::vector<int>& original, const std::vector<int>& sorted) const {
    clearScreen();
    std::cout << "╔════════════════════════════════════╗\n";
    std::cout << "║     Sorting Complete!              ║\n";
    std::cout << "╠════════════════════════════════════╣\n";
    std::cout << std::format("║ Algorithm: {:<25} ║\n", algoName);
    std::cout << std::format("║ Comparisons: {:<21} ║\n", stats.comparisons);
    std::cout << std::format("║ Swaps: {:<27} ║\n", stats.swaps);
    std::cout << std::format("║ Time: {:.4f} ms{:<18} ║\n", stats.duration_ms, "");
    std::cout << "╚════════════════════════════════════╝\n\n";

    std::cout << "Original: ";
    for (size_t i = 0; i < std::min(original.size(), size_t(15)); i++)
        std::cout << original[i] << " ";
    if (original.size() > 15) std::cout << "...";
    std::cout << "\n";

    std::cout << "Sorted:   ";
    for (size_t i = 0; i < std::min(sorted.size(), size_t(15)); i++)
        std::cout << sorted[i] << " ";
    if (sorted.size() > 15) std::cout << "...";
    std::cout << "\n";
}

void ConsoleUI::saveResults(const std::string& filename, const std::string& algo,
                            int size, const SortStats& stats) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << std::format("{},{},{},{},{:.4f}\n",
                           algo, size, stats.comparisons, stats.swaps, stats.duration_ms);
        std::cout << "✓ Saved to " << filename << "\n";
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