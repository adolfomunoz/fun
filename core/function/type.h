#pragma once

#include "../type/type.h"
#include "../type/typeinfo.h"
#include "function.h"

namespace fun {

/*******************************
 * TYPE TAG
 *******************************/

struct Function {};

/*******************************
 * MATCH
 *******************************/

template<typename P1, typename... R1, typename F, typename Ret2, typename P2, typename... R2> 
struct match<type<Function,P1,R1...>, Function_<F,Ret2,P2,R2...>> {
	using match_head = match<P1,P2>;
	using match_rest = match< apply_replacements_t<typename match_head::replacements,type<Function,R1...>>, Function_<F,Ret2,R2...> >;

	static constexpr bool value = (match_head::value) && (match_rest::value); 
	using replacements = generic_replacement_merge_t<typename match_head::replacements, typename match_rest::replacements>;
};

template<typename P1, typename F, typename Ret2> 
struct match<type<Function,P1>, Function_<F,Ret2>> {
	using match_head = match<P1,Ret2>;

	static constexpr bool value = match_head::value;
	using replacements = typename match_head::replacements;
};

namespace detail {
	template<typename... Args> 
	struct function_from_type_aux<type<Function,Args...>> { 
		template<typename F>
		static constexpr auto generate(F&& f) {
			return (typename function_reorder<std::remove_cvref_t<F>,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_reorder<std::remove_cvref_t<F>,Args...>::type)(f); 
		}
		template<typename R, typename... A>
		static constexpr auto generate(R f(A...)) {
			return (typename function_reorder<decltype(f),Args...>::type)(f); 			
		}
	};
}


//General case for 1 or more parameters with a type argument 
template<typename F, typename Ret, typename... TypeArgs, typename... Args>
class Function_<F,Ret,type<TypeArgs...>,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	template<typename Arg> //It is indeed generic and matches a specific type (or not)
	auto operator()(Arg&& arg) const { //Currying
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,std::forward<Arg>(arg)));
	}

	template<typename Arg> //It is indeed generic and matches a specific type (or not)
	auto operator()(const Arg& arg) const { //Currying
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,arg));
	}

	template<typename FArg, typename Arg> // It is indeed generic
	auto operator()(Function_<FArg,Arg>&& arg) const {//Currying with lazy evaluation
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,Arg>>>(this->f,std::forward<Function_<FArg,Arg>>(arg)));	
	}
	
	template<typename FArg, typename Arg> // It is indeed generic
	auto operator()(const Function_<FArg,Arg>& arg) const {//Currying with lazy evaluation
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,Arg>>>(this->f,arg));	
	}
	
	//A1 instead of Arg in order to enable lazy evaluation of parameters, although
	// it does not matter here in the generic version
	template<typename A1, typename A2, typename... Args2>
	auto operator()(A1&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<A1>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};











}
