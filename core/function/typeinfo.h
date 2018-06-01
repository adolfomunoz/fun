#pragma once

#include "generic.h"
#include "function.h"

namespace fun {

template<typename T>
struct typeinfo {
	static  std::string name() { return "<unknown>"; }
};

template<typename T>
struct typeinfo<const T&> {
	static  std::string name() { return typeinfo<T>::name(); }
};

template<typename T>
struct typeinfo<T&&> {
	static  std::string name() { return typeinfo<T>::name(); }
};

template<>
struct typeinfo<float> {
	static  std::string name() { return "Float"; }
};

template<>
struct typeinfo<double> {
	static  std::string name() { return "Double"; }
};

template<>
struct typeinfo<int> {
	static  std::string name() { return "Int"; }
};

template<>
struct typeinfo<char> {
	static  std::string name() { return "Char"; }
};

template<std::size_t I>
struct typeinfo<Generic<I>> {
	static  std::string name() { std::string n; n = char('a'-1+I); return n; }
};

template<>
struct typeinfo<std::string> {
	static  std::string name() { return "[Char]"; }
};


template<typename F, typename Ret, typename Arg, typename... Args>
struct typeinfo<Function_<F,Ret,Arg, Args...>> {
	static  std::string name() { return typeinfo<Arg>::name() + " -> " + typeinfo<Function_<F,Ret,Args...>>::name(); }
};

template<typename F, typename Ret>
struct typeinfo<Function_<F,Ret>> {
	static  std::string name() { return typeinfo<Ret>::name(); }
};





}
