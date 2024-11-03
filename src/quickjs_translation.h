#pragma once

#include <rime/translation.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSTranslation: public Translation {
public:
    QuickJSTranslation(an<QuickJS> qjs, an<qjs::Value> generator);
    virtual ~QuickJSTranslation();

    bool Next();
    an<Candidate> Peek();

private:
    an<QuickJS> qjs_;
    an<Candidate> candidate_;
    an<qjs::Value> generator_;
};

} // namespace rime
