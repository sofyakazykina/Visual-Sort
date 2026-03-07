#pragma once
#include <string>
#include <fstream>
#include <memory>

class Logger {
public:
    explicit Logger(const std::string& filename);
    void log(const std::string& message);
    ~Logger();

private:
    std::unique_ptr<std::ofstream> file_;
};