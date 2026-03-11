#pragma once
#include <vector>
#include <string>
#include <optional>
#include <functional>
#include <memory>
#include <chrono>

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
