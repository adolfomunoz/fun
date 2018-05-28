#pragma once

#include "function.h"

namespace fun {

//We probably need a "Composed" class, unless we manage the mumbo-jumbo of generic functions.

//Function composition with type checking (not generic... yet)
template<typename F1, typename F2, typename A, typename B, typename C>
auto operator*(Function<F1,C,B>&& f1, Function<F2,B,A>&& f2) {
	return function<A,C>([f=std::forward(f1),g=std::forward(f2)] (A&& a) {
		return f(g(std::forward<A>(a)));  });
}
	
	
	
	
} // namespace fun
