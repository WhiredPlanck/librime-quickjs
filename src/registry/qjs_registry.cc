#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void initializeRegistries(qjs::Context *ctx) {
    auto& module = ctx->addModule("rime");

    registerEngine(module);
    registerKeyEvent(module);
    registerCandidate(module);
    registerSegmentation(module);
    registerTranslation(module);
    registerConfig(module);
}

}
}
