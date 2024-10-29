#pragma once

#include <rime/filter.h>
#include <rime/gear/filter_commons.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSFilter: public Filter, TagMatching {
public:
    QuickJSFilter(const Ticket& ticket, an<QuickJS> qjs);
    virtual ~QuickJSFilter();

    virtual an<Translation> Apply(an<Translation> translation, CandidateList* candidates);
    virtual bool AppliesToSegment(Segment* segment);

private:
    an<QuickJS> qjs_;
};

} // namespace rime

