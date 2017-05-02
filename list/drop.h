#ifndef _FUNCTIONAL_LIST_DROP_H_
#define _FUNCTIONAL_LIST_DROP_H_

#include "../function/function.h"
#include "core/list-proxy.h"

namespace fun {

// Note that this implementation is reasonable but slow on
// invocation (not in lazy evaluation) because it requieres
// to advance the iterator
template<typename List>
auto drop_(unsigned long n, List&& l) {
	auto sol = list_proxy(std::forward<List>(l));
	for (unsigned long i=0; i<n; ++i) sol.pop_head();
	return sol;
}

/**************************************
 * fun::API                           *
 **************************************/
auto drop   = function<2>([] (unsigned long n, auto&& l) { return drop_(n, l);   });

};

#endif
