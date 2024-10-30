#include "quickjs_processor.h"

#include "lib/quickjspp.hpp"

namespace rime {

QuickJSProcessor::QuickJSProcessor(const Ticket& ticket, an<QuickJS> qjs)
    : Processor(ticket), qjs_(qjs) {
        try {
            env_ = New<qjs::Value>(qjs->ctx->newObject());
            (*env_)["nameSpace"] = name_space_;
            auto val = qjs->ctx->eval(ticket.name_space);
            if (JS_IsFunction(qjs->ctx->ctx, val.v)) {
                exec_ = New<qjs::Value>(std::move(val));
            } else {
                auto init = (std::function<void(an<qjs::Value>)>) val["init"];
                init(env_);

                exec_ = New<qjs::Value>(val["exec"]);
                exit_ = New<qjs::Value>(val["exit"]);
            }
        } catch (const qjs::exception&) {
            const auto& e = qjs->ctx->getException();
            LOG(ERROR) << "QuickJS component initialize error("
                << "module: " << ticket.klass 
                << ", name_space: " << ticket.name_space
                << "): " << (string) e;
        }
    };

QuickJSProcessor::~QuickJSProcessor() {
    if (exit_) {
        try {
            exit_->as<std::function<void()>>()();
        } catch (const qjs::exception&) {
            const auto& e = qjs_->ctx->getException();
            LOG(ERROR) << "QuickJSProcessor::~QuickJSProcessor error(" << name_space_ << "): " << (string) e;
        }
    }
};

ProcessResult QuickJSProcessor::ProcessKeyEvent(const KeyEvent& key_event) {
    try {
        if (!exec_) return kNoop;
        auto event = New<KeyEvent>(std::move(key_event));
        auto res = ((std::function<int(an<qjs::Value>, an<KeyEvent>)>) *exec_)(env_, event);
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
