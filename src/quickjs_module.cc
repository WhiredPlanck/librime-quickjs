#include <rime/component.h>
#include <rime/registry.h>
#include <rime/service.h>
#include <rime_api.h>

#include "lib/quickjs.hpp"
#include "registry/qjs_registry.h"
#include "gear/quickjs_processor.h"
#include "gear/quickjs_translator.h"
#include "gear/quickjs_fiilter.h"
#include "gear/quickjs_segmentor.h"

using namespace rime;

namespace fs = std::filesystem;

QuickJS *GlobalEngine;

static qjs::Value eval_file(const char* filename) {
  auto buffer = qjs::detail::readFile(filename);
  int evalFlags = JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY;
  auto func = GlobalEngine->ctx->eval(*buffer, filename, evalFlags);
  auto ctx = GlobalEngine->ctx->ctx;
  if (JS_ResolveModule(ctx, func.v) < 0) {
    throw qjs::exception{ctx};
  }
  JSValue ret = JS_EvalFunction(ctx, func.v);
  if (JS_IsException(ret)) throw qjs::exception{ctx};
  JS_FreeValue(ctx, ret);

  JSValue ns = JS_GetModuleNamespace(ctx, (JSModuleDef*) JS_VALUE_GET_PTR(func.v));
  if (JS_IsException(ns)) throw qjs::exception{ctx};
  return qjs::Value{ctx, std::move(ns)};
}

static void quickjs_initialize() {
  auto ctx = GlobalEngine->ctx.get();
  rime::quickjs::initializeRegistries(ctx);

  auto &deployer(Service::instance().deployer());
  auto jsModuleLoader = [&deployer](std::string_view filename) -> qjs::Context::ModuleData {
    std::string name(filename);

    // 1) read directly if absolute / relative paths are used
    {
      fs::path p{name};
      if (p.is_absolute() || (!p.empty() && (p.native().rfind("./", 0) == 0 || p.native().rfind("../", 0) == 0))) {
        if (auto src = qjs::detail::readFile(p)) {
          return qjs::Context::ModuleData{ qjs::detail::toUri(p.generic_string()), std::move(*src) };
        }
      }
    }

    // 2) search in "js" directories
    const auto userDir = deployer.user_data_dir;
    const auto sharedDir = deployer.shared_data_dir;
    std::array<fs::path, 4> paths {
      userDir / "js" / (name + ".js"),
      userDir / "js" / name / "index.js",
      sharedDir / "js" / (name + ".js"),
      sharedDir / "js" / name / "index.js"
    };
    for (const auto& p: paths) {
      if (auto src = qjs::detail::readFile(p)) {
        return qjs::Context::ModuleData{ qjs::detail::toUri(p.generic_string()), std::move(*src) };
      }
    }

    return qjs::Context::ModuleData{ std::nullopt, std::nullopt };
  };
  ctx->moduleLoader = jsModuleLoader;

  const auto userScript = deployer.user_data_dir / "rime.js";
  const auto sharedScript = deployer.shared_data_dir / "rime.js";

  qjs::Value ns(JS_NULL);
  try {
    if (fs::exists(userScript)) {
      LOG(INFO) << "loading user JavaScript file '" << userScript << "'";
      ns = eval_file(userScript.u8string().c_str());
    } else if (fs::exists(sharedScript)) {
      LOG(INFO) << "loading shared JavaScript file '" << sharedScript << "'";
      ns = eval_file(sharedScript.u8string().c_str());
    }
  } catch (const qjs::exception&) {
    auto e = ctx->getException();
    LOG(ERROR) << "failed to load rime.js: " << (string) e << (string) e["stack"];
  }
  GlobalEngine->ns = std::move(ns);
}

static void rime_quickjs_initialize() {
  LOG(INFO) << "registering components from module 'quickjs'.";
  Registry &r = Registry::instance();

  GlobalEngine = new QuickJS;
  quickjs_initialize();

  r.Register("qjs_processor", new QuickJSComponent<QuickJSProcessor>());
  r.Register("qjs_translator", new QuickJSComponent<QuickJSTranslator>());
  r.Register("qjs_segmentor", new QuickJSComponent<QuickJSSegmentor>());
  r.Register("qjs_filter", new QuickJSComponent<QuickJSFilter>());
}

static void rime_quickjs_finalize() {
}

RIME_REGISTER_MODULE(quickjs)
