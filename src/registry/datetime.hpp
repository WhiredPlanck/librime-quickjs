#pragma once

#include "extend/datetime.hpp"
#include "lib/quickjspp.hpp"

using Module = qjs::Context::Module;

namespace JSDatetime {

inline void Register(Module& module) {
    module.class_<Datetime>("Datetime")
        .constructor<>()
        .static_fun<&Datetime::format>("format");
}

}