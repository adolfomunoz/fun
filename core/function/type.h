#pragma once

#include "generic.h"
#include "function.h"
#include <type_traits>

namespace fun {

/*******************************
 * SPECIFIC TYPES
 *******************************/

struct Function {};


/*******************************
 * THE GENERAL TYPE
 *******************************/

template<typename... T>
struct type {
	template<typename Type>
	struct match {
		static constexpr bool value = false; 
	};
};

template<typename T>
struct type<T> {
	template<typename Type>
	struct match {
		static constexpr bool value = std::is_same<T,Type>::value; 
	};
};

template<typename T1, typename T2>
using type_match_v = typename type<T1>::template match<T2>::value;


template<typename A1, typename A2, typename... Rest>
struct type<Function, A1, A2, Rest...> {
	template<typename Type>
	struct match { // This "false" includes Function_<F,Ret>
		static constexpr bool value = false;
	};

	template<typename F, typename Ret, typename Arg, typename... Args> 
	struct match<Function_<F,Ret,Arg, Args...>> {
		static constexpr bool value = 
//			typename type<A1>::template match<Arg>::value &&
		       	typename type<Function, A2, Rest...>::template match<Function_<F,Ret,Args...>>::value;
	};

	template<typename F, typename Ret> 
	struct match<Function_<F,Ret>> {
		static constexpr bool value = false;
	};
};

template<typename A1>
struct type<Function, A1> {
	template<typename Type>
	struct match { // This "false" includes Function_<F,Ret>
		static constexpr bool value = false;
	};

	template<typename F, typename Ret> 
	struct match<Function_<F,Ret>> {
		static constexpr bool value = typename type<A1>::template match<Ret>::value;
	};
};







}
