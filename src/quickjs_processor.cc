#include "quickjs_processor.h"

#include "lib/quickjspp.hpp"

namespace rime {

QuickJSProcessor::QuickJSProcessor(const Ticket& ticket, an<QuickJS> qjs)
    : Processor(ticket), GearBase(ticket, qjs) {};

ProcessResult QuickJSProcessor::ProcessKeyEvent(const KeyEvent& key_event) {
    try {
        if (!exec_) return kNoop;
        auto event = New<KeyEvent>(std::move(key_event));
        auto res = ((std::function<int(const qjs::Value&, an<KeyEvent>)>) *exec_)(*env_, event);
        switch (res) {
            case 0: return kRejected;
            case 1: return kAccepted;
            default: return kNoop;
        }
    } catch (const qjs::exception&) {
        const auto &e = qjs_->ctx->getException();
        LOG(ERROR) << "QuickJSProcessor::ProcessKeyEvent error(" << name_space_ << "): " << (string) e;
        return kNoop;
    }
};

} // namespce rime
