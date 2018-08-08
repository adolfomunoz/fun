#pragma once

#include <utility>
#include <tuple>
#include <iostream>
#include "../type/type.h"
#include "../type/classes.h"

//This replaces something that will happen in C++20
namespace std {
template< class T >
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};	

template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;
}

//Watch out: const char* parameters are problematic with currying
namespace fun {
	
//Handles construction of functions
template<typename F>
class FunctionBase
{
protected:
	F   f;
public:
	constexpr FunctionBase(F&& f)      : f(std::forward<F>(f)) { }
	constexpr FunctionBase(const F& f) : f(f) { }

	//Implementation details, do not use
	const F& impl() const { return f; }
};

//Handles construction of functions, specialization for function pointers (standard C++ functions)
template<typename F>
class FunctionBase<F&>
{
protected:
	F&   f;
public:
	constexpr FunctionBase(const F& f) : f(f) { }
	const F& impl() const { return f; }
};


template<typename F, typename Classes, typename... Args>
class Function_ : public FunctionBase<F> { };

namespace detail {
	template<typename F, typename Classes, typename T>
	struct function_from_tuple { };
	
	template<typename F, typename Classes, typename... Args>
	struct function_from_tuple<F,Classes,std::tuple<Args...>> {
		using type = Function_<F,Classes,Args...>;
	};

	template<typename T, std::size_t... I>
	auto tuple_elements(const T& t, std::index_sequence<I...>) {
		return std::tuple(std::get<I>(t)...);
	}
	
	template<typename... Args>
	auto tuple_reorder(const std::tuple<Args...>& t) {
		return std::tuple_cat(std::tuple(std::get<sizeof...(Args)-1>(t)),
			tuple_elements(t, std::make_index_sequence<sizeof...(Args)-1>{}));
	}	
}

}; //namespace fun

