#pragma once

#include <utility>
#include <tuple>
#include <iostream>
#include "../type/type.h"


//This replaces something that will happen in C++20
namespace std {
template< class T >
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};	
template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;
}

namespace fun {
	
//Handles construction of functions
template<typename F>
class FunctionBase
{
protected:
	F   f;
public:
	constexpr FunctionBase(F&& f)      : f(std::forward<F>(f)) { }
	constexpr FunctionBase(const F& f) : f(f) { }

	//Implementation details, do not use
	const F& impl() const { return f; }
};

//Handles construction of functions, specialization for function pointers (standard C++ functions)
template<typename F>
class FunctionBase<F&>
{
protected:
	F&   f;
public:
	constexpr FunctionBase(const F& f) : f(f) { }
	const F& impl() const { return f; }
};


template<typename F, typename... Args>
class Function_ : public FunctionBase<F> { };

namespace detail {
	template<typename F> //Callable object considered by default
	struct function_deduction { 
		static constexpr auto generate(F&& f) {
			return function_deduction<decltype(&F::operator())>::generate(std::forward<F>(f));
		}
		static constexpr auto generate(const F& f) {
			return function_deduction<decltype(&F::operator())>::generate(f);
		}
	};

	template<typename Ret, typename... Args>
	struct function_deduction<Ret (Args...)> {
		template<typename F>
		static constexpr auto generate(const F& f) { 
			return Function_<const std::remove_cvref_t<F>&,Ret,Args...>(f); 
		}
	};

	template<typename Class, typename Ret, typename... Args>
	struct function_deduction<Ret (Class::*)(Args...) const> {
		template<typename F>
		static constexpr auto generate(F&& f) { 
			return Function_<std::remove_cvref_t<F>,Ret,Args...>(std::forward<F>(f)); 
		}
	};
	
	template<typename T, std::size_t... I>
	auto tuple_elements(const T& t, std::index_sequence<I...>) {
		return std::tuple(std::get<I>(t)...);
	}
	
	template<typename... Args>
	auto tuple_reorder(const std::tuple<Args...>& t) {
		return std::tuple_cat(std::tuple(std::get<sizeof...(Args)-1>(t)),
			tuple_elements(t, std::make_index_sequence<sizeof...(Args)-1>{}));
	}

	template<typename F, typename T>
	struct function_from_tuple { };
	
	template<typename F, typename... Args>
	struct function_from_tuple<F,std::tuple<Args...>> {
		using type = Function_<F,Args...>;
	};
	
	template<typename F, typename... Args>
	struct function_reorder {
		using type = typename function_from_tuple<F,
			decltype(tuple_reorder(std::declval<std::tuple<Args...>>()))>::type;
	};
	
	template<typename F, typename Ret>
	struct function_reorder<F,Ret> {
		using type = Function_<F,Ret>;
	};

	template<std::size_t I, typename NewType, typename Arg, typename... Args>
	struct tuple_replace_generic {
		using type = decltype(std::tuple_cat(std::declval<std::tuple<Arg>>(),
				std::declval<typename tuple_replace_generic<I,NewType,Args...>::type>()));
	};
	
	template<std::size_t I, typename NewType, typename Arg>
	struct tuple_replace_generic<I, NewType, Arg> {
		using type = std::tuple<Arg>;
	};
	
	template<std::size_t I, typename NewType, typename... Args>
	struct tuple_replace_generic<I,NewType,Generic<I>,Args...> {
		using type = decltype(std::tuple_cat(std::declval(std::tuple<NewType>()),
				tuple_replace_generic<I,NewType,Args...>::type));		
	};	

	template<std::size_t I, typename NewType>
	struct tuple_replace_generic<I, NewType, Generic<I>> {
		using type = std::tuple<NewType>;
	};
		
	template<typename F, std::size_t I, typename NewType, typename Arg, typename... Args>
	struct function_replace_generic {
		using type = typename function_from_tuple<F, decltype(tuple_reorder(std::declval<typename tuple_replace_generic<I,NewType,Arg,Args...>::type>()))>::type;
	};

	template<typename F, std::size_t I, typename NewType, typename Arg>
	struct function_replace_generic<F,I,NewType,Arg> {
		using type = typename function_from_tuple<F, typename tuple_replace_generic<I,NewType,Arg>::type>::type;
	};

		
	template<typename... Args> 
	struct function_aux { 
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

