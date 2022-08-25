constexpr bool IsConstantEvaluated() noexcept
{
    if (/* some compiler magic */ true) {
    // if consteval { // syntactic sugar, braces required, C++23
        return true;
    }
    else {
        return false;
    }
}

constexpr double Pow(double b, int x)
{
    if (IsConstantEvaluated()) { /// NOT if constexpr
        // constexpr-friendly (probably, more simple) algo that
        // does not make your compiler boil.
    } else {
        // Runtime version
    }
}
