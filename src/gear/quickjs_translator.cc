#include "quickjs_translator.h"
#include "quickjs_translation.h"
#include "rime/segmentation.h"

namespace rime {

QuickJSTranslator::QuickJSTranslator(const Ticket& ticket, an<QuickJS> qjs)
    : Translator(ticket), GearBase(ticket, qjs) {};

an<Translation> QuickJSTranslator::Query(const string& input, const Segment& segment) {
    auto generatorFunc = ((std::function<qjs::Value(const qjs::Value&, const string&, an<Segment>)>) *exec_);
    auto generator = generatorFunc(*env_, input, New<Segment>(segment));
    auto translation = New<QuickJSTranslation>(qjs_, New<qjs::Value>(std::move(generator)));
    if (translation->exhausted()) {
        return an<QuickJSTranslation>();
    } else {
        return translation;
    }
}

} // namespace rime