#include "quickjs_processor.h"

namespace rime {

QuickJSProcessor::QuickJSProcessor(const Ticket& ticket, JSContext* ctx)
    : Processor(ticket), ctx_(ctx) {};

QuickJSProcessor::~QuickJSProcessor() {};

ProcessResult QuickJSProcessor::ProcessKeyEvent(const KeyEvent& key_event) {
    return kNoop;
};

} // namespce rime
