#pragma once

#include "function.h"

namespace fun {

	//Function composition with type checking (not generic... yet)
	template<typename F1, typename F2, typename A, typename B, typename C>
	auto operator*(Function<F1,B,C>&& f1, Function<F2,A,B>&& f2) {
		return function<A,C>([f=std::forward(f1),g=std::forward(f2)] (A&& a) {
				return f(g(std::forward<A>(a)));  });
	}
	
	
	
	
} // namespace fun