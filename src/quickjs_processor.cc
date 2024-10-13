#include "quickjs_processor.h"

namespace rime {

QuickJSProcessor::QuickJSProcessor(const Ticket& ticket, an<QuickJS> qjs)
    : Processor(ticket), qjs_(qjs) {};

QuickJSProcessor::~QuickJSProcessor() {};

ProcessResult QuickJSProcessor::ProcessKeyEvent(const KeyEvent& key_event) {
    return kNoop;
};

} // namespce rime
