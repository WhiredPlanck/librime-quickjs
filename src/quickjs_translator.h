#pragma once

#include <quickjs/quickjs.h>
#include "rime/translation.h"
#include "rime/translator.h"

namespace rime {

class QuickJSTranslator : public Translator {
public:
    QuickJSTranslator(const Ticket& ticket, JSContext* ctx);

    an<Translation> Query(const string& input, const Segment& segment) override;

private:
    JSContext* ctx_;
};

} // namespace rim
