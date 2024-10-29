
#include "quickjs_translation.h"

namespace rime {

QuickJSTranslation::QuickJSTranslation(an<QuickJS> qjs, an<qjs::Value> resolving)
    : qjs_(qjs), resolving_(resolving) {
        Next();
    }

QuickJSTranslation::~QuickJSTranslation() {}

bool QuickJSTranslation::Next() {
    return false;
}

an<Candidate> QuickJSTranslation::Peek() { return candi_; }

} // namespace rime
