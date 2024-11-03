
#include "quickjs_translation.h"

#include <rime/candidate.h>

namespace rime {

QuickJSTranslation::QuickJSTranslation(an<QuickJS> qjs, an<qjs::Value> generator)
    : qjs_(qjs), generator_(generator) {
        Next();
    }

QuickJSTranslation::~QuickJSTranslation() {}

bool QuickJSTranslation::Next() {
    if (exhausted()) return false;
    try {
        qjs::Value res = generator_->callMember("next");
        qjs::Value value = res["value"];
        auto done = (bool) res["done"];
        if (done || JS_IsUndefined(value.v)) {
            set_exhausted(true);
            return false;
        }
        candidate_ = (an<SimpleCandidate>) value;
        return true;
    } catch (const qjs::exception&) {
        auto e = qjs_->ctx->getException();
        LOG(ERROR) << "QuickJSTranslation::Next error: " << (string) e;
        set_exhausted(true);
        return false;
    }
}

an<Candidate> QuickJSTranslation::Peek() { return candidate_; }

} // namespace rime
