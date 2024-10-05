#include <rime/component.h>
#include <rime/registry.h>
#include <rime_api.h>

#include "todo_processor.h"

using namespace rime;

static void rime_quickjs_initialize() {
  Registry &r = Registry::instance();
  r.Register("todo_processor", new Component<TodoProcessor>);
}

static void rime_quickjs_finalize() {
}

RIME_REGISTER_MODULE(quickjs)
