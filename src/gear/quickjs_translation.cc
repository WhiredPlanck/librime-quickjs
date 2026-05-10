
#include "quickjs_translation.h"

#include <rime/candidate.h>

namespace rime {

QuickJSTranslation::QuickJSTranslation(QuickJS* qjs, qjs::Value generator)
    : qjs_(qjs), generator_(std::move(generator)) {
        Next();
    }

QuickJSTranslation::~QuickJSTranslation() {}

bool QuickJSTranslation::Next() {
    if (exhausted()) return false;
    try {
        qjs::Value res = generator_.callMember("next");
        qjs::Value value = res["value"];
        auto done = (bool) res["done"];
        if (done || value.isUndefined()) {
            set_exhausted(true);
            return false;
        }
        candidate_ = (an<Candidate>) value;
        return true;
    } catch (const qjs::exception&) {
        auto e = qjs_->ctx->getException();
        LOG(ERROR) << "QuickJSTranslation::Next error: " << (string) e << (string) e["stack"];
        set_exhausted(true);
        return false;
    }
}

an<Candidate> QuickJSTranslation::Peek() { return candidate_; }

} // namespace rime
