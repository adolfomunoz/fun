#ifndef _FUNCTIONAL_LIST_DROPWHILE_H_
#define _FUNCTIONAL_LIST_DROPWHILE_H_

#include "core/list-proxy.h"
#include "../function/function.h"

namespace fun {
	
template<typename Predicate, typename List>
class DropWhile :  public ForwardListImpl<DropWhile<Predicate,List>,typename List::value_type>

{
    Predicate predicate;
    List l;
    typename List::const_iterator b;

    void setup() { while(predicate(*b)) ++b;  }
public:
    DropWhile(Predicate&& predicate, List&& l) : predicate(std::forward<Predicate>(predicate)), l(std::forward<List>(l)), b(this->l.begin()) { setup(); }
    DropWhile(const Predicate& predicate, List&& l) : predicate(predicate), l(std::forward<List>(l)), b(this->l.begin())                     { setup(); }
    DropWhile(Predicate&& predicate, const List& l) : predicate(std::forward<Predicate>(predicate)), l(l), b(this->l.begin())                { setup(); }
    DropWhile(const Predicate& predicate, const List& l) : predicate(predicate), l(l), b(this->l.begin())                                    { setup(); }
    DropWhile(const DropWhile& that) : predicate(that.predicate), l(that.l), b(this->l.begin())                                              { setup(); }
    DropWhile(DropWhile&& that) : predicate(std::move(that.predicate)), l(std::move(that.l)), b(this->l.begin())                             { setup(); }

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
// to advance the iterator -> DOES NOT WORK: copies iterators
/*template<typename Predicate, typename List>
auto dropWhile_(const Predicate& predicate, List&& l)
{
	auto sol = list_proxy(std::forward<List>(l));
	while (predicate(sol.front())) sol.pop_head();
	return sol;
}*/

// Note that this implementation is reasonable but slow on constructing / moving / copying
template<typename Predicate, typename List>
auto dropWhile_(Predicate&& predicate, List&& l)
{	return DropWhile<typename std::remove_reference<Predicate>::type, typename std::remove_reference<List>::type>(std::forward<Predicate>(predicate), std::forward<List>(l)); }


/**************************************
 * fun::API                           *
 **************************************/
auto dropWhile   = function<2>([] (auto&& predicate, auto&& l) { return dropWhile_(std::forward<decltype(predicate)>(predicate), std::forward<decltype(l)>(l));   });

};

#endif
