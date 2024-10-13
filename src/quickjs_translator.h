#pragma once

#include <rime/translation.h>
#include <rime/translator.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSTranslator : public Translator {
public:
    QuickJSTranslator(const Ticket& ticket, an<QuickJS> qjs);

    an<Translation> Query(const string& input, const Segment& segment) override;

private:
    an<QuickJS> qjs_;
};

} // namespace rim
