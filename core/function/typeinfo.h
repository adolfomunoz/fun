#pragma once

#include "../type/typeinfo.h"
#include "type.h"

namespace fun {

template<typename P, typename... R>
struct typeinfo<type<Function, P, R...>> {
	static std::string name() { return typeinfo<P>::name() + " -> " + typeinfo<type<Function,R...>>::name(); }
};

template<typename... InnerR, typename... R>
struct typeinfo<type<Function, type<Function, InnerR...>, R...>> {
	static std::string name() { return std::string("(") + typeinfo<type<Function,InnerR...>>::name() + ") -> " + typeinfo<type<Function,R...>>::name(); }
};

template<typename P>
struct typeinfo<type<Function, P>> {
	static std::string name() { return typeinfo<P>::name(); }
};

template<typename F, typename Ret, typename Arg, typename... Args>
struct typeinfo<Function_<F,Ret,Arg, Args...>> {
	static  std::string name() { return typeinfo<Arg>::name() + " -> " + typeinfo<Function_<F,Ret,Args...>>::name(); }
};

template<typename F, typename Ret, typename... InnerArgs, typename... Args>
struct typeinfo<Function_<F,Ret,type<Function, InnerArgs...>, Args...>> {
	static  std::string name() { return std::string("(") + typeinfo<type<Function, InnerArgs...>>::name() + ") -> " + typeinfo<Function_<F,Ret,Args...>>::name(); }
};


template<typename F, typename Ret>
struct typeinfo<Function_<F,Ret>> {
	static  std::string name() { return typeinfo<Ret>::name(); }
};





}
