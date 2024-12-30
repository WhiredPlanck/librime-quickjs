#pragma once

#include "lib/quickjspp.hpp"
#include "quickjs-libc.h"
#include "quickjs.h"
#include <rime/common.h>
#include <string_view>

using namespace qjs;

static bool bignum_ext;

static JSContext *JS_NewCustomContext(JSRuntime *rt)
    {
        JSContext *ctx;
        ctx = JS_NewContext(rt);
        if (!ctx)
            return NULL;
        if (bignum_ext) {
            JS_AddIntrinsicBigFloat(ctx);
            JS_AddIntrinsicBigDecimal(ctx);
            JS_AddIntrinsicOperators(ctx);
            JS_EnableBignumExt(ctx, 1);
        }
        /* system modules */
        js_init_module_std(ctx, "std");
        js_init_module_os(ctx, "os");
        return ctx;
    }

inline void JS_AddExtraHelper(std::shared_ptr<qjs::Context> ctx) {
    auto console = ctx->global()["console"];
    console["info"] = [ctx](std::string_view msg) {
        LOG(INFO) << msg;
    };
    console["warn"] = [](std::string_view msg) {
        LOG(WARNING) << msg;
    };
    console["error"] = [](std::string_view msg) {
        LOG(ERROR) << msg;
    };
    console["debug"] = [](std::string_view msg) {
        DLOG(INFO) << msg;
    };
}

class QuickJS {
public:
    std::shared_ptr<Runtime> rt;
    std::shared_ptr<Context> ctx;

    QuickJS(bool bignumExt = false);
    ~QuickJS();
};
