#include "extend/opencc.hpp"

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerOpenCC(Module &module) {
    module.class_<OpenCCComponent>("OpenCC")
        .constructor<const string&>()
        .fun<&OpenCCComponent::convertText>("convertText")
        .fun<&OpenCCComponent::ramdomConvertText>("ramdomConverText")
        .fun<&OpenCCComponent::convertWord>("convertWord");
}

}
}