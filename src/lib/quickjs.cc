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

QuickJS::~QuickJS() {
    js_std_free_handlers(rt->rt);
}


