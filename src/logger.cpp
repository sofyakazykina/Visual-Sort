#include "logger.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>

std::unique_ptr<Logger> Logger::instance_ = nullptr;
std::mutex Logger::instance_mutex_;

Logger::Logger(const std::string& filename) : file_(filename, std::ios::app) {
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
    info("Logger initialized");
}

Logger::~Logger() {
    if (file_.is_open()) {
        info("Logger shutting down");
        file_.close();
    }
}

std::string Logger::levelToString(Level level) const {
    switch (level) {
        case Level::DEBUG:    return "DEBUG";
        case Level::INFO:     return "INFO";
        case Level::WARNING:  return "WARNING";
        case Level::ERROR:    return "ERROR";
        case Level::CRITICAL: return "CRITICAL";
        default:              return "UNKNOWN";
    }
}

std::string Logger::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ) % 1000;

    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

void Logger::log(Level level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!file_.is_open()) {
        std::cerr << "[" << levelToString(level) << "] " << message << std::endl;
        return;
    }
    
    file_ << "[" << getCurrentTimestamp() << "] "
          << "[" << levelToString(level) << "] "
          << message << std::endl;
    file_.flush();
}

void Logger::debug(const std::string& message)    { log(Level::DEBUG, message); }
void Logger::info(const std::string& message)     { log(Level::INFO, message); }
void Logger::warning(const std::string& message)  { log(Level::WARNING, message); }
void Logger::error(const std::string& message)    { log(Level::ERROR, message); }
void Logger::critical(const std::string& message) { log(Level::CRITICAL, message); }

Logger& Logger::instance() {
    std::lock_guard<std::mutex> lock(instance_mutex_);
    if (!instance_) {
        instance_ = std::make_unique<Logger>("visual_sort.log");
    }
    return *instance_;
}