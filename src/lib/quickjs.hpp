#pragma once

#include <quickjspp.hpp>
#include "quickjs-libc.h"
#include <rime/common.h>

static JSContext *JS_NewCustomContext(JSRuntime *rt) {
    JSContext *ctx;
    ctx = JS_NewContext(rt);
    if (!ctx) return NULL;

    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");
    return ctx;
}

class QuickJS {
public:
    std::unique_ptr<qjs::Runtime> rt;
    std::unique_ptr<qjs::Context> ctx;
    qjs::Value ns;

    QuickJS();
    ~QuickJS();
};

extern QuickJS *GlobalEngine;
