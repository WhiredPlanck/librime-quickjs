#pragma once

#include <memory>
#include "registry/candidate.hpp"
#include "registry/keyevent.hpp"
#include "registry/segment.hpp"

namespace JSRegistry {

inline void Register(std::string_view name, std::shared_ptr<qjs::Context> ctx) {
    auto &module = ctx->addModule(name.data());
    JSKeyEvent::Register(module);
    JSCandidate::Register(module);
    JSSegment::Register(module);
}

} // namespace JSRegistry
