#pragma once

#include <memory>
#include "registry/candidate.hpp"
#include "registry/keyevent.hpp"
#include "registry/opencc.hpp"
#include "registry/segmentation.hpp"
#include "registry/translation.hpp"

namespace JSRegistry {

inline void Register(std::string_view name, std::shared_ptr<qjs::Context> ctx) {
    auto &module = ctx->addModule(name.data());
    JSKeyEvent::Register(module);
    JSCandidate::Register(module);
    JSSegment::Register(module);
    JSTranslation::Register(module);
    JSOpenCC::Register(module);
}

} // namespace JSRegistry
