
#include "quickjs_fiilter.h"

namespace rime {

QuickJSFilter::QuickJSFilter(const Ticket& ticket, an<QuickJS> qjs)
    : Filter(ticket), TagMatching(ticket), GearBase(ticket, qjs) {}

an<Translation> QuickJSFilter::Apply(an<Translation> translation, CandidateList* candidates) {
    // TODO
}

bool QuickJSFilter::AppliesToSegment(Segment* segment) {
    return false;
}

} // namespace rime
