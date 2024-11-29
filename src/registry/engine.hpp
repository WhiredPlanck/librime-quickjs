#pragma once

#include "lib/quickjspp.hpp"
#include "rime/engine.h"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSEngine {

inline void Register(Module &module) {
    module.class_<Engine>("Engine")
        .fun<&Engine::schema>("schema")
        .fun<&Engine::CommitText>("commitText");
}

}