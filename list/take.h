#ifndef _FUNCTIONAL_LIST_TAKE_H_
#define _FUNCTIONAL_LIST_TAKE_H_

#include "../list-core/forward-list.h"
#include "../function/function.h"
#include <memory>

namespace fun {

template<typename List>
class Take :  public ForwardListImpl<Take<List>,typename List::value_type>

{
    std::shared_ptr<List> l; typename List::const_iterator b; typename List::const_iterator e;
    unsigned long n;
public:
    Take(unsigned long _n, const List& _l) : 
	    b(_l.begin()), e(_l.end()), 
	    n(_n) { } 
    Take(unsigned long _n, List&& _l) : 
	    l(std::make_shared<List>(_l)), b(*l.begin()), e(*l.end()),
       	    n(_n) { }

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

    const_iterator_local begin_local() const { return const_iterator_local(b, 0); }
    const_iterator_local end_local()   const { return const_iterator_local(e, n); }
};

template<typename List>
auto take_(unsigned long n, List&& l) 
{   return Take<typename std::remove_reference<List>::type>(n, std::forward<List>(l)); }


/**************************************
 * fun::API                           *
 **************************************/
auto take   = function<2>([] (unsigned long n, auto&& l) { return take_(n, l);   });

};

#endif
