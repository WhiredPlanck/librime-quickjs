#pragma once

#include <rime/processor.h>
#include <rime/ticket.h>
#include <rime/key_event.h>

#include "gear_base.h"
#include "lib/quickjs.hpp"

namespace rime {

class QuickJSProcessor : public Processor, GearBase {
public:
    QuickJSProcessor(const Ticket& ticket, an<QuickJS> qjs);
    virtual ~QuickJSProcessor() = default;

    ProcessResult ProcessKeyEvent(const KeyEvent& key_event) override;
};


template<typename C>
class QuickJSComponent : public C::Component {
public:
    explicit QuickJSComponent(an<QuickJS> qjs): qjs_(qjs) {};
    virtual ~QuickJSComponent() {};

    C* Create(const Ticket& ticket) {
        return new C(ticket, qjs_);
    }

protected:
    an<QuickJS> qjs_;
};

}

