#ifndef _FUNCTIONAL_LIST_DROPWHILE_H_
#define _FUNCTIONAL_LIST_DROPWHILE_H_

#include "../list-core/list-proxy.h"
#include "../function/function.h"

namespace fun {

// Note that this implementation is reasonable but slow on
// invocation (not in lazy evaluation) because it requieres
// to advance the iterator
template<typename Predicate, typename List>
auto dropWhile_(const Predicate& predicate, List&& l)
{
	auto iter = l.begin();
	while (predicate(*iter)) ++iter;
	return list_proxy(std::forward<List>(l), iter);
}

/**************************************
 * fun::API                           *
 **************************************/
auto dropWhile   = function<2>([] (const auto& predicate, auto&& l) { return dropWhile_(predicate, l);   });

};

#endif
