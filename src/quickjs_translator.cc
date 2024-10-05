#include "quickjs_translator.h"

namespace rime {

QuickJSTranslator::QuickJSTranslator(const Ticket& ticket, JSContext* ctx)
    : Translator(ticket), ctx_(ctx) {};

an<Translation> Query(const string& input, const Segment& segment) {
    return nullptr;
}

} // namespace rime