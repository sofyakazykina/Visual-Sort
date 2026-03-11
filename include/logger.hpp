#pragma once
#include <string>
#include <fstream>
#include <memory>
#include "sorter.hpp"

class Logger {
public:
    explicit Logger(const std::string& filename);
    void log(const std::string& message);

    void logResult(const std::string& algoName, const SortResult& result) {
        log(algoName + " | Comparisons: " + std::to_string(result.comparisons) +
            " | Swaps: " + std::to_string(result.swaps) +
            " | Time: " + std::to_string(result.execution_time_ms) + " ms");
    }

    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    std::unique_ptr<std::ofstream> file_;
};