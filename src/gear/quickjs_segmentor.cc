#include "quickjs_segmentor.h"

namespace rime {

QuickJSSegmentor::QuickJSSegmentor(const Ticket& ticket, an<QuickJS> qjs)
    : Segmentor(ticket), GearBase(ticket, qjs) {}

bool QuickJSSegmentor::Proceed(Segmentation* segmentation) {
    try {
        if (!exec_) return true;
        return ((std::function<bool(const qjs::Value&, Segmentation*)>) *exec_)(*env_, segmentation);
    } catch (const qjs::exception&) {
        const auto &e = qjs_->ctx->getException();
        LOG(ERROR) << "QuickJSSegmentor::Procced error(" << name_space_ << "): " << (string) e;
        return true;
    }
}

} // namespace rime
