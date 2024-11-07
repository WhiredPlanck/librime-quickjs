#pragma once

#include <rime/translation.h>

#include "lib/quickjspp.hpp"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSTranslation {

inline void Register(Module& module) {
    module.class_<Translation>("Translation")
        .fun<&Translation::Next>("next")
        .fun<&Translation::Peek>("peek")
        .property<&Translation::exhausted>("exhausted");
}

}