#pragma once

#include "lib/quickjspp.hpp"
#include "rime/translation.h"
#include "rime/translator.h"

namespace rime {

class QuickJSTranslator : public Translator {
public:
    QuickJSTranslator(const Ticket& ticket, an<qjs::Context> ctx);

    an<Translation> Query(const string& input, const Segment& segment) override;

private:
    an<qjs::Context> ctx_;
};

} // namespace rim
