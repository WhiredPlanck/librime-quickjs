#include <quickjspp.hpp>

#include <rime/common.h>
#include <limits>

namespace qjs {

template<>
struct js_traits<size_t>
{
    static size_t unwrap(JSContext* ctx, JSValueConst v)
    {
        uint64_t idx;
        if (JS_ToIndex(ctx, &idx, v))
            throw exception{ctx};

        if constexpr (sizeof(size_t) < sizeof(uint64_t)) {
            if (idx > std::numeric_limits<size_t>::max()) {
                JS_ThrowRangeError(ctx, "size_t overflow");
                throw exception{ctx};
            }
        }
        return static_cast<size_t>(idx);
    }

    static JSValue wrap(JSContext* ctx, size_t i) noexcept
    {
        // Note：JS Number may not be accurate for the number >2^53
        if (i <= static_cast<size_t>(std::numeric_limits<int64_t>::max()))
            return JS_NewInt64(ctx, static_cast<int64_t>(i));
        return JS_NewFloat64(ctx, static_cast<double>(i));
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
