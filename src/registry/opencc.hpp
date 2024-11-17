#pragma once

#include "extend/opencc.hpp"
#include "lib/quickjspp.hpp"

using Module = qjs::Context::Module;

namespace JSOpenCC {

inline void Register(Module &module) {
    module.class_<OpenCCComponent>("OpenCC")
        .constructor<const string&>()
        .fun<&OpenCCComponent::convertText>("convertText")
        .fun<&OpenCCComponent::ramdomConvertText>("ramdomConverText")
        .fun<&OpenCCComponent::convertWord>("convertWord");
}

} // namespace JSOpenCC