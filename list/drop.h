#ifndef _FUNCTIONAL_LIST_DROP_H_
#define _FUNCTIONAL_LIST_DROP_H_

#include "../function/function.h"
#include "core/list-proxy.h"

namespace fun {

template<typename List>
class Drop :  public ForwardListImpl<Drop<List>,typename List::value_type>

{
    unsigned long n;
    List l;
    typename List::const_iterator b;

    void setup() { for (unsigned long i = 0; i<n; ++i) ++b; }
public:
    Drop(unsigned long n, const List& l)      : n(n), l(l), b(this->l.begin())                      { setup(); }
    Drop(unsigned long n, List&& l)  noexcept : n(n), l(std::forward<List>(l)), b(this->l.begin())  { setup(); }
    Drop(const Drop& that)                    : n(that.n), l(that.l), b(this->l.begin())            { setup(); }
    Drop(Drop&& that)                         : n(that.n), l(std::move(that.l)), b(this->l.begin()) { setup(); }

    class const_iterator_local 
    {
	    	typename List::const_iterator i;
	public:
		void inc() { ++i; }
		bool equals(const const_iterator_local& that) const       { return (this->i == that.i); }
		typename List::value_type get() const { return *i;   } 		
	    	const_iterator_local(const typename List::const_iterator& _i) : i(_i) { }
    };

    using value_type     = typename List::value_type;

    const_iterator_local begin_local() const { return const_iterator_local(b);       }
    const_iterator_local end_local()   const { return const_iterator_local(l.end()); }
};


// Note that this implementation is reasonable but slow on
// invocation (not in lazy evaluation) because it requieres
// to advance the iterator -> USELESS copying iterators is wrong.
/*template<typename List>
auto drop_(unsigned long n, List&& l) {
	auto sol = list_proxy(std::forward<List>(l));
	for (unsigned long i=0; i<n; ++i) sol.pop_head();
	return sol;
}*/

// Note that this implementation is reasonable but slow on constructing / moving / copying
// because it requieres to advance the iterator
template<typename List>
auto drop_(unsigned long n, List&& l) 
{ return Drop<typename std::remove_reference<List>::type>(n, std::forward<List>(l)); }


/**************************************
 * fun::API                           *
 **************************************/
auto drop   = function<2>([] (unsigned long n, auto&& l) { return drop_(n, std::forward<decltype(l)>(l));   });

};

#endif
