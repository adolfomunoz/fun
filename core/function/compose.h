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

/**
 * These below are to avoid conflict with lazy evaluation and multiplication with * integer
 **/
/*
template<typename Num, typename F1, typename Classes1, typename F2, typename Classes2>
Num operator*(const Function_<F1,Classes1,Num>&  n1, 
			  const Function_<F2,Classes2,Num>& n2) 
{ return Num(n1)*Num(n2); }

template<typename Num, typename F2, typename Classes2>
Num operator*(const Num& n1, const Function_<F2,Classes2,Num>& n2) 
{ return n1*(Num)(n2); }

template<typename Num, typename F1, typename Classes1>
Num operator*(const Function_<F1,Classes1,Num>&  n1, 
			  const Num& n2) 
{ return (Num)(n1)*n2; }


template<typename Num, typename F2, typename Classes2>
Num operator*(Num n1, 
			  const Function_<F2,Classes2,Num>& n2) 
{ return n1*Num(n2); }

template<typename Num, typename F1, typename Classes1>
Num operator*(const Function_<F1,Classes1,Num>&  n1, 
			  Num n2) 
{ return Num(n1)*n2; }
*/

} // namespace fun
