#include "qjs_registry.h"

#include <rime/common.h>

namespace qjs {

template<typename>
struct sig_wrapper {};

template<typename R, typename... Args>
struct sig_wrapper<R(Args...)> {
    using result_type = R;
};

template <typename Signature>
struct js_traits<boost::signals2::signal<Signature>> {
    using Signal = boost::signals2::signal<Signature>;
    using ResultType = typename sig_wrapper<Signature>::result_type;

    static JSValue wrap(JSContext * ctx, Signal& sig) {
        try {
            auto value = Value{ctx, JS_NewObject(ctx)};

            value.add("connect", [sig = std::move(sig)](std::function<Signature> fn) mutable {
                sig.connect(std::move(fn));
            });

            return value.release();
        } catch (exception) {
            return JS_EXCEPTION;
        } catch (const std::exception& e) {
            JS_ThrowInternalError(ctx, "%s", e.what());
            return JS_EXCEPTION;
        } catch (...) {
            JS_ThrowInternalError(ctx, "Unknown error");
            return JS_EXCEPTION;
        }
    }
};

}
