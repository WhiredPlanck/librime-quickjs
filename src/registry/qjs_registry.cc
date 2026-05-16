#include "qjs_registry.h"
#include "rime/processor.h"

namespace rime {
namespace quickjs {

void initializeRegistries(qjs::Context *ctx) {
    auto& module = ctx->addModule("rime");

    registerAlgebra(module);
    registerCommitHistory(module);
    registerComposition(module);
    registerConnection(module);
    registerContext(module);
    registerEngine(module);
    registerKeyEvent(module);
    registerMenu(module);
    registerSchema(module);
    registerCandidate(module);
    registerSegmentation(module);
    registerTranslation(module);
    registerConfig(module);

    module.object<ProcessResult>("ProcessResult")
        .fun("kRejected", ProcessResult::kRejected)
        .fun("kAccepted", ProcessResult::kAccepted)
        .fun("kNoop", ProcessResult::kNoop);
}

}
}
