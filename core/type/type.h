#pragma once

#include "generic.h"
#include "generic-replacement.h"
#include <type_traits>

namespace fun {

template<typename TypeID, typename... Params>
struct type {};

template<typename P, typename R>
struct type_construct {
	using type = fun::type<P,R>;
};

template<typename P, typename... R>
struct type_construct<P, type<R...>> {
	using type = fun::type<P,R...>;
};

 
template<typename T, typename U>
struct match {
	static constexpr bool value = std::is_same<T,U>::value; 
	using replacements = generic_replacement_default_t;
};

template<std::size_t I, typename U>
struct match<Generic<I>,U> {
	static constexpr bool value = true; 
	using replacements = generic_replacement_t<I,U>;
};

template<typename Replacements, typename T>
struct apply_replacements {
	using type = T;
};

template<typename Replacements, typename T>
using apply_replacements_t = typename apply_replacements<Replacements, T>::type;

template<typename Replacements, std::size_t I>
struct apply_replacements<Replacements,Generic<I>> {
	using type = generic_replacement_find_t<I,Replacements>;
};

template<typename Replacements, typename T>
struct apply_replacements<Replacements, type<T>> {
	using type = fun::type<T>;
};

template<typename Replacements, std::size_t I>
struct apply_replacements<Replacements,type<Generic<I>>> {
	using type = fun::type<generic_replacement_find_t<I,Replacements>>;
};

template<typename Replacements, typename P, typename... R>
struct apply_replacements<Replacements, type<P,R...>> {
	using type = typename type_construct<P,apply_replacements_t<Replacements,fun::type<R...>>>::type;
};

template<typename Replacements, std::size_t I, typename... R>
struct apply_replacements<Replacements, type<Generic<I>,R...> > {
	using type = typename type_construct<generic_replacement_find_t<I,Replacements>,apply_replacements_t<Replacements,fun::type<R...>>>::type;
};


/*
template<typename TypeID, typename P1, typename... R1, typename P2, typename... R2> 
struct match<type<TypeID,P1,R1...>, type<TypeID,P2,R2...>> {

};
*/

}
