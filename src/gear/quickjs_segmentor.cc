#include "quickjs_segmentor.h"

namespace rime {

QuickJSSegmentor::QuickJSSegmentor(const Ticket& ticket, QuickJS* qjs)
    : Segmentor(ticket), GearBase(ticket, qjs) {}

bool QuickJSSegmentor::Proceed(Segmentation* segmentation) {
    try {
        if (!handle_) return true;
        return ((std::function<bool(Segmentation*, qjs::Value)>) *handle_)(segmentation, *env_);
    } catch (const qjs::exception&) {
        auto e = qjs_->ctx->getException();
        LOG(ERROR) << "QuickJSSegmentor::Procced error(" << name_space_ << "): " << (string) e << (string) e["stack"];
        return true;
    }
}

} // namespace rime
