#pragma once

#include "type.h"

namespace fun {

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
struct typeinfo<type<Tuple, Args...>> {
	static std::string name() { return typeinfo<std::tuple<Args...>>::name(); }
};



}
