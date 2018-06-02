#pragma once

#include "../type/typeinfo.h"
#include "function.h"

namespace fun {

template<typename F, typename Ret, typename Arg, typename... Args>
struct typeinfo<Function_<F,Ret,Arg, Args...>> {
	static  std::string name() { return typeinfo<Arg>::name() + " -> " + typeinfo<Function_<F,Ret,Args...>>::name(); }
};

template<typename F, typename Ret>
struct typeinfo<Function_<F,Ret>> {
	static  std::string name() { return typeinfo<Ret>::name(); }
};





}
