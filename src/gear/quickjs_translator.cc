#include "quickjs_translator.h"
#include "quickjs_translation.h"
#include "rime/segmentation.h"

namespace rime {

QuickJSTranslator::QuickJSTranslator(const Ticket& ticket, QuickJS* qjs)
    : Translator(ticket), GearBase(ticket, qjs) {};

an<Translation> QuickJSTranslator::Query(const string& input, const Segment& segment) {
    if (!exec_) return an<QuickJSTranslation>();
    auto generatorFunc = ((std::function<qjs::Value(const string&, an<Segment>, qjs::Value)>) *exec_);
    auto generator = generatorFunc(input, New<Segment>(segment), *env_);
    auto translation = New<QuickJSTranslation>(qjs_, generator);
    if (translation->exhausted()) {
        return an<QuickJSTranslation>();
    } else {
        return translation;
    }
}

} // namespace rime