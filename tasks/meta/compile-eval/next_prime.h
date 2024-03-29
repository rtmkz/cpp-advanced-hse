#pragma once

constexpr bool is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}
constexpr int next_prime(int x) {
    if (is_prime(x)) return x;
    return next_prime(x + 1);
}
