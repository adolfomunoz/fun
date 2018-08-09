#pragma once

#include "../type/type.h"
#include "iterable-list.h"
#include "recursive-list.h"
#include <list>
#include <vector>
#include <array>

namespace fun {

struct List { };

template<typename T1, typename T2> 
struct match<type<List,T1>, std::list<T2>> {
	using match_element_type = match<T1,T2>;

	static constexpr bool value = match_element_type::value;
	using replacements = typename match_element_type::replacements;
};

template<typename T1, typename T2> 
struct match<type<List,T1>, std::vector<T2>> {
	using match_element_type = match<T1,T2>;

	static constexpr bool value = match_element_type::value;
	using replacements = typename match_element_type::replacements;
};

template<typename T1, typename T2, std::size_t N> 
struct match<type<List,T1>, std::array<T2,N>> {
	using match_element_type = match<T1,T2>;

	static constexpr bool value = match_element_type::value;
	using replacements = typename match_element_type::replacements;
};

template<typename T1, typename L, typename T2> 
struct match<type<List,T1>, IterableListImpl<L,T2>> {
	using match_element_type = match<T1,T2>;

	static constexpr bool value = match_element_type::value;
	using replacements = typename match_element_type::replacements;
};

template<typename T1, typename T2> 
struct match<type<List,T1>, IterableList<T2>> {
	using match_element_type = match<T1,T2>;

	static constexpr bool value = match_element_type::value;
	using replacements = typename match_element_type::replacements;
};

template<typename T1> 
struct match<type<List,T1>, EmptyList> {
	static constexpr bool value = true;
	using replacements = generic_replacement_default;
};


template<typename T1, typename T2, typename Rest> 
struct match<type<List,T1>, RecursiveList<T2,Rest>> {
	using match_element_type = match<T1,T2>;

	static constexpr bool value = match_element_type::value;
	using replacements = typename match_element_type::replacements;
};

}
