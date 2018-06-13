#pragma once

#include "type.h"
#include "function.h"

namespace fun {

//General case for 1 or more parameters with a function argument 
template<typename F, typename Ret, typename... TypeArgs, typename... Args>
class Function_<F,Ret,type<Function, TypeArgs...>,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;

	template<typename F2, typename Ret2, typename... Args2> //It is indeed generic and matches a specific type (or not)
	auto operator()(Function_<F2,Ret2,Args2...>&& arg) const { //Function parameter
		using match = fun::match<type<Function, TypeArgs...>,Function_<F2,Ret2,Args2...>>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Function_<F2,Ret2,Args2...>>>(this->f,std::forward<Function_<F2,Ret2,Args2...>>(arg)));
	}
	
	template<typename Arg> //It is indeed generic and matches a specific type (or not)
	auto operator()(Arg&& arg) const { //This is not a "fun-function" so we transform it into one with automatic types deduction
		return (*this)(function(std::forward<Arg>(arg)));
	}

	template<typename F2, typename Ret2, typename... Args2> //It is indeed generic and matches a specific type (or not)
	auto operator()(const Function_<F2,Ret2,Args2...>& arg) const { //Function parameter
		using match = fun::match<type<Function, TypeArgs...>,Function_<F2,Ret2,Args2...>>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Function_<F2,Ret2,Args2...>>>(this->f,arg));
	}
	
	template<typename Arg> //It is indeed generic and matches a specific type (or not)
	auto operator()(const Arg& arg) const { //This is not a "fun-function" so we transform it into one with automatic types deduction
		return (*this)(function(arg));
	}

	//Being a function, we do not do lazy evaluation because functions are lazily
	// evaluated themselves
	
	//A1 instead of Arg in order to enable lazy evaluation of parameters, although
	// it does not matter here in the generic version
	template<typename A1, typename A2, typename... Args2>
	auto operator()(A1&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<A1>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};











}
