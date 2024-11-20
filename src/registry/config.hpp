#pragma once

#include <rime/config.h>

#include "lib/quickjspp.hpp"
#include "rime/config/config_component.h"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSConfig {

inline void Register(Module& module) {
    module.class_<Config>("Config")
        .constructor<>()
        .fun<&Config::IsNull>("isNull")
        .fun<&Config::IsValue>("isValue")
        .fun<&Config::IsList>("isList")
        .fun<&Config::IsMap>("isMap");
}

} // namespace JSConfig
