#include "quickjs_processor.h"

#include <quickjspp.hpp>

namespace rime {

QuickJSProcessor::QuickJSProcessor(const Ticket& ticket, QuickJS* qjs)
    : Processor(ticket), GearBase(ticket, qjs) {};

ProcessResult QuickJSProcessor::ProcessKeyEvent(const KeyEvent& key_event) {
    try {
        if (!handle_) return kNoop;
        auto res = handle_->call<int>(New<KeyEvent>(key_event), *env_);
        switch (res) {
            case 0: return kRejected;
            case 1: return kAccepted;
            default: return kNoop;
        }
    } catch (const qjs::exception&) {
        auto e = qjs_->ctx->getException();
        LOG(ERROR) << "QuickJSProcessor::ProcessKeyEvent error(" << name_space_ << "): " << (string) e << (string) e["stack"];
        return kNoop;
    }
};

} // namespce rime
