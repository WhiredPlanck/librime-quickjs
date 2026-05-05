#include <cstddef>

#include "quickjs.hpp"

QuickJS::QuickJS(): rt(new qjs::Runtime), ns(JS_NULL) {
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(rt->rt);

    JS_SetModuleLoaderFunc2(rt->rt, NULL, js_module_loader, NULL, NULL);

    ctx = std::make_unique<qjs::Context>(JS_NewCustomContext(rt->rt));

    js_std_add_helpers(ctx->ctx, 0, NULL);
    JS_AddExtraHelper(ctx.get());

    /* make 'std' and 'os' visible to non module code */
    ctx->eval(R"xxx(
        import * as std from 'std';
        import * as os from 'os';
        globalThis.std = std;
        globalThis.os = os;
    )xxx", "<input>", JS_EVAL_TYPE_MODULE);

    js_std_loop(ctx->ctx);
}

qjs::Value QuickJS::evalModuleNamespace(std::string_view source, std::string_view filename) {
    int evalFlags = JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY;
    auto func = ctx->eval(source, filename.data(), evalFlags);
    if (JS_ResolveModule(ctx->ctx, func.v) < 0) {
        throw qjs::exception{ctx->ctx};
    }
    JSValue ret = JS_EvalFunction(ctx->ctx, func.v);
    if (JS_IsException(ret)) throw qjs::exception{ctx->ctx};
    JS_FreeValue(ctx->ctx, ret);
            
    JSValue ns = JS_GetModuleNamespace(ctx->ctx, (JSModuleDef*) JS_VALUE_GET_PTR(func.v));
    if (JS_IsException(ns)) throw qjs::exception{ctx->ctx};
    return qjs::Value{ctx->ctx, std::move(ns)};
}

QuickJS::~QuickJS() {
    js_std_free_handlers(rt->rt);
}


