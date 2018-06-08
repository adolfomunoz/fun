#pragma once

#include "function.h"
#include "type.h"

namespace fun {
	
auto compose = fun::function<
			fun::type<Function,fun::generic::b,fun::generic::c>,
			fun::type<Function,fun::generic::a,fun::generic::b>,
			fun::generic::a, fun::generic::c>(
	[] (const auto& f, const auto&g, const auto& x) { return f(g(x)); }
);
	
template<typename F, typename FP, typename FR, typename G, typename GP, typename GR>
auto operator*(Function_<F,FR,FP>&& f, Function_<G,GR,GP>&& g) {
	return compose(std::forward<Function_<F,FR,FP>>(f), std::forward<Function_<G,GR,GP>>(g));
}

template<typename F, typename FP, typename FR, typename G, typename GP, typename GR>
auto operator*(const Function_<F,FR,FP>& f, Function_<G,GR,GP>&& g) {
	return compose(f, std::forward<Function_<G,GR,GP>>(g));
}

template<typename F, typename FP, typename FR, typename G, typename GP, typename GR>
auto operator*(Function_<F,FR,FP>&& f, const Function_<G,GR,GP>& g) {
	return compose(std::forward<Function_<F,FR,FP>>(f), g);
}

template<typename F, typename FP, typename FR, typename G, typename GP, typename GR>
auto operator*(const Function_<F,FR,FP>& f, const Function_<G,GR,GP>& g) {
	return compose(f, g);
}



} // namespace fun
