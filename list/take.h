#ifndef _FUNCTIONAL_LIST_TAKE_H_
#define _FUNCTIONAL_LIST_TAKE_H_

#include "../list-core/forward-list.h"
#include "../function/function.h"
#include "zip.h"
#include "../function/misc.h"
#include "../function/flip.h"

namespace fun {

template<typename List>
class Take :  public ForwardListImpl<Take<List>,typename List::value_type>

{
	unsigned long n;
    List l;

public:
    template<typename L>
    Take(unsigned long n, const List& l)      : n(n), l(l) { }
    Take(unsigned long n, List&& l)  noexcept : n(n), l(l) { }

    class const_iterator_local 
    {
	    friend class Take<List>;
	    typename List::const_iterator i;
	    unsigned long n;

	public:
		void inc() { ++i; ++n; }
		bool equals(const const_iterator_local& that) const       { return (this->i == that.i) || (this->n == that.n); }
		typename List::value_type get() const { return *i;   } 		
	    	const_iterator_local(const typename List::const_iterator& _i, unsigned long _n) : i(_i), n(_n) { }
    };

    using value_type     = typename List::value_type;

    const_iterator_local begin_local() const { return const_iterator_local(l.begin(), 0); }
    const_iterator_local end_local()   const { return const_iterator_local(l.end()  , n); }
};

template<typename List>
auto take_(unsigned long n, List&& l) 
{   return Take<typename std::remove_reference<List>::type>(n, std::forward<List>(l)); }



/**************************************
 * fun::API                           *
 **************************************/
auto take   = function<2>([] (unsigned long n, auto&& l) { return take_(n, l);   });
auto take_2   = function<1>([] (unsigned long n) 
{	return fun::zipWith(fun::flip(fun::constant), fun::range((unsigned long)(1),n));  });

};

#endif
