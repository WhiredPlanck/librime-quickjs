#pragma once

#include <rime/segmentation.h>

#include "lib/quickjspp.hpp"

using namespace rime;

using Module = qjs::Context::Module;
namespace JSSegment {

inline void Register(Module& module) {
    module.class_<Segment>("segment")
        .fun<&Segment::start>("start")
        .fun<&Segment::end>("end");
}

}