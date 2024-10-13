#include <rime/component.h>
#include <rime/registry.h>
#include <rime_api.h>

#include "lib/quickjspp.hpp"
#include "quickjs_processor.h"
#include "quickjs_registry.h"
#include "quickjs_translator.h"
#include "rime/common.h"

using namespace rime;

static void rime_quickjs_initialize() {
  LOG(INFO) << "registering components from module 'quickjs'.";
  Registry &r = Registry::instance();

  static an<qjs::Runtime> rt(new qjs::Runtime);
  an<qjs::Context> ctx = New<qjs::Context>(*rt);

  JSRegistry::Register("RimeQuickJS", ctx);

  r.Register("qjs_processor", new QuickJSComponent<QuickJSProcessor>(ctx));
  r.Register("qjs_translator", new QuickJSComponent<QuickJSTranslator>(ctx));
}

static void rime_quickjs_finalize() {
}

RIME_REGISTER_MODULE(quickjs)
