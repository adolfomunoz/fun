#ifndef _FUNCTIONAL_LIST_DROP_H_
#define _FUNCTIONAL_LIST_DROP_H_

#include "../list-core/list-proxy.h"
#include "../function/function.h"

namespace fun {


template<typename List>
auto drop_(unsigned long n, List&& l)
{
	auto iter = l.begin();
	for (unsigned int i = 0; i < n; ++i) { ++iter; }
	return list_proxy(std::forward<List>(l), iter);
}

/**************************************
 * fun::API                           *
 **************************************/
auto drop   = function<2>([] (unsigned long n, auto&& l) { return drop_(n, l);   });

};

#endif
