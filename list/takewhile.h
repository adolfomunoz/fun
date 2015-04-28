#ifndef _FUNCTIONAL_LIST_TAKEWHILE_H_
#define _FUNCTIONAL_LIST_TAKEWHILE_H_

#include "../iterator/const_iterator.h"
#include <memory>

namespace fun {

template<typename List, typename Predicate>
class TakeWhile
{
    std::unique_ptr<List> l; typename List::const_iterator b; typename List::const_iterator e;
    Predicate predicate;
    friend class const_iterator;
public:
    TakeWhile(Predicate&& _predicate, const List& _l) : 
	    b(_l.begin()), e(_l.end()), 
	    predicate(std::forward<Predicate>(_predicate)) { } 
    TakeWhile(Predicate&& _predicate, List&& _l) : 
	    l(std::make_unique<List>(_l)), b(*l.begin()), e(*l.end()),
	    predicate(std::forward<Predicate>(_predicate)) { } 
    TakeWhile(const Predicate& _predicate, const List& _l) : 
	    b(_l.begin()), e(_l.end()), 
	    predicate(_predicate) { } 
    TakeWhile(const Predicate& _predicate, List&& _l) : 
	    l(std::make_unique<List>(_l)), b(*l.begin()), e(*l.end()),
	    predicate(_predicate) { } 

    class const_iterator : public ConstIteratorFacade<const_iterator>
    {
	    friend class TakeWhile<List, Predicate>;
	    typename List::const_iterator i;
	    const Predicate& predicate;

	    const_iterator(const typename List::const_iterator& _i, const Predicate& p) : i(_i), predicate(p) { }
	public:
		void inc() { ++i; }
		bool equals(const const_iterator& that) const       { return (this->i == that.i) || (!predicate(*i)); }
		typename List::value_type operator*() const { return *i;   } 		
    };

    using value_type     = typename List::value_type;

    const_iterator begin() const { return const_iterator(b, predicate); }
    const_iterator end()   const { return const_iterator(e, predicate); }
};

template<typename List, typename Predicate>
auto takeWhile_(Predicate&& predicate, List&& l) 
{   return TakeWhile<typename std::remove_reference<List>::type,
	    typename std::remove_reference<Predicate>::type>(std::forward<Predicate>(predicate), std::forward<List>(l)); }



/**************************************
 * fun::API                           *
 **************************************/
auto takeWhile   = [] (auto&& p, auto&& l) { return takeWhile_(p, l);   };

};

#endif
