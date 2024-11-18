#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>

class Datetime {
public:
    Datetime() = default;
    ~Datetime() = default;

    static std::string format(std::string_view fmt) {
        std::ostringstream buffer;
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);
        buffer << std::put_time(localtime(&tt), fmt.data());
        return std::move(buffer.str());
    }
};
