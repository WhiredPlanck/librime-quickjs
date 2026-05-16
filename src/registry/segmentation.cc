#include <rime/segmentation.h>
#include <rime/menu.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

Segment* segmentationBack(Segmentation * self) {
    if (self->empty()) return nullptr;
    return &self->back();
}

void registerSegmentation(Module& module) {
    module.class_<Segment>("Segment")
        .constructor<>()
        .constructor<int, int>()
        .fun("kVoid", Segment::kVoid)
        .fun("kGuess", Segment::kGuess)
        .fun("kSelected", Segment::kSelected)
        .fun("kConfirmed", Segment::kConfirmed)
        .fun<&Segment::status>("status")
        .fun<&Segment::start>("start")
        .fun<&Segment::end>("end")
        // .fun<&Segment::tags>("tags")
        .fun<&Segment::menu>("menu")
        .fun<&Segment::selected_index>("selectedIndex")
        .fun<&Segment::prompt>("prompt")
        .fun<&Segment::Clear>("clear")
        .fun<&Segment::Close>("close")
        .fun<&Segment::Reopen>("reopen")
        .fun<&Segment::HasTag>("hasTag")
        .fun<&Segment::GetCandidateAt>("getCandidateAt")
        .fun<&Segment::GetSelectedCandidate>("getSelectedCandidate");

    module.class_<Segmentation>("Segmentation")
        .property<&Segmentation::input>("input")
        .property<&Segmentation::size>("size")
        .fun<overload<const string&>(&Segmentation::Reset)>("resetInput")
        .fun<overload<size_t>(&Segmentation::Reset)>("resetLength")
        .fun<&Segmentation::AddSegment>("addSegment")
        .fun<&Segmentation::Forward>("forward")
        .fun<&Segmentation::Trim>("trim")
        .fun<&Segmentation::HasFinishedSegmentation>("hasFinishedSegmentation")
        .fun<&Segmentation::GetCurrentStartPosition>("getCurrentStartPosition")
        .fun<&Segmentation::GetCurrentEndPosition>("getCurrentEndPosition")
        .fun<&Segmentation::GetConfirmedPosition>("getConfirmedPosition")
        .fun<&Segmentation::GetCurrentSegmentLength>("getCurrentSegmentLength")
        .fun<&Segmentation::empty>("empty")
        .fun<&segmentationBack>("back")
        .fun<&Segmentation::pop_back>("popBack");
}

}
}
