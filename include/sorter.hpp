#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <functional>

struct SortStats {
    std::vector<int> sorted_array;
    long long comparisons = 0;
    long long swaps = 0;
    double duration_ms = 0.0;
};

using VisualCallback = std::function<void(const std::vector<int>&, int, int, const std::string&)>;

class ISorter {
public:
    virtual ~ISorter() = default;
    virtual std::string getName() const = 0;
    virtual SortStats sort(std::vector<int>& array, VisualCallback callback) = 0;
    virtual SortStats sortFast(std::vector<int> array) = 0;
};
