#pragma once

#include "generic.h"
#include <type_traits>
#include <tuple>

namespace fun {

struct initial_replacement {
	using type = std::tuple<Generic<1>>; 
};

template<typename T, std::size_t Index, template NewType, std::size_t... I>
auto tuple_replace(const T& t, std::index_sequence<I...>) {
	return std::tuple((I==Index)?NewType():std::get<I>(t)...);
}

template<typename T, std::size_t... I>
auto tuple_expand(const T& t, std::index_sequence<I...>) {
	return std::tuple((I<std::tuple_size_v<T>)?std::get<I>(t):Generic<I>);
}

template<std::size_t I, typename NewType, typename Replacement>
struct add_generic_replacement {
	using type = decltype(tuple_replace<
	using type = decltype(std::tuple_cat(std::declval<std::tuple<Arg>>()),
			std::declval<typename add_generic_replacement<I,NewType,Args...>::type>());
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
