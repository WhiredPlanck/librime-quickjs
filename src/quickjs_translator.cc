#include "quickjs_translator.h"

namespace rime {

QuickJSTranslator::QuickJSTranslator(const Ticket& ticket, an<QuickJS> qjs)
    : Translator(ticket), GearBase(ticket, qjs) {};

an<Translation> QuickJSTranslator::Query(const string& input, const Segment& segment) {
    return nullptr;
}

} // namespace rime