#include "quickjs_translator.h"

namespace rime {

QuickJSTranslator::QuickJSTranslator(const Ticket& ticket, an<qjs::Context> ctx)
    : Translator(ticket), ctx_(ctx) {};

an<Translation> QuickJSTranslator::Query(const string& input, const Segment& segment) {
    return nullptr;
}

} // namespace rime