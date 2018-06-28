#ifndef _FUNCTIONAL_FILTER_H_
#define _FUNCTIONAL_FILTER_H_

#include "../../function/function.h"
#include "../core/forward-list.h"
#include <utility>
#include <type_traits>
#include <memory>

namespace fun {

template<typename Predicate, typename List>
class Filtered : public ForwardListImpl<Filtered<Predicate, List>, typename List::value_type>
{
private:
	List list;
	Predicate predicate;
public:
	using value_type = typename List::value_type; 

	Filtered(Predicate&& predicate, List&& list):      list(std::forward<List>(list)), predicate(std::forward<Predicate>(predicate)) { }
	Filtered(Predicate&& predicate, const List& list): list(list), predicate(std::forward<Predicate>(predicate)) { }
	Filtered(const Predicate& predicate, List&& list):      list(std::forward<List>(list)), predicate(predicate) { }
	Filtered(const Predicate& predicate, const List& list): list(list), predicate(predicate) { }

	class const_iterator_local
	{
		typename List::const_iterator i;
		const Filtered<Predicate, List>& f;
		
		//(*i) is evaluated twice for filtered data, once for the predicate and once in get. We cannot 
		//do it otherwise because we would need to use assignment.
		//An advance implementation would use assignment for assignable types and this way for non-assignabe.
		void advance() { 
			while( (i!=f.list.end()) && (!f.predicate(*i)) ) ++i; 
		}

	public:
		void inc() { ++i; advance(); }
		bool equals(const const_iterator_local& that) const { return this->i == that.i; }
		auto get() const { return (*i); } 		
		const_iterator_local(const typename List::const_iterator& _i, const Filtered<Predicate,List>& _f) : 
			i(_i), f(_f) { advance(); }
	};

	const_iterator_local begin_local() const { return const_iterator_local(list.begin(), *this); }
	const_iterator_local end_local()   const { return const_iterator_local(list.end(),   *this); }
};

/*
template<typename List, typename Predicate>
auto filter_(Predicate&& predicate, List&& list)
{	return Filtered<typename std::remove_reference<List>::type,typename std::remove_reference<Predicate>::type>
		(std::forward<Predicate>(predicate), std::forward<List>(list));  }
*/

/**************************************
 * fun::API                           *
 **************************************/
auto filter = function<2>([] (auto&& p1, auto&& p2) { 
	return Filtered<typename std::remove_reference<decltype(p1)>::type,typename std::remove_reference<decltype(p2)>::type>
		(std::forward<decltype(p1)>(p1), std::forward<decltype(p2)>(p2)); 
});


}; //namespace fun

#endif
