#ifndef _FUNCTIONAL_LIST_TAKE_H_
#define _FUNCTIONAL_LIST_TAKE_H_

#include "../iterator/const_iterator.h"
#include <memory>

namespace fun {

template<typename List>
class Take
{
    std::unique_ptr<List> l; typename List::const_iterator b; typename List::const_iterator e;
    unsigned long n;
public:
    Take(unsigned long _n, const List& _l) : 
	    b(_l.begin()), e(_l.end()), 
	    n(_n) { } 
    Take(unsigned long _n, List&& _l) : 
	    l(std::make_unique<List>(_l)), b(*l.begin()), e(*l.end()),
       	    n(_n) { }

    class const_iterator : public ConstIteratorFacade<const_iterator>
    {
	    friend class Take<List>;
	    typename List::const_iterator i;
	    unsigned long n;

	    const_iterator(const typename List::const_iterator& _i, unsigned long _n) : i(_i), n(_n) { }
	public:
		void inc() { ++i; ++n; }
		bool equals(const const_iterator& that) const       { return (this->i == that.i) || (this->n == that.n); }
		typename List::value_type operator*() const { return *i;   } 		
    };

    using value_type     = typename List::value_type;

    const_iterator begin() const { return const_iterator(b, 0); }
    const_iterator end()   const { return const_iterator(e, n); }
};

template<typename List>
auto take_(unsigned long n, List&& l) 
{   return Take<typename std::remove_reference<List>::type>(n, std::forward<List>(l)); }



/**************************************
 * fun::API                           *
 **************************************/
auto take   = [] (unsigned long n, auto&& l) { return take_(n, l);   };

};

#endif
