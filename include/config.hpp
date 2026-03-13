#pragma once

#include <string>
#include <string_view>
#include <optional>
#include <unordered_map>
#include <vector>
#include <cstdint>

class Config {
public:
    Config() = default;
    explicit Config(std::string_view filename);

    [[nodiscard]] std::optional<std::size_t> array_size() const noexcept;
    void set_array_size(std::size_t size) noexcept;

    [[nodiscard]] std::optional<std::size_t> animation_delay_ms() const noexcept;
    void set_animation_delay_ms(std::size_t delay) noexcept;

    [[nodiscard]] std::optional<std::string> log_filename() const;
    void set_log_filename(std::string_view filename);

    [[nodiscard]] std::optional<bool> enable_colors() const noexcept;
    void set_enable_colors(bool enable) noexcept;

    void save(std::string_view filename) const;

    void reset() noexcept;

    [[nodiscard]] bool has_array_size() const noexcept;
    [[nodiscard]] bool has_animation_delay() const noexcept;

private:
    std::optional<std::size_t> array_size_;
    std::optional<std::size_t> animation_delay_ms_;
    std::optional<std::string> log_filename_;
    std::optional<bool> enable_colors_;

    void load_from_file(std::string_view filename);
    [[nodiscard]] static std::string trim(std::string_view str) noexcept;
};