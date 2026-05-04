#include <rime/segmentation.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerSegmentation(Module& module) {
    module.class_<Segment>("Segment")
        .fun<&Segment::start>("start")
        .fun<&Segment::end>("end");
}

}
}
