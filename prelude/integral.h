#pragma once

#include <type_traits>

namespace fun {

struct Integral {
	template<typename T>
	struct check {
		static constexpr bool value = std::is_integral_v<T>;
    };
};

auto div = fun::function<classes<Integral, generic::a>,generic::a, generic::a, generic::a>(
	[] (const auto& x, const auto& y) { return x/y; } );
auto mod = fun::function<classes<Integral, generic::a>,generic::a, generic::a, generic::a>(
	[] (const auto& x, const auto& y) { return x%y; } );
auto divMod = fun::function<classes<Integral, generic::a>,generic::a, generic::a, type<Tuple,generic::a,generic::a>>(
	[] (const auto& x, const auto& y) { return std::tuple(div(x,y),mod(x,y)); } );
auto substract = flip(_-_);
auto even = (_==0)*flip(mod,2);
auto odd = (_!=0)*flip(mod,2);
}
