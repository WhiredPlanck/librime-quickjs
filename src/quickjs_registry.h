#pragma once

#include <memory>
#include "registry/keyevent.hpp"

namespace JSRegistry {

inline void Register(std::string_view name, std::shared_ptr<qjs::Context> ctx) {
    auto &module = ctx->addModule(name.data());
    JSKeyEvent::Register(module);
}

} // namespace JSRegistry
