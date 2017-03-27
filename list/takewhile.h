#ifndef _FUNCTIONAL_LIST_TAKEWHILE_H_
#define _FUNCTIONAL_LIST_TAKEWHILE_H_

#include "../list-core/list-proxy.h"
#include <memory>

namespace fun {

template<typename List, typename Predicate>
class TakeWhile:  public ForwardListImpl<TakeWhile<List,Predicate>,typename List::value_type>
{
    Predicate predicate;
	List l;

public:
	TakeWhile(Predicate&& predicate, List&& l) : predicate(predicate), l(l) { }
	TakeWhile(const Predicate& predicate, List&& l) : predicate(predicate), l(l) { }
	TakeWhile(Predicate&& predicate, const List& l) : predicate(predicate), l(l) { }
	TakeWhile(const Predicate& predicate, const List& l) : predicate(predicate), l(l) { }

    class const_iterator_local 
    {
	    friend class TakeWhile<List, Predicate>;
	    typename List::const_iterator i;
	    const Predicate& predicate;

	public:
		void inc() { ++i; }
		bool equals(const const_iterator_local& that) const       { return (this->i == that.i) || (!predicate(*i)); }
		typename List::value_type get() const { return *i;   } 		
	    const_iterator_local(const typename List::const_iterator& _i, const Predicate& p) : i(_i), predicate(p) { }
    };

    using value_type     = typename List::value_type;

    const_iterator_local begin_local() const { return const_iterator_local(l.begin(), predicate); }
    const_iterator_local end_local()   const { return const_iterator_local(l.end(),   predicate); }
};

template<typename List, typename Predicate>
auto takeWhile_(Predicate&& predicate, List&& l) 
{   return TakeWhile<typename std::remove_reference<List>::type,
	    Predicate>(std::forward<Predicate>(predicate), std::forward<List>(l)); }



/**************************************
 * fun::API                           *
 **************************************/
auto takeWhile   = [] (auto p, auto l) { return takeWhile_(std::forward<decltype(p)>(p), 
		std::forward<decltype(l)>(l));   };

};

#endif
