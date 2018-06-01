#pragma once

#include "function.h"

namespace fun {

//We probably need a "Composed" class, unless we manage the mumbo-jumbo of generic functions.
template<typename F1, typename F2>
class Composed {
	F1 f1; F2 f2;
public:
	Composed(F1&& f1, F2&& f2) : f1(std::forward<F1>(f1)), f2(std::forward<F2>(f2)) { }
	Composed(const F1& f1, F2&& f2) : f1(f1), f2(std::forward<F2>(f2))              { }
	Composed(F1&& f1, const F2& f2) : f1(std::forward<F1>(f1)), f2(f2)              { }
	Composed(const F1& f1, const F2& f2) : f1(f1), f2(f2)                           { }

	template<typename Arg>
	auto operator()(Arg&& arg) const {
		return f1(f2(std::forward<Arg>(arg)));
	}
};



//Function composition with type checking (not generic... yet)
template<typename F1, typename F2, typename A, typename B, typename C>
auto operator*(Function_<F1,C,B>&& f1, Function_<F2,B,A>&& f2) {
	return function<A,C>(Composed<F1,F2>(std::forward(f1.impl()), std::forward(f2.impl())));
}

//Function composition with type checking (not generic... yet)
template<typename F1, typename F2, typename A, typename B, typename C>
auto operator*(const Function_<F1,C,B>& f1, Function_<F2,B,A>&& f2) {
	return function<A,C>(Composed<F1,F2>(f1.impl(), std::forward(f2.impl())));
}

template<typename F1, typename F2, typename A, typename B, typename C>
auto operator*(Function_<F1,C,B>&& f1, const Function_<F2,B,A>& f2) {
	return function<A,C>(Composed<F1,F2>(std::forward(f1.impl()), f2.impl()));
}

template<typename F1, typename F2, typename A, typename B, typename C>
auto operator*(const Function_<F1,C,B>& f1, const Function_<F2,B,A>& f2) {
	return function<A,C>(Composed<F1,F2>(f1.impl(), f2.impl()));
}



	
	
	
	
} // namespace fun
