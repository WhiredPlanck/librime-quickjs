#pragma once

#include <memory>
#include "registry/candidate.hpp"
#include "registry/config.hpp"
#include "registry/datetime.hpp"
#include "registry/engine.hpp"
#include "registry/keyevent.hpp"
#include "registry/opencc.hpp"
#include "registry/schema.hpp"
#include "registry/segmentation.hpp"
#include "registry/translation.hpp"

namespace JSRegistry {

inline void Register(std::string_view name, std::shared_ptr<qjs::Context> ctx) {
    auto &module = ctx->addModule(name.data());
    JSEngine::Register(module);
    JSKeyEvent::Register(module);
    JSCandidate::Register(module);
    JSSchema::Register(module);
    JSSegment::Register(module);
    JSTranslation::Register(module);
    JSConfig::Register(module);
    JSOpenCC::Register(module);
    JSDatetime::Register(module);
}

} // namespace JSRegistry
