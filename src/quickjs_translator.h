#pragma once

#include <rime/translation.h>
#include <rime/translator.h>
#include <rime/segmentation.h>

#include "gear_base.h"
#include "lib/quickjs.hpp"

namespace rime {

class QuickJSTranslator : public Translator, GearBase {
public:
    QuickJSTranslator(const Ticket& ticket, an<QuickJS> qjs);

    an<Translation> Query(const string& input, const Segment& segment) override;
};

} // namespace rim
