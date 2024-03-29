#pragma once

#include <constexpr_map.h>

#include <type_traits>

template<class K, class V>
constexpr void Swap(std::pair<K, V>& a, std::pair<K, V>& b, bool f = 0) {
	if (!f) {
		// increasing
		if (b < a) {
			std::swap(a.first, b.first);
			std::swap(a.second, b.second);
		}
	} 
	else {
		// decreasing
		if (a < b) {
			std::swap(a.first, b.first);
			std::swap(a.second, b.second);
		}
	}
}

template<class K, class V, int S>
constexpr auto Sort(ConstexprMap<K, V, S> map) {
	bool f = 0;
	for (size_t i = 0; i < map.Size(); i++) {
		f |= std::is_integral_v<K>;
	}
	for (size_t i = 0; i < map.Size(); i++) {
		for (size_t j = i + 1; j < map.Size(); j++) {
			Swap(map.GetByIndex(i), map.GetByIndex(j), f);
		}
	}
	return map;
}
