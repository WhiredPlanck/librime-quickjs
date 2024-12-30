#include "quickjs.hpp"
#include <cstddef>
#include "lib/quickjspp.hpp"
#include "quickjs-libc.h"
#include "quickjs.h"

QuickJS::QuickJS(bool bignumExt): rt(new Runtime) {
    bignum_ext = bignumExt;
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(rt->rt);

    JS_SetModuleLoaderFunc(rt->rt, NULL, js_module_loader, NULL);

    ctx = std::make_shared<Context>(JS_NewCustomContext(rt->rt));

    js_std_add_helpers(ctx->ctx, 0, NULL);
    JS_AddExtraHelper(ctx);

    /* make 'std' and 'os' visible to non module code */
    ctx->eval(R"xxx(
        import * as std from 'std';
        import * as os from 'os';
        globalThis.std = std;
        globalThis.os = os;
    )xxx", "<input>", JS_EVAL_TYPE_MODULE);
}

QuickJS::~QuickJS() {
    js_std_loop(ctx->ctx);
    js_std_free_handlers(rt->rt);
}


