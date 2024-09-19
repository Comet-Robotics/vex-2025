#ifndef __COMETS_MATH_H__
#define __COMETS_MATH_H__

#include <cmath>
#include <type_traits>

namespace comets
{
    inline constexpr bool in_range(double value, double low, double high)
    {
        return value >= low && value <= high;
    }

    inline constexpr bool approx_equal(double a, double b, double epsilon)
    {
        return std::abs(a - b) < epsilon;
    }

    template <typename T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
    inline constexpr int signum(T val) noexcept
    {
        return (T(0) < val) - (val < T(0));
    }
} // namespace comets

#endif
