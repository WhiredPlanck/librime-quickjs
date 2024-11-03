#pragma once

#include <rime/segmentor.h>
#include <rime/segmentation.h>

#include "gear_base.h"
#include "lib/quickjs.hpp"

namespace rime {

class QuickJSSegmentor: public Segmentor, GearBase {
public:
    QuickJSSegmentor(const Ticket& ticket, an<QuickJS> qjs);
    virtual ~QuickJSSegmentor() = default;

    virtual bool Proceed(Segmentation* Segmentation);
};

} // namespace rime
