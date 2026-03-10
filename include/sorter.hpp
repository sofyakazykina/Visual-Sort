#pragma once
#include <vector>
#include <string>
#include <chrono>

// Результат сортировки
struct SortResult {
    std::vector<int> sorted_array;
    long long comparisons = 0;
    long long swaps = 0;
    double execution_time_ms = 0.0;
};

// Единый интерфейс для всех алгоритмов
class ISorter {
public:
    virtual ~ISorter() = default;
    virtual std::string getName() const = 0;
    virtual SortResult sort(std::vector<int> arr) = 0;
};
