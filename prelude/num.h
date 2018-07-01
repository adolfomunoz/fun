#pragma once

#include <type_traits>
#include "floating.h"
#include "integral.h"

namespace fun {

struct Num {
	template<typename T>
	struct check {
		static constexpr bool value = 
			Floating::check<T>::value ||
			Integral::check<T>::value;
       	};
};

auto negate = fun::function<classes<Num,generic::a>,generic::a, generic::a>(
	[] (const auto& x) { return -x; });
auto abs = fun::function<classes<Num,generic::a>,generic::a, generic::a>(
	[] (const auto& x) { return std::abs(x); });
auto signum = fun::function<classes<Num,generic::a>,generic::a, generic::a>(
	[] (const auto& x) { return (x<0)?decltype(x)(-1):((x>0)?decltype(x)(1):decltype(x)(0));});


}
