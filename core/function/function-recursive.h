#pragma once

#include "function-construction.h"

namespace fun {

template <typename F, typename A1, typename... Args>
class FunctionRecursive {
	F f;
public:
	FunctionRecursive(F&& f) : f(std::forward<F>(f)) { }
	FunctionRecursive(const F& f) : f(f)             { }

	template<typename... Args2>
	decltype(auto) operator()(Args2&&... args2) const {
		return f(function<A1, Args...>(*this),std::forward<Args2>(args2)...); 
	}
};

template<typename A1, typename... Args, typename F>
auto function_recursive(F&& f) {
	return function<A1, Args...>(FunctionRecursive<F,A1,Args...>(std::forward<F>(f)));
}	

}