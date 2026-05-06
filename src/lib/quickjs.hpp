#pragma once

#include <quickjspp.hpp>
#include "quickjs/quickjs-libc.h"
#include <rime/common.h>
#include <string_view>

static JSContext *JS_NewCustomContext(JSRuntime *rt) {
    JSContext *ctx;
    ctx = JS_NewContext(rt);
    if (!ctx) return NULL;

    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");
    return ctx;
}

inline void JS_AddExtraHelper(qjs::Context* ctx) {
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
    std::unique_ptr<qjs::Runtime> rt;
    std::unique_ptr<qjs::Context> ctx;
    qjs::Value ns;

    QuickJS();
    ~QuickJS();
};

extern QuickJS *GlobalEngine;
