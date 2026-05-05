#pragma once

#include "lib/overload.hpp"
#include "lib/qjs_traits.hpp"

using Module = qjs::Context::Module;

namespace rime {
namespace quickjs {

void registerEngine(Module& module);
void registerKeyEvent(Module& module);
void registerCandidate(Module& module);
void registerSegmentation(Module& module);
void registerTranslation(Module& module);
void registerConfig(Module& module);
void registerDatatime(Module& module);
void registerOpenCC(Module& module);

void initializeRegistries(qjs::Context* ctx);

}
}
