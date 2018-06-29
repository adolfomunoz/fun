#pragma once

#include "../core/function/function.h"
#include "../core/function/type.h"
#include "eq.h"

namespace fun {

struct Ord {
	template<typename T>
	struct check {
		template<typename U>
	    static auto test(U*) -> typename std::is_same<decltype(std::declval<U>() <= std::declval<U>()), bool>::type;
        template<typename>
        static constexpr std::false_type test(...);

		static constexpr bool value = decltype(test<T>(nullptr))::value &&
							Eq::check<T>::value; 
       	};
};

auto max      = function<classes<Ord,generic::a>,generic::a,generic::a,generic::a>(
	[] (const auto& x, const auto& y) { return (x<=y)?y:x; });

auto min      = function<classes<Ord,generic::a>,generic::a,generic::a,generic::a>(
	[] (const auto& x, const auto& y) { return (x<=y)?x:y; });
}
