#include "quickjs_segmentor.h"

namespace rime {

QuickJSSegmentor::QuickJSSegmentor(const Ticket& ticket, an<QuickJS> qjs)
    : Segmentor(ticket), qjs_(qjs) {}

QuickJSSegmentor::~QuickJSSegmentor() {}

bool QuickJSSegmentor::Proceed(Segmentation* segmentation) {
    return false;
}

} // namespace rime
