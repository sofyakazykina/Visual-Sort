#pragma once
#include <vector>
#include <string>
#include <optional>
#include <functional>
#include <memory>
#include <chrono>
#include <format>

struct SortStats {
    long long comparisons = 0;
    long long swaps = 0;
    double duration_ms = 0.0;
};

using StepCallback = std::function<void(const std::vector<int>&, int, int)>;

class ISorter {
public:
    virtual ~ISorter() = default;
    virtual std::string getName() const = 0;
    virtual SortStats sort(std::vector<int>& array, StepCallback callback) = 0;
};

class IArrayGenerator {
public:
    virtual ~IArrayGenerator() = default;
    virtual std::vector<int> generate(int size, int min_val = 1, int max_val = 100) = 0;
};

namespace ui {
    constexpr int MIN_ARRAY_SIZE = 5;
    constexpr int MAX_ARRAY_SIZE = 50;
    constexpr int MIN_VALUE = 1;
    constexpr int MAX_VALUE = 100;
    constexpr int MAX_DISPLAY_ELEMENTS = 50;
    constexpr int ANIMATION_DELAY_MS = 50;

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

    class ConsoleUI {
    public:
        void clearScreen() const;
        void showMenu() const;
        void renderArray(const std::vector<int>& array,
                         int highlightIdx1 = -1, int highlightIdx2 = -1) const;
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
    };
}