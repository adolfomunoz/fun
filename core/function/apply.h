#pragma once

#include "function.h"
#include "type.h"

namespace fun {
	
auto apply = function<type<Function,generic::a,generic::b>,generic::a,generic::b>(
	[] (const auto& f, const auto& x) { return f(x); }
);
	
template<typename F, typename FC, typename FP, typename FR, typename P>
auto operator%(Function_<F,FC, FR,FP>&& f, P&& x) {
	return apply(std::forward<Function_<F,FC, FR,FP>>(f), std::forward<P>(x));
}

template<typename F, typename FC, typename FP, typename FR, typename P>
auto operator%(Function_<F,FC, FR,FP>&& f, const P& x) {
	return apply(std::forward<Function_<F,FC,FR,FP>>(f), x);
}

template<typename F, typename FC, typename FP, typename FR, typename P>
auto operator%(const Function_<F,FC,FR,FP>& f, P&& x) {
	return apply(f, std::forward<P>(x));
}

template<typename F, typename FC, typename FP, typename FR, typename P>
auto operator%(const Function_<F,FC, FR,FP>& f, const FP& x) {
	return apply(f, x);
}

} // namespace fun
