#include <rime/component.h>
#include <rime/registry.h>
#include <rime/service.h>
#include <rime_api.h>

#include "lib/quickjs.hpp"
#include "quickjs_registry.h"
#include "quickjs_processor.h"
#include "quickjs_translator.h"

using namespace rime;

namespace fs = std::filesystem;

static void quickjs_initialize(an<qjs::Context> ctx) {
  JSRegistry::Register("RimeQuickJS", ctx);

  auto &deployer(Service::instance().deployer());
  const auto userScript = deployer.user_data_dir / "rime.js";
  const auto sharedScript = deployer.shared_data_dir / "rime.js";

  try {
    if (fs::exists(userScript)) {
      LOG(INFO) << "loading user's JavaScript file '" << userScript << "'";
      ctx->evalFile(userScript.c_str());
    } else if (fs::exists(sharedScript)) {
      LOG(INFO) << "loading shared JavaScript file '" << sharedScript << "'";
      ctx->evalFile(sharedScript.c_str());
    }
  } catch (const qjs::exception&) {
    const auto &e = ctx->getException();
    LOG(ERROR) << "failed to load rime.js: " << e.as<string>();
  }
}

static void rime_quickjs_initialize() {
  LOG(INFO) << "registering components from module 'quickjs'.";
  Registry &r = Registry::instance();

  an<QuickJS> qjs(new QuickJS);
  quickjs_initialize(qjs->ctx);

  r.Register("qjs_processor", new QuickJSComponent<QuickJSProcessor>(qjs));
  r.Register("qjs_translator", new QuickJSComponent<QuickJSTranslator>(qjs));
}

static void rime_quickjs_finalize() {
}

RIME_REGISTER_MODULE(quickjs)
