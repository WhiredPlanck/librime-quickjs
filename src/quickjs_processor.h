#pragma once

#include <quickjs/quickjs.h>
#include "rime/processor.h"
#include "rime/ticket.h"

namespace rime {

class QuickJSProcessor : public Processor {
public:
    QuickJSProcessor(const Ticket& ticket, JSContext* ctx);
    virtual ~QuickJSProcessor();

    ProcessResult ProcessKeyEvent(const KeyEvent& key_event) override;

private:
    JSContext* ctx_;
};


template<typename C>
class QuickJSComponent : public C::Component {
public:
    explicit QuickJSComponent(JSContext* ctx): ctx_(ctx) {};
    virtual ~QuickJSComponent() {};

    C* Create(const Ticket& ticket) {
        return new C(ticket, ctx_);
    }

protected:
    JSContext* ctx_;
};

}

