#pragma once

#include "generic.h"
#include <type_traits>
#include <tuple>

namespace fun {

namespace detail {

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

template<typename Replacement1, typename Replacement2, std::size_t I = 0, typename R2I = typename generic_replacement_find<I,Replacement2>::type, bool last = (I == (std::tuple_size_v<Replacement2>-1))>
struct generic_replacement_merge {
	using type = typename generic_replacement<I,R2I, typename generic_replacement_merge<Replacement1, Replacement2, I+1>::type>::type;
};

template<typename Replacement1, typename Replacement2, std::size_t I>
struct generic_replacement_merge<Replacement1, Replacement2, I, Generic<I>, false> {
	using type = typename generic_replacement_merge<Replacement1, Replacement2, I+1>::type;
};

template<typename Replacement1, typename Replacement2, std::size_t I, typename R2I>
struct generic_replacement_merge<Replacement1, Replacement2, I, R2I, true> {
	using type = typename generic_replacement<I, R2I, Replacement1>::type;
};

template<typename Replacement1, typename Replacement2, std::size_t I>
struct generic_replacement_merge<Replacement1, Replacement2, I, Generic<std::tuple_size_v<Replacement2>-1>, true> {
	using type = Replacement1;
};

template<typename Replacement1, typename Replacement2>
using generic_replacement_merge_t = typename generic_replacement_merge<Replacement1, Replacement2>::type;




}