	template<std::size_t I, typename NewType, typename... Args> 
	struct function_replace_aux { 
		template<typename F>
		static constexpr auto generate(F&& f) {
			return (typename function_replace_generic<std::remove_cvref_t<F>,I, NewType,Args...>::type)(std::forward<F>(f)); 
		}
		template<typename F>
		static constexpr auto generate(const F& f) {
			return (typename function_replace_generic<std::remove_cvref_t<F>,I, NewType,Args...>::type)(f); 
		}
		template<typename R, typename... A>
		static constexpr auto generate(R f(A...)) {
			return (typename function_replace_generic<decltype(f),I, NewType,Args...>::type)(f); 			
		}
	};

	
};

template<std::size_t I, typename NewType, typename A1, typename... Args, typename F>
auto function_replace(F&& f) {
	return detail::function_replace_aux<I, NewType, A1, Args...>::generate(std::forward<F>(f));
}

template<typename A1, typename... Args, typename F>
auto function(F&& f) {
	return detail::function_aux<A1, Args...>::generate(std::forward<F>(f));
}

template<typename F>
auto function(F&& f) {
	return detail::function_deduction<std::remove_cvref_t<F>>::generate(std::forward<F>(f));
}

//Special case for 0 parameter functions (can be evaluated and converted to ret (lazy evaluation))
template<typename F, typename Ret>
class Function_<F,Ret> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;

	operator Ret() const { return (this->f)(); }
};

//Special case for 0 parameter functions (can be evaluated and converted to ret (lazy evaluation)). If we reach this point and it is still generic, we deduce the type from the function call
template<typename F, std::size_t I>
class Function_<F,Generic<I>> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	using Ret = decltype(std::declval<F>()());
	
	operator Ret() const { return (this->f)(); }
};

//When outputting a lazy-evaluable function, we actually evaluate it
template<typename F, typename Ret>
std::ostream& operator<<(std::ostream& os, const Function_<F,Ret>& f) {
	os<<f.impl()(); return os;
}

template<typename F, typename Arg>
class Curried {
	F f;
	Arg arg;
public:
	Curried(F&& f, Arg&& arg) : f(std::forward<F>(f)), arg(std::forward<Arg>(arg)) { }
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(F&& f, const Arg& arg) : f(std::forward<F>(f)), arg(arg)               { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	template<typename... Args>
	auto operator()(Args&&... args) const {
		return f(arg, std::forward<Args>(args)...);
	}

/*
	template<typename... Args>
	auto operator()(const Args&... args) const {
		return f(arg, args...);
	}*/
};


template<typename F, typename Arg>
class Curried<F&,Arg> {
	F& f;
	Arg arg;
public:
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	template<typename... Args>
	auto operator()(Args&&... args) const {
		return f(arg, std::forward<Args>(args)...);
	}
};
//General case for 1 or more parameters
template<typename F, typename Ret, typename Arg, typename... Args>
class Function_<F,Ret,Arg,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	auto operator()(Arg&& arg) const { //Currying
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,std::forward<Arg>(arg)));
	}

	auto operator()(const Arg& arg) const { //Currying
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,arg));
	}
	
	template<typename FArg>
	auto operator()(Function_<FArg,Arg>&& arg) const {//Currying with lazy evaluation
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,Arg>>>(this->f,std::forward<Function_<FArg,Arg>>(arg)));	
	}
	
	template<typename FArg>
	auto operator()(const Function_<FArg,Arg>& arg) const {//Currying with lazy evaluation
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,Arg>>>(this->f,arg));	
	}
	
	//A1 instead of Arg in order to enable lazy evaluation of parameters.
	template<typename A1, typename A2, typename... Args2>
	auto operator()(A1&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<A1>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};

//General case for 1 or more parameters with a generic argument
template<typename F, typename Ret, std::size_t I, typename... Args>
class Function_<F,Ret,Generic<I>,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	template<typename Arg> //It is indeed generic
	auto operator()(Arg&& arg) const { //Currying
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<I,Arg,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,std::forward<Arg>(arg)));
	}

	template<typename Arg> //It is indeed generic	
	auto operator()(const Arg& arg) const { //Currying
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<I,Arg,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>>(this->f,arg));
	}
	
	template<typename FArg, typename Arg> // It is indeed generic
	auto operator()(Function_<FArg,Arg>&& arg) const {//Currying with lazy evaluation
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<I,Arg,Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,Arg>>>(this->f,std::forward<Function_<FArg,Arg>>(arg)));	
	}
	
	template<typename FArg, typename Arg> // It is indeed generic
	auto operator()(const Function_<FArg,Arg>& arg) const {//Currying with lazy evaluation
		//We would need to replace Generic<I> with Arg in Args... and Ret
		return function_replace<I,Arg, Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Function_<FArg,Arg>>>(this->f,arg));	
	}
	
	//A1 instead of Arg in order to enable lazy evaluation of parameters, although
	// it does not matter here in the generic version
	template<typename A1, typename A2, typename... Args2>
	auto operator()(A1&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<A1>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};



}; //namespace fun

