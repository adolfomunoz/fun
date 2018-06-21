#pragma once

#include "function.h"
#include "type.h"

namespace fun {
	
auto compose = function<type<Function,generic::b,generic::c>,
			type<Function,generic::a,generic::b>,
			generic::a, generic::c>(
	[] (const auto& f, const auto&g, const auto& x) { return f(g(x)); }
);
	
template<typename F, typename FC, typename FP, typename FR, typename G, typename GC, typename GP, typename GR>
auto operator*(Function_<F,FC, FR,FP>&& f, Function_<G,GC, GR,GP>&& g) {
	return compose(std::forward<Function_<F,FC, FR,FP>>(f), std::forward<Function_<G,GC, GR,GP>>(g));
}

template<typename F, typename FC, typename FP, typename FR, typename G, typename GC, typename GP, typename GR>
auto operator*(const Function_<F,FC,FR,FP>& f, Function_<G,GC,GR,GP>&& g) {
	return compose(f, std::forward<Function_<G,GC, GR,GP>>(g));
}

template<typename F, typename FC, typename FP, typename FR, typename G, typename GC, typename GP, typename GR>
auto operator*(Function_<F,FC,FR,FP>&& f, const Function_<G,GC,GR,GP>& g) {
	return compose(std::forward<Function_<F,FC,FR,FP>>(f), g);
}

template<typename F, typename FC, typename FP, typename FR, typename G, typename GC, typename GP, typename GR>
auto operator*(const Function_<F,FC,FR,FP>& f, const Function_<G,GC,GR,GP>& g) {
	return compose(f, g);
}



} // namespace fun
