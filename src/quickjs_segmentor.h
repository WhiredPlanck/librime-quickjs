#pragma once

#include <rime/segmentor.h>

#include "lib/quickjs.hpp"

namespace rime {

class QuickJSSegmentor: public Segmentor {
public:
    QuickJSSegmentor(const Ticket& ticket, an<QuickJS> qjs);
    virtual ~QuickJSSegmentor();

    virtual bool Proceed(Segmentation* Segmentation);

private:
    an<QuickJS> qjs_;
};

} // namespace rime
