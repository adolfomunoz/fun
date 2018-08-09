#pragma once

#include "../function/function.h"
#include "../function/function-lazy.h"
#include "recursive-list.h"
#include "type.h"

namespace fun {


	
template<typename T, typename LazyRest>
RecursiveList<std::decay_t<T>, std::decay_t<LazyRest>> l_(T&& t, LazyRest&& lazy_rest) {
	return RecursiveListNode<std::decay_t<T>, std::decay_t<LazyRest>>(
		std::forward<T>(t), std::forward<LazyRest>(lazy_rest));
}		

auto l = function<generic::a,type<List, generic::a>, type<List, generic::a>>(
	[] (auto&& x, auto&& xs) { return l_(x,xs); });
	
template<typename... TS>
struct C { };

template<typename T, typename... TS>
struct C<T,TS...> {
	static auto list(T&& x, TS&&... xs) {
		return l(std::forward<T>(x),C<TS...>::list(std::forward<TS>(xs)...));
	}
};

template<>
struct C<> {
	static auto list() { return EmptyList(); }
};

template<typename... TS>
auto c(TS&&... xs) {
	return C<TS...>::list(std::forward<TS>(xs)...);
}
	
}