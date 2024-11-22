#pragma once

#include <rime/config.h>
#include <optional>

#include "lib/quickjspp.hpp"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSConfig {

#define GETTER_ALIAS(R, N, F) \
static std::optional<R> N(Config * config, const string& path) { \
    R value;                                              \
    if (config->F(path, &value)) {                        \
        return value;                                     \
    } else {                                              \
        return std::nullopt;                              \
    }                                                     \
}

struct ConfigAlias {
    GETTER_ALIAS(bool, getBool, GetBool)
    GETTER_ALIAS(int, getInt, GetInt)
    GETTER_ALIAS(double, getDouble, GetDouble)
    GETTER_ALIAS(string, getString, GetString)
};

inline void Register(Module& module) {
    module.class_<Config>("Config")
        .fun<&Config::IsNull>("isNull")
        .fun<&Config::IsValue>("isValue")
        .fun<&Config::IsList>("isList")
        .fun<&Config::IsMap>("isMap")
        .add<&ConfigAlias::getBool>("getBool")
        .add<&ConfigAlias::getInt>("getInt")
        .add<&ConfigAlias::getDouble>("getDouble")
        .add<&ConfigAlias::getString>("getString");
}

} // namespace JSConfig
