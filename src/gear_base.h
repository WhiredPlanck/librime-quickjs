#pragma once

#include <rime/common.h>
#include <rime/ticket.h>

#include "lib/quickjs.hpp"

namespace rime {

class GearBase {
public:
    GearBase(const Ticket& ticket, an<QuickJS>);
    ~GearBase();

protected:
    an<QuickJS> qjs_;
    an<qjs::Value> env_;
    an<qjs::Value> exec_;
    an<qjs::Value> exit_;
};

} // namespace rime
