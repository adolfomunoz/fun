#pragma once

#include "../type/typeinfo.h"
#include "type.h"

namespace fun {

//We are ignoring the classes

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

template<typename F, typename Classes, typename Ret, typename Arg, typename... Args>
struct typeinfo<Function_<F,Classes, Ret,Arg, Args...>> {
	static  std::string name() { return typeinfo<Arg>::name() + " -> " + typeinfo<Function_<F,Classes,Ret,Args...>>::name(); }
};

template<typename F, typename Classes, typename Ret, typename... InnerArgs, typename... Args>
struct typeinfo<Function_<F,Classes,Ret,type<Function, InnerArgs...>, Args...>> {
	static  std::string name() { return std::string("(") + typeinfo<type<Function, InnerArgs...>>::name() + ") -> " + typeinfo<Function_<F,Classes,Ret,Args...>>::name(); }
};


template<typename F, typename Classes, typename Ret>
struct typeinfo<Function_<F,Classes,Ret>> {
	static  std::string name() { return typeinfo<Ret>::name(); }
};





}
