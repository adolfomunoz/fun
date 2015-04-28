#ifndef _FUNCTIONAL_LIST_CYCLE_H_
#define _FUNCTIONAL_LIST_CYCLE_H_

#include "../iterator/const_iterator.h"
#include <memory>

namespace fun {

template<typename List>
class Cycle
{
    std::unique_ptr<List> l; typename List::const_iterator b; typename List::const_iterator e;
public:
    Cycle(const List& _l) : b(_l.begin()), e(_l.end())  { } 
    Cycle(List&& _l)      : l(std::make_unique<List>(_l)), b(*l.begin()), e(*l.end()) { }

    class const_iterator : public ConstIteratorFacade<const_iterator>
    {
	    friend class Take<List>;
	    typename List::const_iterator i;
	    const Cycle<List>& cy;

	    const_iterator(const typename List::const_iterator& _i, const Cycle<List>& _cy) : 
		    i(_i), cy(_cy) { }
	public:
		void inc() { ++i; if (i==cy.e) i = cy.b; }
		bool equals(const const_iterator& that) const { return (this->i == that.i); }
		typename List::value_type operator*()   const { return *i;   } 		
    };

    using value_type     = typename List::value_type;

    const_iterator begin() const { return const_iterator(b, *this); }
    const_iterator end()   const { return const_iterator(e, *this); }
};

template<typename List>
auto cycle_(List&& l) 
{   return Cycle<typename std::remove_reference<List>::type>(std::forward<List>(l)); }



/**************************************
 * fun::API                           *
 **************************************/
auto cycle   = [] (auto&& l) { return cycle_(l);   };

};

#endif
