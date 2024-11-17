#include "opencc.hpp"
#include <filesystem>
#include <opencc/Config.hpp>
#include <opencc/Converter.hpp>
#include <opencc/ConversionChain.hpp>
#include <opencc/Dict.hpp>
#include <opencc/UTF8Util.hpp>
#include <rime/service.h>

namespace fs = std::filesystem;

OpenCCComponent::OpenCCComponent(const string& configPath) {
  const auto& deployer = Service::instance().deployer();
  const auto userConfig = deployer.user_data_dir / "opencc" / configPath;
  const auto sharedConfig = deployer.shared_data_dir / "opencc" / configPath;
  try {
    path foundPath;
    if (fs::exists(userConfig)) {
      foundPath = std::move(userConfig);
    } else if (fs::exists(sharedConfig)) {
      foundPath = std::move(sharedConfig);
    }
    if (!foundPath.empty()) {
      opencc::Config config;
      converter_ = config.NewFromFile(configPath);
      const auto conversions =
          converter_->GetConversionChain()->GetConversions();
      dict_ = conversions.front()->GetDict();
    }
  } catch (...) {
    LOG(ERROR) << "Either '" << userConfig << "' or '" << sharedConfig
               << "' found / valided.";
  }
}

std::optional<string> OpenCCComponent::convertText(const string& text) {
  if (!converter_)
    return std::nullopt;
  const auto& result = converter_->Convert(text);
  return std::make_optional(std::move(result));
}

std::optional<string> OpenCCComponent::ramdomConvertText(const string& text) {
  if (!dict_)
    return std::nullopt;
  const auto conversions = converter_->GetConversionChain()->GetConversions();
  const char* phrase = text.c_str();
  string result;
  for (auto conversion : conversions) {
    auto dict = conversion->GetDict();
    if (!dict)
      return std::nullopt;
    std::ostringstream buffer;
    for (const char* pstr = phrase; *pstr != '\0';) {
      auto matched = dict->MatchPrefix(pstr);
      size_t matchedLength;
      if (matched.IsNull()) {
        matchedLength = opencc::UTF8Util::NextCharLength(pstr);
        buffer << opencc::UTF8Util::FromSubstr(pstr, matchedLength);
      } else {
        auto pmatched = matched.Get();
        matchedLength = pmatched->KeyLength();
        size_t i = rand() % (pmatched->NumValues());
        buffer << pmatched->Values().at(i);
      }
      pstr += matchedLength;
    }
    result = buffer.str();
    phrase = result.c_str();
  }
  return std::make_optional(std::move(result));
}

vector<string> OpenCCComponent::convertWord(const string& text) {
  vector<string> original{text};
  if (!converter_)
    return std::move(original);
  const auto conversions = converter_->GetConversionChain()->GetConversions();
  bool matched = false;
  for (auto conversion : conversions) {
    auto dict = conversion->GetDict();
    if (!dict)
      return std::move(original);
    set<string> wordSet;
    vector<string> converted;
    for (const auto& word : original) {
      auto item = dict->Match(word);
      if (item.IsNull()) {
        // No exact match, but still need to convert partially matched
        std::ostringstream buffer;
        for (const char* wstr = word.c_str(); *wstr != '\0';) {
          auto matched = dict->MatchPrefix(wstr);
          size_t matchedLength;
          if (matched.IsNull()) {
            matchedLength = opencc::UTF8Util::NextCharLength(wstr);
            buffer << opencc::UTF8Util::FromSubstr(wstr, matchedLength);
          } else {
            matchedLength = matched.Get()->KeyLength();
            buffer << matched.Get()->GetDefault();
          }
          wstr += matchedLength;
        }
        const string& converted_word = buffer.str();
        // Even if current dictionary doesn't convert the word
        // (converted_word == original_word), we still need to keep it for
        // subsequent dicts in the chain. e.g. s2t.json expands 里 to 里 and
        // 裏, then t2tw.json passes 里 as-is and converts 裏 to 裡.
        if (wordSet.insert(converted_word).second) {
          converted.emplace_back(converted_word);
        }
        continue;
      }
      matched = true;
      const auto entry = item.Get();
      for (const auto& converted_word : entry->Values()) {
        if (wordSet.insert(converted_word).second) {
          converted.emplace_back(converted_word);
        }
      }
    }
    original.swap(converted);
  }
  return std::move(original);
}
