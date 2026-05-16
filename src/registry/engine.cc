#include <rime/engine.h>
#include <rime/schema.h>
#include <rime/context.h>
#include <rime/key_event.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerEngine(Module &module) {
    module.class_<Engine>("Engine")
        .property<&Engine::active_engine, &Engine::set_active_engine>("activeEngine")
        .property<&Engine::schema>("schema")
        .property<&Engine::context>("context")
        .fun<&Engine::ProcessKey>("processKey")
        .fun<&Engine::CommitText>("commitText")
        .fun<&Engine::Compose>("compose");
}

}
}