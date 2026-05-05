#pragma once


namespace rime {
namespace quickjs {

template <class... Args>
struct NonConstOverload
{
    template <class R, class T>
    constexpr auto operator()(R (T::*ptr)(Args...)) const noexcept -> decltype(ptr)
    {
        return ptr;
    }

    template <class R, class T>
    static constexpr auto with(R (T::*ptr)(Args...)) noexcept -> decltype(ptr)
    {
        return ptr;
    }
};

template <class... Args>
struct ConstOverload
{
    template <class R, class T>
    constexpr auto operator()(R (T::*ptr)(Args...) const) const noexcept -> decltype(ptr)
    {
        return ptr;
    }

    template <class R, class T>
    static constexpr auto with(R (T::*ptr)(Args...) const) noexcept -> decltype(ptr)
    {
        return ptr;
    }
};

template <class... Args>
struct Overload : ConstOverload<Args...>, NonConstOverload<Args...>
{
    using ConstOverload<Args...>::operator();
    using NonConstOverload<Args...>::operator();

    template <class R>
    constexpr auto operator()(R (*ptr)(Args...)) const noexcept -> decltype(ptr)
    {
        return ptr;
    }

    template <class R, class T>
    static constexpr auto with(R (T::*ptr)(Args...)) noexcept -> decltype(ptr)
    {
        return ptr;
    }
};


template <class... Args> [[maybe_unused]] constexpr Overload<Args...> overload = {};
template <class... Args> [[maybe_unused]] constexpr ConstOverload<Args...> constOverload = {};
template <class... Args> [[maybe_unused]] constexpr NonConstOverload<Args...> nonConstOverload = {};

}
}
