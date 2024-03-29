#pragma once

template<unsigned a, unsigned b>
struct Pow {
    static const unsigned tmp = Pow<a, b/2>::value;
    static const unsigned value = (b % 2 == 1 ? a * tmp * tmp : tmp * tmp);
};

template<unsigned a>
struct Pow<a, 0> {
    static const unsigned value = 1;
};
