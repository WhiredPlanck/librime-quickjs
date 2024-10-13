#pragma once

#include "lib/quickjspp.hpp"
#include "rime/processor.h"
#include "rime/ticket.h"

namespace rime {

class QuickJSProcessor : public Processor {
public:
    QuickJSProcessor(const Ticket& ticket, an<qjs::Context> ctx);
    virtual ~QuickJSProcessor();

    ProcessResult ProcessKeyEvent(const KeyEvent& key_event) override;

private:
    an<qjs::Context> ctx_;
};


template<typename C>
class QuickJSComponent : public C::Component {
public:
    explicit QuickJSComponent(an<qjs::Context> ctx): ctx_(ctx) {};
    virtual ~QuickJSComponent() {};

    C* Create(const Ticket& ticket) {
        return new C(ticket, ctx_);
    }

protected:
    an<qjs::Context> ctx_;
};

}

