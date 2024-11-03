
#include "quickjs_fiilter.h"
#include "quickjs_translation.h"

namespace rime {

QuickJSFilter::QuickJSFilter(const Ticket& ticket, an<QuickJS> qjs)
    : Filter(ticket), TagMatching(ticket), GearBase(ticket, qjs) {
    try {
        env_ = New<qjs::Value>(qjs->ctx->newObject());
        (*env_)["nameSpace"] = ticket.name_space;
        auto modules = qjs->ctx->eval("qjsModules");
        qjs::Value handler = modules[ticket.name_space.c_str()];
        if (!JS_IsFunction(qjs->ctx->ctx, handler.v)) {
            qjs::Value tagsMatch = handler["tagsMatch"];
            if (JS_IsFunction(qjs->ctx->ctx, tagsMatch.v)) {
                tags_match_ = New<qjs::Value>(std::move(tagsMatch));
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

an<Translation> QuickJSFilter::Apply(an<Translation> translation, CandidateList* candidates) {
    auto generator = ((std::function<qjs::Value(const qjs::Value&, an<Translation>, CandidateList*)>) *exec_)(*env_, translation, candidates);
    return New<QuickJSTranslation>(qjs_, New<qjs::Value>(std::move(generator)));
}

bool QuickJSFilter::AppliesToSegment(Segment* segment) {
    if (!tags_match_) {
        return TagsMatch(segment);
    }
    try {
        return ((std::function<bool(const qjs::Value&, Segment*)>) *tags_match_)(*env_, segment);
    } catch (const qjs::exception&) {
        auto e = qjs_->ctx->getException();
        LOG(ERROR) << "LuaFilter::AppliesToSegment error(" << name_space_ << "): " << (string) e;
        return false;
    }
}

} // namespace rime
