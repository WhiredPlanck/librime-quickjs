#include <rime/engine.h>
#include <rime/schema.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerEngine(Module &module) {
    module.class_<Engine>("Engine")
        .property<&Engine::schema>("schema")
        .fun<&Engine::CommitText>("commitText");
}

}
}