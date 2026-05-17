#include <quickjspp.hpp>

#include <rime/common.h>
#include <limits>

namespace qjs {

template<>
struct js_traits<size_t>
{
    /// @throws exception
    static size_t unwrap(JSContext * ctx, JSValueConst v)
    {
        if constexpr (sizeof(size_t) > sizeof(int32_t)) {
            return js_traits<int64_t>::unwrap(ctx, v);
        } else {
            return js_traits<int32_t>::unwrap(ctx, v);
        }
        
    }

    static JSValue wrap(JSContext * ctx, size_t i) noexcept
    {
        if constexpr (sizeof(size_t) > sizeof(int32_t)) {
            return js_traits<int64_t>::wrap(ctx, i);
        } else {
            return js_traits<int32_t>::wrap(ctx, i);
        }
    }
};

template<>
struct js_traits<rime::path>
{
    static rime::path unwrap(JSContext* ctx, JSValueConst v)
    {
        auto sv = js_traits<std::string_view>::unwrap(ctx, v);
        return rime::path{std::string_view{sv.data(), sv.size()}};
    }

    static JSValue wrap(JSContext* ctx, const rime::path& path)
    {
        const auto& path_str = path.generic_u8string();
        return JS_NewStringLen(ctx, path_str.c_str(), path_str.size());
    }
};

}
