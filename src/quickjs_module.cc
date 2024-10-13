#include <rime/component.h>
#include <rime/registry.h>
#include <rime_api.h>

#include "lib/quickjs.hpp"
#include "quickjs_registry.h"
#include "quickjs_processor.h"
#include "quickjs_translator.h"

using namespace rime;

static void rime_quickjs_initialize() {
  LOG(INFO) << "registering components from module 'quickjs'.";
  Registry &r = Registry::instance();

  an<QuickJS> qjs(new QuickJS);
  JSRegistry::Register("RimeQuickJS", qjs->ctx);

  r.Register("qjs_processor", new QuickJSComponent<QuickJSProcessor>(qjs));
  r.Register("qjs_translator", new QuickJSComponent<QuickJSTranslator>(qjs));
}

static void rime_quickjs_finalize() {
}

RIME_REGISTER_MODULE(quickjs)
