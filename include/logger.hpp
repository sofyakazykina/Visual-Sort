#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>
#include <memory>

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    explicit Logger(const std::string& filename);
    ~Logger();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    void log(Level level, const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);

    static Logger& instance();

private:
    std::ofstream file_;
    std::mutex mutex_;
    static std::unique_ptr<Logger> instance_;
    static std::mutex instance_mutex_;

    std::string levelToString(Level level) const;
    std::string getCurrentTimestamp() const;
};

#endif