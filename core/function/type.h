#pragma once

#include "../type/type.h"
#include "function.h"

namespace fun {

/*******************************
 * TYPE TAG
 *******************************/

struct Function {};

/*******************************
 * MATCH
 *******************************/

template<typename P1, typename... R1, typename F, typename Ret2, typename P2, typename... R2> 
struct match<type<Function,P1,R1...>, Function_<F,Ret2,P2,R2...>> {
	using match_head = match<P1,P2>;
	using match_rest = match< apply_replacements_t<typename match_head::replacements,type<Function,R1...>>, Function_<F,Ret2,R2...> >;

	static constexpr bool value = (match_head::value) && (match_rest::value); 
	using replacements = generic_replacement_merge_t<typename match_head::replacements, typename match_rest::replacements>;
};

template<typename P1, typename F, typename Ret2> 
struct match<type<Function,P1>, Function_<F,Ret2>> {
	using match_head = match<P1,Ret2>;

	static constexpr bool value = match_head::value;
	using replacements = typename match_head::replacements;
};








}
