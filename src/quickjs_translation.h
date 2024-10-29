#pragma once

#include <rime/translation.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSTranslation: public Translation {
public:
    QuickJSTranslation(an<QuickJS> qjs, an<qjs::Value> resolving);
    virtual ~QuickJSTranslation();

    bool Next();
    an<Candidate> Peek();

private:
    an<QuickJS> qjs_;
    an<Candidate> candi_;
    an<qjs::Value> resolving_;
};

} // namespace rime
