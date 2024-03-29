#pragma once


constexpr int hashCalc(const char *s, int p, int pw, int mod) {
    return (s[0] == '\0') ? 0 : (hashCalc(s + 1, p, (pw * 1LL * p % mod), mod) + s[0] * 1LL * pw) % mod;
}
constexpr int hash(const char *s, int p, int mod) {
    return hashCalc(s, p, 1, mod);
}
