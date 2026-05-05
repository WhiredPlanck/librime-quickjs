#include <rime/segmentation.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerSegmentation(Module& module) {
    module.class_<Segment>("Segment")
        .constructor<>()
        .constructor<int, int>()
        .fun<&Segment::status>("status")
        .fun<&Segment::start>("start")
        .fun<&Segment::end>("end");
}

}
}
