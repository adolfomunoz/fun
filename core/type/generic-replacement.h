#pragma once

#include "generic.h"
#include <type_traits>
#include <tuple>

namespace fun {

namespace detail {
    template<std::size_t Index, typename NewType, typename T, std::size_t... I>
    auto tuple_replace(const T& t, std::index_sequence<I...>) {
	    return std::tuple((I==Index)?NewType{}:std::get<I>(t)...);
    }

    template<typename T, std::size_t... I>
    auto tuple_expand(const T& t, std::index_sequence<I...>) {
	    return std::tuple((I<std::tuple_size_v<T>)?std::get<I>(t):Generic<I>{}...);
    }
}

template<std::size_t I, typename NewType, typename Replacement = std::tuple<Generic<0> > >
struct generic_replacement {
	using type = decltype(detail::tuple_replace<I,NewType>(detail::tuple_expand(std::declval<Replacement>(),std::make_index_sequence<I+1>{}),std::make_index_sequence<I+1>{})); 
};


}
