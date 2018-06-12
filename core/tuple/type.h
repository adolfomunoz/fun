#pragma once

#include "../type/type.h"
#include <tuple>

namespace fun {

struct Tuple { };

template<typename P1, typename... R1, typename P2, typename... R2> 
struct match<type<Tuple,P1,R1...>, std::tuple<P2,R2...>> {
	using match_head = match<P1,P2>;
	using match_rest = match< apply_replacements_t<typename match_head::replacements,type<Tuple,R1...>>, std::tuple<R2...> >;

	static constexpr bool value = (match_head::value) && (match_rest::value); 
	using replacements = generic_replacement_merge_t<typename match_head::replacements, typename match_rest::replacements>;
};

template<typename P1, typename P2> 
struct match<type<Tuple,P1>, std::tuple<P2>> {
	using match_head = match<P1,P2>;

	static constexpr bool value = match_head::value;
	using replacements = typename match_head::replacements;
};



}
