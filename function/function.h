#pragma once

#include <utility>


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


template<typename F, typename Ret, typename... Args>
class Function : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	Ret operator()(Args&&... args) const {
		return f(std::forward<Args>(args)...);
	}
};

namespace detail {
	template<typename F> //Callable object considered by default
	struct function_aux_deduction { 
		static constexpr auto generate(F&& f) {
			return function_aux_deduction<decltype(&F::operator())>::generate(std::forward<F>(f));
		}
		static constexpr auto generate(const F& f) {
			return function_aux_deduction<decltype(&F::operator())>::generate(f);
		}
	};

	template<typename Ret, typename... Args>
	struct function_aux_deduction<Ret (Args...)> {
		template<typename F>
		static constexpr auto generate(const F& f) { 
			return Function<const std::remove_cvref_t<F>&,Ret,Args...>(f); 
		}
	};

	template<typename Class, typename Ret, typename... Args>
	struct function_aux_deduction<Ret (Class::*)(Args...) const> {
		template<typename F>
		static constexpr auto generate(F&& f) { 
			return Function<std::remove_cvref_t<F>,Ret,Args...>(std::forward<F>(f)); 
		}
	};

	template<typename F, typename Ret, typename... Args> 
	struct function_aux { 
		static constexpr auto generate(F&& f) {
			return Function<std::remove_cvref_t<F>,Ret,Args...>(std::forward<F>(f)); 
		}
		static constexpr auto generate(const F& f) {
			return Function<std::remove_cvref_t<F>,Ret,Args...>(f); 
		}

	};

	template<typename Ret, typename... Args>
	struct function_aux<Ret (Args...), Ret, Args...> {
		template<typename F>
		static constexpr auto generate(const F& f) { 
			return Function<const std::remove_cvref_t<F>&,Ret,Args...>(f); 
		}
	};	
};

template<typename Ret, typename... Args, typename F>
auto function(F&& f) {
	return detail::function_aux<std::remove_cvref_t<F>, Ret, Args...>::generate(std::forward<F>(f));
}

template<typename F>
auto function(F&& f) {
	return detail::function_aux_deduction<std::remove_cvref_t<F>>::generate(std::forward<F>(f));
}


//Special case for 1 parameter functions (can be composed)
template<typename F, typename Ret, typename Arg>
class Function<F,Ret,Arg> : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	Ret operator()(Arg&& arg) const {
		return (this->f)(std::forward<Arg>(arg));
	}
	
	//Function composition with type checking (not generic... yet)
	template<typename F2, typename Arg2>
	auto operator*(Function<F2,Arg,Arg2>&& that) {
		return function<Ret,Arg2>([f=*this,t=std::forward(that)] 
			(Arg2&& arg2) { return f(t(std::forward<Arg2>(arg2))); });  
	}
	
	//Function composition with type checking (not generic... yet)
	template<typename F2, typename Arg2>
	auto operator*(const Function<F2,Arg,Arg2>& that) {
		return function<Ret,Arg2>([f=*this,t=that] 
			(Arg2&& arg2) { return f(t(std::forward<Arg2>(arg2))); });  
	}
};



}; //namespace fun

