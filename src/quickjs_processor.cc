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
                qjs::Value init = val["init"];
                if (JS_IsFunction(qjs->ctx->ctx, init.v)) {
                    ((std::function<void(an<qjs::Value>)>) init)(env_);
                }

                qjs::Value exec = val["exec"];
                if (JS_IsFunction(qjs->ctx->ctx, exec.v)) {
                    exec_ = New<qjs::Value>(std::move(exec));
                }

                qjs::Value exit = val["exit"];
                if (JS_IsFunction(qjs->ctx->ctx, exit.v)) {
                    exit_ = New<qjs::Value>(std::move(exit));
                }
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
            ((std::function<void(an<qjs::Value>)>) *exit_)(env_);
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
