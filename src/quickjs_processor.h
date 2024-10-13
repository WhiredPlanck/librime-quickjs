#pragma once

#include <rime/processor.h>
#include <rime/ticket.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSProcessor : public Processor {
public:
    QuickJSProcessor(const Ticket& ticket, an<QuickJS> qjs);
    virtual ~QuickJSProcessor();

    ProcessResult ProcessKeyEvent(const KeyEvent& key_event) override;

private:
    an<QuickJS> qjs_;
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

