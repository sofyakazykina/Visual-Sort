#include "logger.hpp"
#include <iostream>

Logger::Logger(const std::string& filename) {
    file_ = std::make_unique<std::ofstream>(filename);
    if (!file_->is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

void Logger::log(const std::string& message) {
    if (file_ && file_->is_open()) {
        *file_ << message << std::endl;
    }
}

Logger::~Logger() {
    if (file_ && file_->is_open()) {
        file_->close();
    }
}
