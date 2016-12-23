#ifndef _FUNCTIONAL_UNCURRY_H_
#define _FUNCTIONAL_UNCURRY_H_

#include "function.h"
#include <tuple>

namespace fun {

template<unsigned int N, unsigned int I>
class Uncurry {
public:
	template<typename F, typename ...TupleParams>
	static auto apply(const Function<N,F>& f, const std::tuple<TupleParams...>& params) {
		static_assert(std::tuple_size<std::tuple<TupleParams...>>::value == N, "Function uncurried with a tuple of different size than its number of parameters.");
		return Uncurry<N-1,I+1>::apply(f(std::get<I>(params)),params);
	}
};

template<unsigned int I>
class Uncurry<1,I> {
public:
	template<typename F, typename Tuple>
	static auto apply(const Function<1,F>& f, const Tuple& params) {
		return f(std::get<I>(params));
	}
};

template<unsigned int N, typename F, typename ...TupleParams>
auto uncurry_(const Function<N,F>& f, const std::tuple<TupleParams...>& params) {
	return Uncurry<N,0>::apply(f, params);
}

template<unsigned int N, typename F, typename Iterator>
auto uncurry_iterator_(const Function<N,F>& f, Iterator& i) {
	auto v = *(i++); 
	return uncurry_iterator_(f(v), i);
}

template<typename F, typename Iterator>
auto uncurry_iterator_(const Function<1,F>& f, Iterator& i) {
	return f(*(i++));
}

template<typename F, typename List>
auto uncurry_list_(const F& f, const List& l) {
	auto iter = l.begin();
	return uncurry_iterator_(f, iter);
}

/**************************************
 * fun::API                           *
 **************************************/
auto uncurry          = function<2>([] (const auto& f, const auto& tuple) { return uncurry_(f, tuple); });
auto uncurry_iterator = function<2>([] (const auto& f, auto& iter)  { return uncurry_iterator_(f, iter); });
auto uncurry_list     = function<2>([] (const auto& f, const auto& list)  { return uncurry_list_(f, list); });

}; //namespace fun

#endif
