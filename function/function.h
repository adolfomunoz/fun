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
	FunctionBase(F&& f)      : f(std::forward<F>(f)) { }
	FunctionBase(const F& f) : f(f) { }
};

template<typename F, typename Ret, typename... Args>
class Function : public FunctionBase<F> {
public:
	using FunctionBase<F>::FunctionBase;
	
	Ret operator()(Args&&... args) const {
		return f(std::forward<Args>(args)...);
	}
};

template<typename Ret, typename... Args, typename F>
auto function(F&& f) {
	return Function<std::remove_cvref_t<F>,Ret,Args...>(std::forward<F>(f));
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

