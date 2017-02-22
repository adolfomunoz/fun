#ifndef _FUNCTIONAL_FILTER_H_
#define _FUNCTIONAL_FILTER_H_

#include "../function/function.h"
#include "../list-core/forward-list.h"
#include <utility>
#include <type_traits>
#include <memory>

namespace fun {

template<typename List, typename Predicate>
class Filtered : public ForwardListImpl<Filtered<List,Predicate>,typename List::value_type>
{
private:
	std::shared_ptr<List> list; typename List::const_iterator b; typename List::const_iterator e;
	Predicate predicate;
	friend class const_iterator_local;
public:
	using value_type = typename List::value_type; 

	Filtered(Predicate&& _predicate, List&& _list):
		list(std::make_shared<List>(_list)), b(*list.begin()), e(*list.end()),
		predicate(std::forward<Predicate>(_predicate)) { }

	Filtered(Predicate&& _predicate, const List& _list):
		b(_list.begin()), e(_list.end()),
		predicate(std::forward<Predicate>(_predicate)) { }

	Filtered(const Predicate& _predicate, List&& _list):
		list(std::make_shared<List>(_list)), b(*list.begin()), e(*list.end()),
		predicate(_predicate) { }

	Filtered(const Predicate& _predicate, const List& _list):
		b(_list.begin()), e(_list.end()),
		predicate(_predicate) { }

	class const_iterator_local
	{
		typename List::const_iterator i;
		const Filtered<List,Predicate>& f;
//		Filtered<List,Predicate>::value_type v;
		
		//(*i) is evaluated twice for filtered data, once for the predicate and once in get. We cannot 
		//do it otherwise because we would need to use assignment.
		//An advance implementation would use assignment for assignable types and this way for non-assignabe.
		void advance() { 
			while( (i!=f.e) && (!f.predicate(*i)) ) ++i; 
		}

	public:
		void inc() { ++i; advance(); }
		bool equals(const const_iterator_local& that) const { return this->i == that.i; }
		auto get() const { return (*i); } 		
		const_iterator_local(const typename List::const_iterator& _i, const Filtered<List,Predicate>& _f) : 
			i(_i), f(_f) { advance(); }
	};

	const_iterator_local begin_local() const { return const_iterator_local(b, *this);  }
	const_iterator_local end_local()   const { return const_iterator_local(e, *this); }
};

template<typename List, typename Predicate>
auto filter_(Predicate&& predicate, List&& list)
{	return Filtered<typename std::remove_reference<List>::type,typename std::remove_reference<Predicate>::type>
		(std::forward<Predicate>(predicate), std::forward<List>(list));  }

/**************************************
 * fun::API                           *
 **************************************/
auto filter = function<2>([] (auto&& p1, auto&& p2) { return filter_(p1, p2); });


}; //namespace fun

#endif
