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

        auto& ns = qjs->ns;
        if (ns.isNull()) {
            auto md = qjs->ctx->moduleLoader(ticket.name_space.c_str());
            ns = qjs->evalModuleNamespace(*md.source, *md.url);
        }
        qjs::Value value = ns[ticket.name_space.c_str()];
        if (value.isFunction()) {
            handle_ = std::move(value);
        } else {
            qjs::Value init = value["init"];
            if (init.isFunction()) {
                init.call(*env_);
            }

            qjs::Value handle = value["handle"];
            if (handle.isFunction()) {
                handle_ = std::move(handle);
            }

            qjs::Value dispose = value["dispose"];
            if (dispose.isFunction()) {
                dispose_ = std::move(dispose);
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
    if (dispose_) {
        try {
            dispose_->call(*env_);
        } catch (const qjs::exception&) {
            auto e = qjs_->ctx->getException();
            LOG(ERROR) << "QuickJS component deconstruct error(" << (string) (*env_)["nameSpace"] << "): " << (string) e << (string) e["stack"];
        }
    }
}

} // namespace rime
