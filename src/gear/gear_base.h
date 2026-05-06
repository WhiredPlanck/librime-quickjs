#pragma once

#include <rime/common.h>
#include <rime/ticket.h>

#include "lib/quickjs.hpp"

namespace rime {

class GearBase {
public:
    GearBase(const Ticket& ticket, QuickJS* qjs);
    ~GearBase();

protected:
    QuickJS* qjs_;
    std::optional<qjs::Value> env_;
    std::optional<qjs::Value> handle_;
    std::optional<qjs::Value> dispose_;
};

} // namespace rime
