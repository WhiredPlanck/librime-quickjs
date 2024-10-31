#pragma once

#include <rime/filter.h>
#include <rime/gear/filter_commons.h>

#include "gear_base.h"
#include "lib/quickjs.hpp"

namespace rime {

class QuickJSFilter: public Filter, TagMatching, GearBase {
public:
    QuickJSFilter(const Ticket& ticket, an<QuickJS> qjs);
    virtual ~QuickJSFilter() = default;

    virtual an<Translation> Apply(an<Translation> translation, CandidateList* candidates);
    virtual bool AppliesToSegment(Segment* segment);
};

} // namespace rime

