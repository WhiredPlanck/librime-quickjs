#include "quickjs_processor.h"

namespace rime {

QuickJSProcessor::QuickJSProcessor(const Ticket& ticket, an<qjs::Context> ctx)
    : Processor(ticket), ctx_(ctx) {};

QuickJSProcessor::~QuickJSProcessor() {};

ProcessResult QuickJSProcessor::ProcessKeyEvent(const KeyEvent& key_event) {
    return kNoop;
};

} // namespce rime
