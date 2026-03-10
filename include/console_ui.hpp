#pragma once
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include "sorter.hpp"

namespace ui {

    constexpr int MIN_ARRAY_SIZE = 5;
    constexpr int MAX_ARRAY_SIZE = 50;
    constexpr int MIN_VALUE = 1;
    constexpr int MAX_VALUE = 100;
    constexpr int MAX_DISPLAY_ELEMENTS = 50;
    constexpr int ANIMATION_DELAY_MS = 30;

    enum class MenuOption {
        BubbleSort = 1,
        InsertionSort = 2,
        SelectionSort = 3,
        QuickSort = 4,
        MergeSort = 5,
        HeapSort = 6,
        ShellSort = 7,
        CountingSort = 8,
        Exit = 0
    };

    enum class Color { Green, Red, Yellow, Blue, White };

    class ConsoleUI {
    public:
        void clearScreen() const;
        void showMenu() const;
        void renderArray(const std::vector<int>& array,
                         int highlightIdx1 = -1, int highlightIdx2 = -1,
                         const std::string& action = "") const;
        std::optional<int> getArraySize() const;
        std::optional<MenuOption> getAlgorithmChoice() const;
        void showStats(const std::string& algoName, const SortStats& stats,
                       const std::vector<int>& original, const std::vector<int>& sorted) const;
        void saveResults(const std::string& filename, const std::string& algo,
                         int size, const SortStats& stats) const;
        void printMessage(const std::string& msg) const;
        void waitForEnter() const;

        static constexpr int getMinArraySize() { return MIN_ARRAY_SIZE; }
        static constexpr int getMaxArraySize() { return MAX_ARRAY_SIZE; }

    private:
        void setColor(Color c) const;
        void resetColor() const;
        std::string getBar(int value, int maxVal) const;
    };

}