#include <quickjs/quickjs.h>
#include <rime/component.h>
#include <rime/registry.h>
#include <rime_api.h>

#include "quickjs_processor.h"
#include "quickjs_translator.h"
#include "rime/common.h"

using namespace rime;

static void rime_quickjs_initialize() {
  LOG(INFO) << "registering components from module 'quickjs'.";
  Registry &r = Registry::instance();

  JSRuntime* runtime = JS_NewRuntime();
  JSContext* ctx = JS_NewContext(runtime);

  r.Register("qjs_processor", new QuickJSComponent<QuickJSProcessor>(ctx));
  r.Register("qjs_translator", new QuickJSComponent<QuickJSTranslator>(ctx));
}

static void rime_quickjs_finalize() {
}

RIME_REGISTER_MODULE(quickjs)
