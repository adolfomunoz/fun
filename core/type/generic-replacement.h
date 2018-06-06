#pragma once

#include "generic.h"
#include <type_traits>
#include <tuple>

namespace fun {

namespace detail {

	/*
    template<bool cond, typename T1, typename T2>
    constexpr auto choose(const T1& t1, const T2& t2) {
	if constexpr (cond) return t1; else return t2;
    }

    template<std::size_t Index, typename NewType, typename T, std::size_t... I>
    constexpr auto tuple_replace(const T& t, std::index_sequence<I...>) {
	    return std::tuple(choose<I==Index>(NewType{},std::get<I>(t))...);
    }

    template<typename T, std::size_t... I>
    constexpr auto tuple_expand(const T& t, std::index_sequence<I...>) {
	    return std::tuple(choose<I<std::tuple_size_v<T>>(std::get<I>(t),Generic<I>{})...);
    }
   */

    template<typename Tuple, std::size_t Index, typename NewType, typename Indices>
    struct tuple_replace_sequence { };

    template<typename Tuple, std::size_t Index, typename NewType, std::size_t... I>
    struct tuple_replace_sequence<Tuple, Index, NewType, std::integer_sequence<std::size_t, I...>> {
  	using type = std::tuple<typename std::conditional<I==Index, NewType, typename std::tuple_element<I,Tuple>::type>::type...>;
    };

    template<typename Tuple, std::size_t Index, typename NewType>
    struct tuple_replace {
	using type = typename tuple_replace_sequence<Tuple, Index, NewType, std::make_index_sequence<std::tuple_size_v<Tuple>>>::type;
    };

    template <std::size_t I, typename Tuple, bool IsInTuple = (I < std::tuple_size_v<Tuple>)>
    struct tuple_expand_element {
	using type = Generic<I>;
    };

    template <std::size_t I, typename Tuple>
    struct tuple_expand_element<I,Tuple,true> {
	using type = typename std::tuple_element<I, Tuple>::type;
    };

    template<typename Tuple, typename Indices>
    struct tuple_expand_sequence { };

    template<typename Tuple, std::size_t... I>
    struct tuple_expand_sequence<Tuple, std::integer_sequence<std::size_t, I...>> {
	using type = std::tuple<typename tuple_expand_element<I,Tuple>::type... >;
    };


    template<typename Tuple, std::size_t N>
    struct tuple_expand {
	using type = typename tuple_expand_sequence<Tuple, std::make_index_sequence<std::max(N,std::tuple_size_v<Tuple>)>>::type;
    };
    
}

struct generic_replacement_default {
	using type = std::tuple<Generic<0> >;
};

using generic_replacement_default_t = generic_replacement_default::type;

template<std::size_t I, typename NewType, typename Replacement = typename generic_replacement_default::type>
struct generic_replacement {
	using type = typename detail::tuple_replace<typename detail::tuple_expand<Replacement,I+1>::type, I, NewType>::type;  
};
//Maybe we need to replace the default "NewType = Generic<J>" when it is included, although maybe we can take care of this case elsewhere.

template<std::size_t I, typename NewType, typename Replacement = std::tuple<Generic<0> > >
using generic_replacement_t = typename generic_replacement<I, NewType, Replacement>::type;

template<std::size_t I, typename Replacement> 
struct generic_replacement_find {
	using type = typename detail::tuple_expand_element<I, Replacement>::type;
};

template<std::size_t I, typename Replacement>
using generic_replacement_find_t = typename generic_replacement_find<I,Replacement>::type;

}
