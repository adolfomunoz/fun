#pragma once

#include <utility>
#include <tuple>
#include <iostream>


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
};

//Handles construction of functions, specialization for function pointers (standard C++ functions)
template<typename F>
class FunctionBase<F&>
{
protected:
	F&   f;
public:
	constexpr FunctionBase(const F& f) : f(f) { }
};


template<typename F, typename... Args>
class Function : public FunctionBase<F> { };

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
			return Function<const std::remove_cvref_t<F>&,Ret,Args...>(f); 
		}
	};

	template<typename Class, typename Ret, typename... Args>
	struct function_deduction<Ret (Class::*)(Args...) const> {
		template<typename F>
		static constexpr auto generate(F&& f) { 
			return Function<std::remove_cvref_t<F>,Ret,Args...>(std::forward<F>(f)); 
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
		using type = Function<F,Args...>;
	};
	
	template<typename F, typename... Args>
	struct function_reorder {
		using type = typename function_from_tuple<F,
			decltype(tuple_reorder(std::declval<std::tuple<Args...>>()))>::type;
	};
	
	template<typename F, typename Ret>
	struct function_reorder<F,Ret> {
		using type = Function<F,Ret>;
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
};

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
class Function<F,Ret> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;

	operator Ret() const { return (this->f)(); }
};

template<typename F, typename Arg, typename... Args>
class Curried {
	F f;
	Arg arg;
public:
	Curried(F&& f, Arg&& arg) : f(std::forward<F>(f)), arg(std::forward<Arg>(arg)) { }
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(F&& f, const Arg& arg) : f(std::forward<F>(f)), arg(arg)               { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	auto operator()(Args&&... args) const {
		return f(arg, std::forward<Args>(args)...);
	}

	auto operator()(const Args&... args) const {
		return f(arg, args...);
	}
};

template<typename F, typename Arg>
class Curried<F,Arg> {
	F f;
	Arg arg;
public:
	Curried(F&& f, Arg&& arg) : f(std::forward<F>(f)), arg(std::forward<Arg>(arg)) { }
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(F&& f, const Arg& arg) : f(std::forward<F>(f)), arg(arg)               { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	auto operator()() const {
		return f(arg);
	}
};


template<typename F, typename Arg, typename... Args>
class Curried<F&,Arg,Args...> {
	F& f;
	Arg arg;
public:
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	auto operator()(Args&&... args) const {
		return f(arg, std::forward<Args>(args)...);
	}

	auto operator()(const Args&... args) const {
		return f(arg, args...);
	}
};

template<typename F, typename Arg>
class Curried<F&,Arg> {
	F& f;
	Arg arg;
public:
	Curried(const F& f, Arg&& arg) : f(f), arg(std::forward<Arg>(arg))             { }
	Curried(const F& f, const Arg& arg) : f(f), arg(arg)                           { }

	auto operator()() const {
		return f(arg);
	}
};




//General case for 1 or more parameters
template<typename F, typename Ret, typename Arg, typename... Args>
class Function<F,Ret,Arg,Args...> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	auto operator()(Arg&& arg) const { //Currying
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>, Args...>(this->f,std::forward<Arg>(arg)));
	}

	auto operator()(const Arg& arg) const { //Currying
		return function<Args...,Ret>(Curried<decltype(this->f),std::remove_cvref_t<Arg>, Args...>(this->f,arg));
	}
	
	template<typename A2, typename... Args2>
	auto operator()(Arg&& arg, A2&& a2, Args2&&... args2) const { // Full call
		return ((*this)(std::forward<Arg>(arg)))
			(std::forward<A2>(a2),std::forward<Args2>(args2)...);
	}
};



}; //namespace fun

