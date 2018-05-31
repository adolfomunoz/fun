#pragma once

#include "generic.h"
#include "function.h"

namespace fun {

template<typename T>
struct type {
	static  std::string name() { return "<unknown>"; }
};

template<typename T>
struct type<const T&> {
	static  std::string name() { return type<T>::name(); }
};

template<typename T>
struct type<T&&> {
	static  std::string name() { return type<T>::name(); }
};

template<>
struct type<float> {
	static  std::string name() { return "Float"; }
};

template<>
struct type<double> {
	static  std::string name() { return "Double"; }
};

template<>
struct type<int> {
	static  std::string name() { return "Int"; }
};

template<>
struct type<char> {
	static  std::string name() { return "Char"; }
};

template<std::size_t I>
struct type<Generic<I>> {
	static  std::string name() { std::string n; n = char('a'-1+I); return n; }
};

template<>
struct type<std::string> {
	static  std::string name() { return "[Char]"; }
};


template<typename F, typename Ret, typename Arg, typename... Args>
struct type<Function<F,Ret,Arg, Args...>> {
	static  std::string name() { return type<Arg>::name() + " -> " + type<Function<F,Ret,Args...>>::name(); }
};

template<typename F, typename Ret>
struct type<Function<F,Ret>> {
	static  std::string name() { return type<Ret>::name(); }
};





}
