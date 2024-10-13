#pragma once

#include <memory>
#include "lib/quickjspp.hpp"
#include "quickjs-libc.h"

using namespace qjs;

static bool bignum_ext;

class QuickJS {
public:
    std::shared_ptr<Runtime> rt;
    std::shared_ptr<Context> ctx;

    QuickJS(bool bignumExt = false);
    ~QuickJS();

private:
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
};
