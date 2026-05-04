#include <rime/translation.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerTranslation(Module& module) {
    module.class_<Translation>("Translation")
        .fun<&Translation::Next>("next")
        .fun<&Translation::Peek>("peek")
        .property<&Translation::exhausted>("exhausted");
}

}
}
