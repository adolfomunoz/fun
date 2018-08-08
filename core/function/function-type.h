#pragma once

#include "type.h"
#include "function.h"

namespace fun {

namespace detail {
	template<typename T>
	struct function_from_type_aux{};
	
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

template<typename T, typename F>
auto function_from_type(F&& f) {
	return detail::function_from_type_aux<T>::generate(std::forward<F>(f));
}

//General case for 1 or more parameters with a type argument 
template<typename F, typename Classes, typename Ret, typename... TypeArgs, typename... Args>
class Function_<F,Classes,Ret,type<TypeArgs...>,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	template<typename Arg> //It is indeed generic and matches a specific type (or not)
	auto operator()(Arg&& arg) const { //Currying
		//We should make sure that we check the classes inside of the type match.
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Classes, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,std::forward<Arg>(arg)));
	}

	template<typename Arg> //It is indeed generic and matches a specific type (or not)
	auto operator()(const Arg& arg) const { //Currying
		//We should make sure that we check the classes inside of the type match.
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Classes, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,arg));
	}

	template<typename FArg, typename FClasses, typename Arg> // It is indeed generic
	auto operator()(Function_<FArg,FClasses,Arg>&& arg) const {//Currying with lazy evaluation
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Classes, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,FClasses,Arg>>>(this->f,std::forward<Function_<FArg,FClasses,Arg>>(arg)));	
	}
	
	template<typename FArg, typename FClasses, typename Arg> // It is indeed generic
	auto operator()(const Function_<FArg,FClasses,Arg>& arg) const {//Currying with lazy evaluation
		using match = fun::match<type<TypeArgs...>,Arg>;
		static_assert(match::value, "Type mismatch");
		return function_from_type<apply_replacements_t<typename match::replacements, type<Function, Classes, Args...,Ret>>>(
				Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,FClasses,Arg>>>(this->f,arg));	
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
