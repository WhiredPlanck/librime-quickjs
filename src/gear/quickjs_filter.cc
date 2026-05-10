
#include "quickjs_fiilter.h"
#include "quickjs_translation.h"

namespace rime {

QuickJSFilter::QuickJSFilter(const Ticket& ticket, QuickJS* qjs)
    : Filter(ticket), TagMatching(ticket), GearBase(ticket, qjs) {
    try {
        auto& ns = qjs->ns;
        qjs::Value handle = ns[ticket.name_space.c_str()];
        if (!handle.isFunction()) {
            qjs::Value tagsMatch = handle["tagsMatch"];
            if (tagsMatch.isFunction()) {
                tagsMatch_ = std::move(tagsMatch);
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

an<Translation> QuickJSFilter::Apply(an<Translation> translation, CandidateList* candidates) {
    auto generator = ((std::function<qjs::Value(an<Translation>, qjs::Value, CandidateList*)>) *handle_)(translation, *env_, candidates);
    return New<QuickJSTranslation>(qjs_, generator);
}

bool QuickJSFilter::AppliesToSegment(Segment* segment) {
    if (!tagsMatch_) {
        return TagsMatch(segment);
    }
    try {
        return ((std::function<bool(Segment*, qjs::Value)>) *tagsMatch_)(segment, *env_);
    } catch (const qjs::exception&) {
        auto e = qjs_->ctx->getException();
        LOG(ERROR) << "LuaFilter::AppliesToSegment error(" << name_space_ << "): " << (string) e;
        return false;
    }
}

} // namespace rime
