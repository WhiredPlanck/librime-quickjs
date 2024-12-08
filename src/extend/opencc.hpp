#pragma once

#include <rime/common.h>
#include <opencc/Common.hpp>
#include <optional>

using namespace rime;

class OpenCCComponent {
public:
    OpenCCComponent(std::string_view configPath);

    std::optional<string> convertText(std::string_view text);
    std::optional<string> ramdomConvertText(std::string_view text);
    vector<string> convertWord(std::string_view text);

private:
    opencc::ConverterPtr converter_;
    opencc::DictPtr dict_;
};