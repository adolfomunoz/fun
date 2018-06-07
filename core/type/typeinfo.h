#pragma once

#include "generic.h"
#include "type.h"

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
struct typeinfo<bool> {
	static  std::string name() { return "Bool"; }
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
	static  std::string name() { std::string n; n = char('a'+I); return n; }
};

template<>
struct typeinfo<std::string> {
	static  std::string name() { return "[Char]"; }
};

template<typename... Args> 
struct typeinfo<std::tuple<Args...>> {
private:
	template<typename Arg, typename... Rest>
	struct  innertypeinfo {
			static std::string name() { return typeinfo<Arg>::name()+","+innertypeinfo<Rest...>::name(); }
	};
	template<typename Arg>
	struct  innertypeinfo<Arg> {
			static std::string name() { return typeinfo<Arg>::name(); }
	};
public:
	static std::string name() { return std::string("(")+innertypeinfo<Args...>::name()+")"; }
};

template<typename... Args> 
struct typeinfo<type<Args...>> {
private:
	template<typename Arg, typename... Rest>
	struct  innertypeinfo {
			static std::string name() { return typeinfo<Arg>::name()+" "+innertypeinfo<Rest...>::name(); }
	};
	template<typename Arg>
	struct  innertypeinfo<Arg> {
			static std::string name() { return typeinfo<Arg>::name(); }
	};
public:
	static std::string name() { return innertypeinfo<Args...>::name(); }
};

template<typename... Args>
struct typeinfo<type<Tuple, Args...>> {
	static std::string name() { return typeinfo<std::tuple<Args...>>::name(); }
};



}
