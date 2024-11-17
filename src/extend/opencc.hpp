#pragma once

#include <rime/common.h>
#include <opencc/Common.hpp>
#include <optional>

using namespace rime;

class OpenCCComponent {
public:
    OpenCCComponent(const string& configPath);

    std::optional<string> convertText(const string& text);
    std::optional<string> ramdomConvertText(const string& text);
    vector<string> convertWord(const string& text);

private:
    opencc::ConverterPtr converter_;
    opencc::DictPtr dict_;
};