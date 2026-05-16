#pragma once

#include "lib/overload.hpp"
#include "lib/qjs_traits.hpp"

using Module = qjs::Context::Module;

namespace rime {
namespace quickjs {

void registerAlgebra(Module& module);
void registerCommitHistory(Module& module);
void registerComposition(Module& module);
void registerConnection(Module& module);
void registerContext(Module& module);
void registerEngine(Module& module);
void registerKeyEvent(Module& module);
void registerMenu(Module& module);
void registerSchema(Module& module);
void registerCandidate(Module& module);
void registerSegmentation(Module& module);
void registerTranslation(Module& module);
void registerConfig(Module& module);
void registerDatatime(Module& module);
void registerOpenCC(Module& module);

void initializeRegistries(qjs::Context* ctx);

}
}
