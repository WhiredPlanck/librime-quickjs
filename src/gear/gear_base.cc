#include "gear_base.h"

#include <rime/engine.h>
#include <rime/schema.h>

namespace rime {

GearBase::GearBase(const Ticket& ticket, QuickJS* qjs): qjs_(qjs) {
    try {
        auto env = qjs->ctx->newObject();
        env["nameSpace"] = ticket.name_space;
        env["engine"] = ticket.engine;
        env_ = std::move(env);

        auto* ctx = qjs->ctx->ctx; 
        auto& ns = qjs->ns;
        if (JS_IsNull(ns.v)) {
            auto md = qjs->ctx->moduleLoader(ticket.name_space.c_str());
            ns = qjs->evalModuleNamespace(*md.source, *md.url);
        }
        qjs::Value handle = ns[ticket.name_space.c_str()];
        if (JS_IsFunction(ctx, handle.v)) {
            exec_ = std::move(handle);
        } else {
            qjs::Value init = handle["init"];
            if (JS_IsFunction(ctx, init.v)) {
                ((std::function<void(const qjs::Value&)>) init)(*env_);
            }

            qjs::Value exec = handle["exec"];
            if (JS_IsFunction(ctx, exec.v)) {
                exec_ = std::move(exec);
            }

            qjs::Value exit = handle["exit"];
            if (JS_IsFunction(ctx, exit.v)) {
                exit_ = std::move(exit);
            }
        }
    } catch (const qjs::exception&) {
        auto e = qjs->ctx->getException();
        LOG(ERROR) << "QuickJS component initialize error("
            << "module: " << ticket.klass 
            << ", name_space: " << ticket.name_space
            << "): " << (string) e << (string) e["stack"];
    }
}

GearBase::~GearBase() {
    if (exit_) {
        try {
            ((std::function<void(const qjs::Value&)>) *exit_)(*env_);
        } catch (const qjs::exception&) {
            const auto& e = qjs_->ctx->getException();
            LOG(ERROR) << "QuickJS component deconstruct error(" << (string) (*env_)["nameSpace"] << "): " << (string) e;
        }
    }
}

} // namespace rime
