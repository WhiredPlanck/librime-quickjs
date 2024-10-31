#include "gear_base.h"

namespace rime {

GearBase::GearBase(const Ticket& ticket, an<QuickJS> qjs): qjs_(qjs) {
    try {
        env_ = New<qjs::Value>(qjs->ctx->newObject());
        (*env_)["nameSpace"] = ticket.name_space;
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
}

GearBase::~GearBase() {
    if (exit_) {
        try {
            ((std::function<void(an<qjs::Value>)>) *exit_)(env_);
        } catch (const qjs::exception&) {
            const auto& e = qjs_->ctx->getException();
            LOG(ERROR) << "QuickJS component deconstruct error(" << (string) (*env_)["nameSpace"] << "): " << (string) e;
        }
    }
}

} // namespace rime
