#pragma once

#include <rime/translation.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSTranslation: public Translation {
public:
    QuickJSTranslation(QuickJS* qjs, qjs::Value generator);
    virtual ~QuickJSTranslation();

    bool Next();
    an<Candidate> Peek();

private:
    QuickJS* qjs_;
    an<Candidate> candidate_;
    qjs::Value generator_;
};

} // namespace rime
