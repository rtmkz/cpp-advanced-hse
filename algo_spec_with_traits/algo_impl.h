#include <cstdint>
#include <type_traits>

using AlgoRes = int;

struct Int128 { int64_t lo, hi; };
struct Int256 { Int128 lo, hi; };

template <class T> concept integral = std::is_integral_v<T>;
template <class T> concept unsigned_integral = std::is_unsigned_v<T>;
template <class T> concept floating_point = std::is_floating_point_v<T>;

AlgoRes ComputeUnsignedIntegral(unsigned_integral auto) { return 1 << 3; }
AlgoRes ComputeIntegral(integral auto) { return 1 << 2; }
AlgoRes ComputeFloat(floating_point auto) { return 1 << 1; }
AlgoRes ComputeGeneral(auto) { return 1 << 0; }
